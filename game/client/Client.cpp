//
// Created by tsv on 18.04.19.
//

#include "Client.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <cstring>

short ID = 5;

Client::Client()
        : m_window (sf::VideoMode(1280, 720), "HL3", sf::Style::Titlebar | sf::Style::Close), m_objects(), is_map(false), this_player_id(0),
          is_creator(false) {
    std::cout << ID << '\n';
    //тут меняется область видимости камеры
    //NOTE: отношение строном области видимости должно совпадать с отшонешием сторон окна
    view.get_view().reset(sf::FloatRect(0, 0, 640, 360));
}


//Client::Client(const std::string &host, unsigned short port, const std::string &username)
//        : m_window(sf::VideoMode(640, 512), "HALF LIFE 3"), m_objects(), is_map(false), this_player_id(0),
//          is_creator(false) {
//
//    auto socket = std::make_unique<sf::TcpSocket>();
//    if (socket->connect(sf::IpAddress(host), port) != sf::Socket::Done) {
//        throw std::runtime_error(std::strerror(errno));
//    }
//    //std::cout << ID << '\n';
//    m_user = std::make_shared<User>(username, std::move(socket));
//    //тут меняется область видимости камеры
//    //NOTE: отношение строном области видимости должно совпадать с отшонешием сторон окна
//    view.get_view().reset(sf::FloatRect(0, 0, 480, 384));
//}

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
    is_creator = true;
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
    float current_frame_enemy = 0;  //хранит текущий кадр врага
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    while (m_window.isOpen()) {

        // process_events();

        TimeSinceUpdate += clock.restart();
        time = TimePerFrame.asSeconds();
        while (TimeSinceUpdate > TimePerFrame) {
            receive_from_server();
            process_events();
            render(time, current_frame, current_frame_enemy);
            send_to_server();
            TimeSinceUpdate -= TimePerFrame;
        }
    }

    return 0;
}

void Client::process_events() {
    sf::Event event{};
    //sf::SoundBuffer buffer;

   // sf::Sound sound;


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

    m_weapon.pistol = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);

    //управление стрелочками стрельбой пулями
    m_fire_dir.f_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_window.hasFocus();
    m_fire_dir.f_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_window.hasFocus();
    m_fire_dir.f_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_window.hasFocus();
    m_fire_dir.f_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_window.hasFocus();

    m_direction.fire = 0;
    if (m_fire_dir.f_up || m_fire_dir.f_left || m_fire_dir.f_right || m_fire_dir.f_down){
    m_direction.fire = 1;


   // sound.setBuffer(buffer);
   // sound.play();
    }//выстрел
    apply_dir_b();
}

void Client::receive_from_server() {
    trans::ServerToUserVectorMessage message;
    sf::Packet packet;
    while (m_user->receive_packet(packet) != sf::Socket::Done) { ; }
    packet >> message;

    apply_messages(message);
}

void Client::render(float time, float& dir, float& dir_en) {
    m_window.clear();

    m_window.setView(view.get_view());

    m_level.Draw(m_window);

    for (auto& obj: m_objects) {
        if (obj->object_name == n_enemy) {
            obj->draw(m_window, time, dir_en);
        }
        if (obj->object_name == n_player) {
            obj->draw(m_window, time, dir);
        }
        if (obj->object_name == n_bullet) { //можно будет потом заменить, пусть пока останется (статическая отрисовка)
            obj->draw_stat(m_window);

        }
    }

    m_window.display();
}

void Client::send_to_server() {
    trans::UserToServerMessage message;

    //trans::UserToServerMessage message;
    trans::UserToServerMessage_Direction *direction = new trans::UserToServerMessage_Direction;
    direction->set_up(m_direction.up);
    direction->set_down(m_direction.down);
    direction->set_left(m_direction.left);
    direction->set_right(m_direction.right);
    direction->set_fire(m_direction.fire);

    //траектория пули
    trans::UserToServerMessage_BulletDirection *bulletDirection = new trans::UserToServerMessage_BulletDirection;
    bulletDirection->set_up(m_direction_bullet.up);
    bulletDirection->set_down(m_direction_bullet.down);
    bulletDirection->set_left(m_direction_bullet.left);
    bulletDirection->set_right(m_direction_bullet.right);

    trans::UserToServerMessage_Weapon *weap_choise = new trans::UserToServerMessage_Weapon;
    weap_choise->set_pistol(choise_weapon.pistol);
    weap_choise->set_automat(choise_weapon.automat);
    weap_choise->set_shotgun(choise_weapon.shotgun);

    message.set_type(trans::UserToServerMessage::Move);
    message.set_allocated_direction(direction);
    message.set_allocated_b_direction(bulletDirection);


    sf::Packet packet;
    packet << message;

    m_user->send_packet(packet);
}

