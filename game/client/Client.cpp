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

#include "transition.pb.h"

Client::Client(const std::string& host, unsigned short port, const std::string& username)
        : m_window(sf::VideoMode(800, 600), "game")
        , m_objects() {
    auto socket = std::make_unique<sf::TcpSocket>();
    if (socket->connect(sf::IpAddress(host), port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }

    m_user = std::make_shared<User>(username, std::move(socket));
}

void Client::create_session() {
    sf::Packet packet;

    trans::UserInitMessage message;
    {
        message.set_action(trans::UserInitMessage::Create);
        message.set_username(m_user->get_username());
        message.set_session_id(0);
        //UserInitMessage message = {UserInitMessage::Create, m_user->get_username(), 0};
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
        trans::UserInitMessage message;
        //UserInitMessage message = {UserInitMessage::Join, m_user->get_username(), session_id};
        message.set_action(trans::UserInitMessage::Join);
        message.set_username(m_user->get_username());
        message.set_session_id(session_id);
        packet << message;

        m_user->send_packet(packet);

        std::cout << "Joined to session " << session_id << std::endl;
    }
}

int Client::run() {
    sf::Time TimeSinceUpdate = sf::Time::Zero;
    sf:: Time TimePerFrame = sf::seconds(1.f / 90.f);
    sf::Clock clock;
    clock.restart();
    while (m_window.isOpen()) {
        process_events();
        TimeSinceUpdate += clock.restart();
        while (TimeSinceUpdate > TimePerFrame) {
            receive_from_server();
            process_events();
            render();
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

    m_direction.up = sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_window.hasFocus();
    m_direction.left = sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_window.hasFocus();
    m_direction.right = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_window.hasFocus())
        m_direction.right = true;
    m_direction.down = sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_window.hasFocus();
}

void Client::receive_from_server() {
    trans::ServerToUserVectorMessage message;

    sf::Packet packet;
    packet.clear();
    while (m_user->receive_packet(packet) != sf::Socket::Done) {;}
    packet >> message;

    apply_messages(message);
}

void Client::render() {
    m_window.clear();

    for (auto& obj: m_objects) {
        obj->draw(m_window);
    }

    m_window.display();
}

void Client::send_to_server() {
    trans::UserToServerMessage message;
    trans::UserToServerMessage_Direction *direction = new trans::UserToServerMessage_Direction;
    direction->set_up(m_direction.up);
    direction->set_down(m_direction.down);
    direction->set_left(m_direction.left);
    direction->set_right(m_direction.right);

    message.set_type(trans::UserToServerMessage::Move);
    message.set_allocated_direction(direction);
    //UserToServerMessage message = {.type=UserToServerMessage::Move};
    //message.direction = m_direction;

    sf::Packet packet;
    packet << message;

    m_user->send_packet(packet);
}

void Client::apply_messages(const trans::ServerToUserVectorMessage& messages) {
    for (const trans::ServerToUserMessage& message: messages.vec_messages()) {
        if (message.type() == trans::ServerToUserMessage::NewPlayer) {
            m_objects.push_back(std::make_shared<Player>(message.np_msg().id(), message.np_msg().username(),
                                sf::Vector2f(message.np_msg().x(), message.np_msg().y())));
        }
        else if (message.type() == ServerToUserMessage::UpdatePlayer) {
            bool is_in = false;
            for (const auto obj: m_objects) {
                if (obj.get()->get_id() == message.upd_msg().id()) {
                    is_in = true;
                    //std::cout << "ID " << obj->get_id() << " X " <<message_upd.x << " Y " << message_upd.y << "\n";
                    obj->set_position(sf::Vector2f(message.upd_msg().x(), message.upd_msg().y()));
                }
            }
            if (!is_in) {
                m_objects.push_back(std::make_shared<Player>(message.upd_msg().id(), " ",
                        sf::Vector2f(message.upd_msg().x(), message.upd_msg().y())));
            }

        }
    }
}

