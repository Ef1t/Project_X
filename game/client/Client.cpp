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


Client::Client(const std::string &host, unsigned short port, const std::string &username)
        : m_window(sf::VideoMode(640, 512), "HALF LIFE 3"), m_objects(), is_map(false), this_player_id(0) {

    auto socket = std::make_unique<sf::TcpSocket>();
    if (socket->connect(sf::IpAddress(host), port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }
    //std::cout << ID << '\n';
    m_user = std::make_shared<User>(username, std::move(socket));
    //тут меняется область видимости камера
    //NOTE отношение строном области видимости должно совпадать с отшонешием сторон окна
    view.get_view().reset(sf::FloatRect(0, 0, 480, 384));
}

void Client::create_session(std::string map_name) {
    sf::Packet packet;

    {
        trans::UserInitMessage message;
        message.set_action(trans::UserInitMessage::Create);
        message.set_username(m_user->get_username());
        message.set_session_id(0);
        message.set_map_name(map_name);
        packet << message;

        m_user->send_packet(packet);
    }

    {
        packet.clear();

        while (m_user->receive_packet(packet) != sf::Socket::Done) {
        }

        trans::SessionCreatedMessage message;
        packet >> message;

        std::cout << "New session created. Session ID: " << message.session_id() << std::endl;

    }

}

void Client::join_to(sf::Uint64 session_id) {
    sf::Packet packet;
    {
        trans::UserInitMessage message;
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
    sf::Time TimePerFrame = sf::seconds(1.f / 90.f);
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
            render(time, current_frame);
            send_to_server();
            TimeSinceUpdate -= TimePerFrame;
            // std::cout<<"ID: " << this_player_id << '\n';
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
    m_direction.fire = sf::Keyboard::isKeyPressed(sf::Keyboard::Space); //создать пепеменную state
    apply_dir_b();
}

void Client::receive_from_server() {
    trans::ServerToUserVectorMessage message;
    sf::Packet packet;
    while (m_user->receive_packet(packet) != sf::Socket::Done) { ; }
    packet >> message;

    apply_messages(message);
}

void Client::render(float time, float &dir) {
    m_window.clear();
    m_window.setView(view.get_view());

    m_level.Draw(m_window);
    for (auto &obj: m_objects) {
        //std::cout << "Type = " << obj->object_name << std::endl;
        if (obj->object_name == n_player) {
            obj->draw(m_window, time, dir);
        }
        if (obj->object_name == n_bullet) {
            obj->draw_stat(m_window);
        }


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
    direction->set_fire(m_direction.fire);


    trans::UserToServerMessage_BulletDirection *bulletDirection = new trans::UserToServerMessage_BulletDirection;
    bulletDirection->set_up(m_direction_bullet.up);
    bulletDirection->set_down(m_direction_bullet.down);
    bulletDirection->set_left(m_direction_bullet.left);
    bulletDirection->set_right(m_direction_bullet.right);


    message.set_type(trans::UserToServerMessage::Move);
    message.set_allocated_direction(direction);
    message.set_allocated_b_direction(bulletDirection);


    sf::Packet packet;
    packet << message;

    m_user->send_packet(packet);
}

void Client::apply_messages(const trans::ServerToUserVectorMessage &messages) {

    for (const trans::ServerToUserMessage &message: messages.vec_messages()) {
        if (message.type() == trans::ServerToUserMessage::NewPlayer) {
            m_objects.push_back(std::make_shared<Player>(message.np_msg().id(), message.np_msg().username(),
                                                         sf::Vector2f(message.np_msg().x(), message.np_msg().y())));

            if (!is_map) {
                std::cout << message.np_msg().map_name();
                this->m_level.GetMapName() = message.np_msg().map_name();
                this->m_level.LoadFromFile("../../client/maps/" + message.np_msg().map_name());

                is_map = true;
            }
            if (!this_player_id) {
                this_player_id = message.np_msg().id();
            }

        } else if (message.type() == trans::ServerToUserMessage::UpdatePlayer) {
            bool is_in = false;
            for (const auto obj: m_objects) {
                if (obj.get()->get_id() == message.upd_msg().id()) {
                    is_in = true;
                    obj->set_position(sf::Vector2f(message.upd_msg().x(), message.upd_msg().y()));
                    Direction direction = {message.upd_msg().direction().up(), message.upd_msg().direction().left(),
                                           message.upd_msg().direction().right(), message.upd_msg().direction().down()};
                    obj->set_direction(direction);
                    if (this_player_id == message.upd_msg().id()) {
                        view.set_view(message.upd_msg().x(), message.upd_msg().y(), m_level.GetTilemapWidth(),
                                      m_level.GetTilemapHeight());

                    }
                }
            }
            if (!is_in) {
                m_objects.push_back(
                        std::make_shared<Player>(message.upd_msg().id(), " ",
                                                 sf::Vector2f(message.upd_msg().x(), message.upd_msg().y())));
            }
        } else if (message.type() == trans::ServerToUserMessage::NewBullet) {
            std::cout << "Bullet added\n";
            m_objects.push_back(std::make_shared<Bullet>(message.nb_msg().id(),
                                                         sf::Vector2f(message.nb_msg().x(), message.nb_msg().y())));
            std::cout << message.nb_msg().id() << " bullet ID\n";
            //m_objects[1]->set_position(sf::Vector2f(50,50));
            // std::cout << m_objects[1]->get_x() << '\n';
            // std::cout << "nb X = " << message.nb_msg().x() << "\n";
            // std::cout << "nb Y = " << message.nb_msg().y() << "\n";
            // std::cout << " X = " << message.np_msg().x() << "\n";
            // std::cout << " Y = " << message.np_msg().y() << "\n";

        } else if (message.type() == trans::ServerToUserMessage::UpdateBullet) {
            int i = 0;
            for (const auto obj: m_objects) {
                bool alive = true;

                ++i;

                puts("");
                std:: cout << message.ub_msg().state() << " Alive s\n\n";
                if((obj->get_id() == message.ub_msg().id() && (alive != message.ub_msg().state()))) {
                    puts("");
                    std:: cout << message.ub_msg().state() << " Alive false\n\n";
//                    BulletPtr temp;
//                    temp = bullet;
//                    m_bullets[i] = m_bullets[m_bullets.size() - 1];
//                    m_bullets[m_bullets.size() - 1] = temp;
//                    m_bullets.pop_back();

                    ObjectPtr temp;
                    temp = obj;
                    m_objects[i] = m_objects[m_objects.size() - 1];
                    m_objects[m_objects.size() - 1] = temp;
                    m_objects.pop_back();
                    m_objects.resize(m_objects.size() - 1);
                    if (m_objects.empty()) {
                        break;

                    }
                   // continue;
                    std::cout << "DELETE\n";


                } else
                if (obj->get_id() == message.ub_msg().id()) {
                    puts("");
                    std:: cout << message.ub_msg().state() << " Alive true\n\n";
                    std::cout << "Bullet updated\n";
                    std::cout << message.ub_msg().name() << " name\n";
                    std::cout << "obj X = " << obj->get_x() << "\n";
                    std::cout << "obj Y = " << obj->get_y() << "\n";
                    obj->set_position(sf::Vector2f(message.ub_msg().x(), message.ub_msg().y()));


                }

            }

        }
    }
}

void Client::apply_dir_b() { // устанавливаем тракеторию пули (убираем неопределенность, когда нажато несколько клавиш)
    if (m_direction.up) {
        m_direction_bullet.up = m_direction.up;
        m_direction_bullet.down = 0;
        m_direction_bullet.right = 0;
        m_direction_bullet.left = 0;
    } else if (m_direction.down) {
        m_direction_bullet.down = m_direction.down;
        m_direction_bullet.right = 0;
        m_direction_bullet.left = 0;
        m_direction_bullet.up = 0;
    } else if (m_direction.right) {
        m_direction_bullet.right = m_direction.right;
        m_direction_bullet.left = 0;
        m_direction_bullet.up = 0;
        m_direction_bullet.down = 0;
    } else if (m_direction.left) {
        m_direction_bullet.left = m_direction.left;
        m_direction_bullet.up = 0;
        m_direction_bullet.down = 0;
        m_direction_bullet.right = 0;
    }
}

//void Client::add_objects(std::vector<TmxObject> all_objects) {
//    for (auto obj: all_objects) {
//        if (obj.name == "Wall") {
//            m_objects.push_back(std::maked_shared<Wall>());
//        }
//    }
//}