void Client::apply_messages(const trans::ServerToUserVectorMessage &messages) {

    Objects temp_obj; //создаем временный вектор, чтобы обновить основной (очистить от "удаленных" пуль)
    for (auto obj : m_objects) {
        if (obj->get_hp() > 0 || obj->object_name == n_player) {
            temp_obj.push_back(obj);
        }
    }
    m_objects = temp_obj;
    for (const trans::ServerToUserMessage &message: messages.vec_messages()) {
        if (message.type() == trans::ServerToUserMessage::NewPlayer) {
            m_objects.push_back(std::make_shared<Player>(message.np_msg().id(), message.np_msg().username(),

            sf::Vector2f(message.np_msg().x(), message.np_msg().y()), message.np_msg().hp()));

            if (!is_map) {
                //std::cout << message.np_msg().map_name();
                this->m_level.GetMapName() = message.np_msg().map_name();
                this->m_level.LoadFromFile("../../client/maps/" + message.np_msg().map_name());
                if (is_creator) {
                    auto obj = m_level.GetAllObjects("Wall");
                    send_obj_to_server(obj);
                }
                is_map = true;
            }
            if (!this_player_id) {
                this_player_id = message.np_msg().id();
            }
        } else if (message.type() == trans::ServerToUserMessage::UpdatePlayer) {
            bool is_in = false;
            for (const auto obj: m_objects) {
                if (obj->get_id() == message.upd_msg().id()) {
                    is_in = true;
                    obj->set_position(sf::Vector2f(message.upd_msg().x(), message.upd_msg().y()));
                    Direction direction = {message.upd_msg().direction().up(), message.upd_msg().direction().left(),
                                           message.upd_msg().direction().right(), message.upd_msg().direction().down()};
                    obj->set_direction(direction);
                    //obj->set_state(message.upd_msg().state());
                    obj->set_hp(message.upd_msg().hp());
                    if (this_player_id == message.upd_msg().id()) {
                        view.set_view(message.upd_msg().x(), message.upd_msg().y(), m_level.GetTilemapWidth(),
                                      m_level.GetTilemapHeight());
                    }
                }
            }
            if (!is_in) {
                m_objects.push_back(std::make_shared<Player>(message.upd_msg().id(), " ",
                                                             sf::Vector2f(message.upd_msg().x(),
                                                                          message.upd_msg().y()),
                                                                          message.upd_msg().hp()));
            }
        } else if (message.type() == trans::ServerToUserMessage::NewBot) {
            m_objects.push_back(std::make_shared<Enemy>(message.n_bot_msg().id(),
                                            sf::Vector2f(message.n_bot_msg().x(), message.n_bot_msg().y()), message.n_bot_msg().hp()));

        } else if (message.type() == trans::ServerToUserMessage::UpdateBot) {
            bool is_in = false;
            for (const auto obj: m_objects) {
                if (obj->get_id() == message.u_bot_msg().id()) {
                    is_in = true;
                    obj->update_dir_enemy( message.u_bot_msg().step_x(), message.u_bot_msg().step_y()); //смотрим направление по обновлению координат
                    obj->set_position(sf::Vector2f(message.u_bot_msg().x(), message.u_bot_msg().y()));
                    obj->set_hp(message.u_bot_msg().hp());
                }
            }
            if (!is_in && message.u_bot_msg().hp()) {
                m_objects.push_back(std::make_shared<Enemy>(message.u_bot_msg().id(),
                                                            sf::Vector2f(message.u_bot_msg().x(),
                                                                         message.u_bot_msg().y()),
                                                                         message.u_bot_msg().hp()));
            }
        } else if (message.type() == trans::ServerToUserMessage::NewBullet) {
            m_objects.push_back(std::make_shared<Bullet>(message.nb_msg().id(),
                                                         sf::Vector2f(message.nb_msg().x(), message.nb_msg().y()), message.nb_msg().hp()));
            //play_sound();
            buffer.loadFromFile("../../client/sounds/pistol.wav");
            sound.setBuffer(buffer);
            sound.setVolume(5);
            //sf::Sound sound;
            sound.play();


        } else if (message.type() == trans::ServerToUserMessage::UpdateBullet) {
            for (const auto obj: m_objects) {
                if (obj->get_id() == message.ub_msg().id()) {
                    obj->set_position(sf::Vector2f(message.ub_msg().x(), message.ub_msg().y()));
                    obj->set_hp(message.ub_msg().hp());
                }
            }
        }
    }
}

