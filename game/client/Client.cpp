//
// Created by tsv on 18.04.19.
//

#include "Client.h"
#include "Object.h"
#include "Player.h"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <cstring>

short ID = 5;


Client::Client(const std::string& host, unsigned short port, const std::string& username)
        : m_window(sf::VideoMode(800, 600), "JOIN")
        , m_objects()
        , is_map(false) {
    auto socket = std::make_unique<sf::TcpSocket>();
    if (socket->connect(sf::IpAddress(host), port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }
    std::cout << ID << '\n';
    m_user = std::make_shared<User>(username, std::move(socket));
}

void Client::create_session(std::string map_name) {
    sf::Packet packet;

    {
        UserInitMessage message = {UserInitMessage::Create, m_user->get_username(), 0, map_name};
        packet << message;

        m_user->send_packet(packet);
    }

    {
        packet.clear();

        while (m_user->receive_packet(packet) != sf::Socket::Done) {
        }

        SessionCreatedMessage message{};
        packet >> message;

        std::cout << "New session created. Session ID: " << message.session_id << std::endl;

    }

}

void Client::join_to(sf::Uint64  session_id) {
    sf::Packet packet;

    {
        UserInitMessage message = {UserInitMessage::Join, m_user->get_username(), session_id};
        packet << message;

        m_user->send_packet(packet);

        std::cout << "Joined to session " << session_id << std::endl;
    }
}

int Client::run() {
    sf::Time TimeSinceUpdate = sf::Time::Zero;
    sf:: Time TimePerFrame = sf::seconds(1.f / 90.f);
    sf::Clock clock;
    float current_frame = 0;  //хранит текущий кадр
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    while (m_window.isOpen()) {
       // process_events();
        TimeSinceUpdate += clock.restart();
        time = TimePerFrame.asSeconds();
        while (TimeSinceUpdate > TimePerFrame) {
            receive_from_server();
            process_events();
            render(time,current_frame);
            send_to_server();
            TimeSinceUpdate -= TimePerFrame;

        }
    }

    return 0;
}

void Client::process_events() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {

        switch (event.type) {
            case sf::Event::Closed: {
                m_window.close();
                break;
            }

            default: {
                break;
            }
        }
    }

    m_direction.up = sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_window.hasFocus(); //добавить в поле direction
    m_direction.left = sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_window.hasFocus();
    m_direction.right = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_window.hasFocus())
        m_direction.right = true;
    m_direction.down = sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_window.hasFocus();



}

void Client::receive_from_server() {
    ServerToUserVectorMessage message;
    std::cout << ID << " ID PLAYERA \n";
    sf::Packet packet;
    packet.clear();
    while (m_user->receive_packet(packet) != sf::Socket::Done) {;}
    packet >> message;

    apply_messages(message);
}

void Client::render(float time, float& dir) {
    m_window.clear();

    m_level.Draw(m_window);
    for (auto& obj: m_objects) {
        obj->draw(m_window, time, dir);
    }

    m_window.display();
}

void Client::send_to_server() {
    UserToServerMessage message {.type=UserToServerMessage::Move};
    message.direction = m_direction;
    sf::Packet packet;

    packet << message;
    m_user->send_packet(packet);
}

void Client::apply_messages(const ServerToUserVectorMessage& messages) {
    for (const ServerToUserMessage& message: messages.messages) {
        if (message.type == ServerToUserMessage::NewPlayer) {
            NewPlayerMessage message_new = std::get<NewPlayerMessage>(message.value);
            m_objects.push_back(std::make_shared<Player>(message_new.id, message_new.username, sf::Vector2f(message_new.x, message_new.y)));
            //инициализация карты
            if (!is_map) {
                this->m_level.GetMapName() = message_new.map_name;
                this->m_level.LoadFromFile("../../client/maps/" + message_new.map_name);
                //инициализация объектов из структуры
                //TODO: добавлять сюда новые объекты
                //add_objects(m_level.GetAllObjects("Wall"));

                is_map = true;
            }
        }
        else if (message.type == ServerToUserMessage::UpdatePlayer) {
            UpdatePlayerMessage message_upd = std::get<UpdatePlayerMessage>(message.value);
            //std::cout << message_upd.id << "\n";
            bool is_in = false;
            for (const auto obj: m_objects) {
                if (obj.get()->get_id() == message_upd.id) {
                    is_in = true;
                    std::cout << "ID " << obj->get_id() << " X " <<message_upd.x << " Y " << message_upd.y << "\n";
                    obj->set_position(sf::Vector2f(message_upd.x, message_upd.y));
                    obj->set_direction(message_upd.route);
                }
            }
            if (!is_in) {
                m_objects.push_back(std::make_shared<Player>(message_upd.id, " ", sf::Vector2f(message_upd.x, message_upd.y)));

            }


        }
    }

}

//void Client::add_objects(std::vector<TmxObject> all_objects) {
//    for (auto obj: all_objects) {
//        if (obj.name == "Wall") {
//            m_objects.push_back(std::maked_shared<Wall>());
//        }
//    }
//}