void Client::apply_dir_b() { // устанавливаем тракеторию пули (убираем неопределенность, когда нажато несколько клавиш)
    if (m_fire_dir.f_up) {
        m_direction_bullet.up = m_fire_dir.f_up;
        m_direction_bullet.down = 0;
        m_direction_bullet.right = 0;
        m_direction_bullet.left = 0;
    } else if (m_fire_dir.f_down) {
        m_direction_bullet.down = m_fire_dir.f_down;
        m_direction_bullet.right = 0;
        m_direction_bullet.left = 0;
        m_direction_bullet.up = 0;
    } else if (m_fire_dir.f_right) {
        m_direction_bullet.right = m_fire_dir.f_right;
        m_direction_bullet.left = 0;
        m_direction_bullet.up = 0;
        m_direction_bullet.down = 0;
    } else if (m_fire_dir.f_left) {
        m_direction_bullet.left = m_fire_dir.f_left;
        m_direction_bullet.up = 0;
        m_direction_bullet.down = 0;
        m_direction_bullet.right = 0;
    }
}

void Client::send_obj_to_server(std::vector<TmxObject> &all_objects) {
    //if (all_objects[0].name == "Wall") {
        for (auto obj: all_objects) {
            trans::UserToServerMessage message;
            auto *rect = new trans::UserToServerMessage_Rect;
            rect->set_left(obj.rect.left);
            rect->set_top(obj.rect.top);
            rect->set_width(obj.rect.width);
            rect->set_height(obj.rect.height);

            //message.set_type(trans::UserToServerMessage::Wall);

            if (obj.name == "Wall") {
                message.set_type(trans::UserToServerMessage::Wall);
            }
            if (obj.name == "lava") {
                message.set_type(trans::UserToServerMessage::Lava);
            }
            if (obj.name == "spike") {
                message.set_type(trans::UserToServerMessage::Spike);
            }

            message.set_allocated_rect(rect);

            sf::Packet packet;
            packet << message;

            m_user->send_packet(packet);
            packet.clear();
        }
   // }
}

void Client::choise_of_weapon() {
    if (m_weapon.pistol) {
        choise_weapon.pistol = 1;
        choise_weapon.automat = 0;
        choise_weapon.shotgun = 0;
    } else if (m_weapon.automat) {
        choise_weapon.pistol = 0;
        choise_weapon.automat = 1;
        choise_weapon.shotgun = 0;
    } else if (m_weapon.shotgun) {
        choise_weapon.pistol = 0;
        choise_weapon.automat = 0;
        choise_weapon.shotgun = 1;
    }

}

void Client::play_sound() {
    //sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("../../client/sounds/pistol.wav")) {
        return;
    }
    //sf::Sound sound;
    sound.play();

   /* while (sound.getStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
        std::cout << std::flush;
    } */
    //std::cout << std::endl << std::endl;
}

sf::RenderWindow &Client::get_window() {
    return m_window;
}

void Client::set_config(const std::string &host, unsigned short port, const std::string &username) {
    auto socket = std::make_unique<sf::TcpSocket>();
    if (socket->connect(sf::IpAddress(host), port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }
    m_user = std::make_shared<User>(username, std::move(socket));
}

