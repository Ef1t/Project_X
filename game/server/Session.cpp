//
// Created by tsv on 18.04.19.
//

#include <iostream>

#include "Session.h"
#include "messages/ServerToUserMessage.h"
#include "iostream"
#include "Enemy.h"
#include "TmxLevel.h"

sf::Uint64 Session::next_id = 10;


Session::Session(std::string_view map_name)
        : m_id(next_id++), m_users(), m_messages(), map_name(map_name) {
    TmxLevel level;
    level.LoadFromFile("../../client/maps/" + this->map_name);
    auto objects = level.GetAllObjects("VSE");
    for (auto obj : objects) {
        if (obj.name == "lava") {
            std::cout << "LAVA " << std::endl;
            m_land_objects.push_back(std::make_shared<Lava>(obj.rect.left,
                                                            obj.rect.top,
                                                            obj.rect.width,
                                                            obj.rect.height));
        }
        if (obj.name == "spike") {
            std::cout << "SPIKE " << std::endl;
            m_land_objects.push_back(std::make_shared<Spike>(obj.rect.left,
                                                             obj.rect.top,
                                                             obj.rect.width,
                                                             obj.rect.height));
        }
    }
}
unsigned int time_per_fire_pistol = 30; //коэффициент скоростельности (регулирует скорость стрельбы для одного оружия)
unsigned int time_per_fire_automat = 5;
unsigned int time_per_fire_shotgun = 40;

void Session::update(float dt) {
    for (auto &m_user : m_users) {
        sf::Packet packet;

        auto &user = m_user.first;
        auto &player = m_user.second;

        if (player->is_alive()) {
            UserSocket socket = user->get_socket();
            if (socket->receive(packet) == sf::Socket::Done) {
                trans::UserToServerMessage message;
                packet >> message;

                if (message.type() == trans::UserToServerMessage::Move) {
                    sf::Vector2f dir;
                    if (message.direction().up()) {
                        dir.y--;
                    }
                    if (message.direction().down()) {
                        dir.y++;
                    }
                    if (message.direction().left()) {
                        dir.x--;
                    }
                    if (message.direction().right()) {
                        dir.x++;
                    }
                    Direction direction = {message.direction().up(), message.direction().left(),
                                           message.direction().right(),
                                           message.direction().down(), message.direction().fire()};

                    player->apply(dir, direction);

                    Direction b_direction = {message.b_direction().up(), message.b_direction().left(),
                                             message.b_direction().right(), message.b_direction().down()};
                    std:: cout << message.weapon().pistol() << " Pistol\n";

                    //стрельба
                    if (player->get_route().fire == 1 && player->is_alive()) { //если нажата клавижа space, создаем пулю
                        if (message.weapon().pistol()) {
                            if (time_per_fire_pistol++ > 30) {
                                add_bullet(player, player->get_position().x, player->get_position().y, b_direction, pistolet);
                                time_per_fire_pistol = 0; //обнуляем счетчик после выстрела
                            }
                        } else if (message.weapon().automat()) {
                            if (time_per_fire_automat++ > 15) {
                                add_bullet(player, player->get_position().x, player->get_position().y, b_direction, aut);
                                time_per_fire_automat = 0; //обнуляем счетчик после выстрела
                            }
                        } else if (message.weapon().shotgun()) {
                            if (time_per_fire_shotgun++ > 40) {
                                add_bullet(player, player->get_position().x, player->get_position().y, b_direction, aut);
                                time_per_fire_shotgun = 0; //обнуляем счетчик после выстрела
                            }
                        }



                    }


                }
                if (message.type() == trans::UserToServerMessage::Wall) {
                    std::cout << "WALL " << std::endl;
                    m_objects.push_back(std::make_shared<Wall>(message.rect().left(),
                                                               message.rect().top(),
                                                               message.rect().width(),
                                                               message.rect().height(),
                                                               "Wall"));
                }
                if (message.type() == trans::UserToServerMessage::Lava) {
                    std::cout << "LAVA " << std::endl;
                    m_land_objects.push_back(std::make_shared<Lava>(message.rect().left(),
                                                                    message.rect().top(),
                                                                    message.rect().width(),
                                                                    message.rect().height()));
                }
                if (message.type() == trans::UserToServerMessage::Spike) {
                    std::cout << "SPIKE " << std::endl;
                    m_land_objects.push_back(std::make_shared<Spike>(message.rect().left(),
                                                                     message.rect().top(),
                                                                     message.rect().width(),
                                                                     message.rect().height()));
                }
            }
            user->receive_socket(socket);
        }
        if (player->is_alive()) {
            for (int i = 0; i < m_enemies.size(); ++i) {
                if (m_enemies[i]->is_alive()) {
                    int lol = m_enemies[i]->get_target();
                    //int64_t kek = m_users[lol]->get_position().x;
                    int j = 0; // player ID
                    for (auto user : m_users) {
                        //std::cout << "USER ID IS " << user.second->get_id() << "ENEMY ID IS " << m_enemies[i]->get_target() << std::endl;
                        if (j == m_enemies[i]->get_target()) {
                            m_enemies[i]->movement(dt, user.second->get_position().x, user.second->get_position().y,
                                                   m_objects);
                        }
                        j++;
                    }
                    auto *update_message = new trans::UpdateBotMessage;
                    update_message->set_id(m_enemies[i]->get_id());
                    update_message->set_x(m_enemies[i]->get_position().x);
                    update_message->set_y(m_enemies[i]->get_position().y);
                    update_message->set_hp(m_enemies[i]->get_hp());
                    update_message->set_step_x(m_enemies[i]->get_dir_x());
                    update_message->set_step_y(m_enemies[i]->get_dir_y());

                    auto server_message = m_messages.add_vec_messages();
                    server_message->set_type(trans::ServerToUserMessage::UpdateBot);
                    server_message->set_allocated_u_bot_msg(update_message);
                } else {
                    auto *update_message = new trans::UpdateBotMessage;
                    update_message->set_id(m_enemies[i]->get_id());
                    update_message->set_x(m_enemies[i]->get_position().x);
                    update_message->set_y(m_enemies[i]->get_position().y);
                    update_message->set_hp(m_enemies[i]->get_hp());
                    update_message->set_step_x(m_enemies[i]->get_dir_x());
                    update_message->set_step_y(m_enemies[i]->get_dir_y());

                    auto server_message = m_messages.add_vec_messages();
                    server_message->set_type(trans::ServerToUserMessage::UpdateBot);
                    server_message->set_allocated_u_bot_msg(update_message);
                    for (size_t j = 0; j < m_objects.size(); ++j) {
                        if (m_objects[j]->get_id() == m_enemies[i]->get_id()) {
                            m_objects.erase(m_objects.begin() + j);
                        }
                    }
                    m_enemies.erase(m_enemies.begin() + i);
                }
            }
        }
    }
    auto it = m_users.begin();
    for (int i = 0; it != m_users.end(); ++it, ++i) {
        auto &player = it->second;

        if (player->m_name == n_player && player->is_alive()) {
            player->update(dt * 10, m_objects);

            auto *direction = new trans::UpdatePlayerMessage::Direction;
            direction->set_up(player->get_route().up);
            direction->set_down(player->get_route().down); //почему не зануляются??
            direction->set_left(player->get_route().left);
            direction->set_right(player->get_route().right);

            auto *update_message = new trans::UpdatePlayerMessage;
            update_message->set_id(player->get_id());
            update_message->set_x(player->get_position().x);
            update_message->set_y(player->get_position().y);
            update_message->set_allocated_direction(direction);
            update_message->set_hp(player->get_hp());

            auto server_message = m_messages.add_vec_messages();
            server_message->set_type(trans::ServerToUserMessage::UpdatePlayer);
            server_message->set_allocated_upd_msg(update_message);
        } else {
            auto *direction = new trans::UpdatePlayerMessage::Direction;
            direction->set_up(player->get_route().up);
            direction->set_down(player->get_route().down); //почему не зануляются??
            direction->set_left(player->get_route().left);
            direction->set_right(player->get_route().right);

            auto *update_message = new trans::UpdatePlayerMessage;
            update_message->set_id(player->get_id());
            update_message->set_x(player->get_position().x);
            update_message->set_y(player->get_position().y);
            update_message->set_allocated_direction(direction);
            update_message->set_hp(player->get_hp());

            auto server_message = m_messages.add_vec_messages();
            server_message->set_type(trans::ServerToUserMessage::UpdatePlayer);
            server_message->set_allocated_upd_msg(update_message);

            for (size_t j = 0; j < m_objects.size(); ++j) {
                if (m_objects[j]->get_id() == player->get_id()) {
                    m_objects.erase(m_objects.begin() + j);
                }
            }
        }
    }
    // проходимся по вектору пуль и обновляем координатыa
    for (auto &bullet: m_bullets) {
        if (!((bullet->get_position().x > win_lenght) || (bullet->get_position().y > win_height) ||
              (bullet->get_position().x < 0) ||
              (bullet->get_position().y < 0)) && bullet->is_alive()) { //условие "исчесновения пули"
            bullet->update(dt, m_objects);
            //std::cout << " JOE\n";

            auto *update_message_bul = new trans::UpdateBulletMessage;
            update_message_bul->set_id(bullet->get_id());
            update_message_bul->set_hp(1); //условие исчезновения
            update_message_bul->set_x(bullet->get_position().x);
            update_message_bul->set_y(bullet->get_position().y);
            update_message_bul->set_name(n_bullet); //название объекта

            auto server_message = m_messages.add_vec_messages();
            server_message->set_type(trans::ServerToUserMessage::UpdateBullet);
            server_message->set_allocated_ub_msg(update_message_bul);
        } else {
            auto *update_message_bul = new trans::UpdateBulletMessage;
            update_message_bul->set_id(bullet->get_id());
            update_message_bul->set_hp(0); //условие жизни
            update_message_bul->set_x(bullet->get_position().x);
            update_message_bul->set_y(bullet->get_position().y);
            update_message_bul->set_name(n_bullet);

            auto server_message = m_messages.add_vec_messages();
            server_message->set_type(trans::ServerToUserMessage::UpdateBullet);
            server_message->set_allocated_ub_msg(update_message_bul);
        }

    }
    int count_enemies = 3;
    while (m_enemies.size() < count_enemies) {
        float x = 50;
        float y = 50;
        float dist = win_lenght / count_enemies;
        while (x < win_lenght) {
            add_enemy(x, y);
            x += dist;
        }
        x -= dist;
        y += dist;
        while (y < win_height) {
            add_enemy(x, y);
            y += dist;
        }
        y -= dist;
        x -= dist;
        while (x > 0) {
            add_enemy(x, y);
            x -= dist;
        }
        x += dist;
        y -= dist;
        while (y > 50) {
            add_enemy(x, y);
            y -= dist;
        }
    }
    notify_all();
}

bool Session::is_end() {
    return m_users.empty();
}

sf::Uint64 Session::get_id() const {
    return m_id;
}

void Session::add_enemy(float bot_x, float bot_y) {
    std::cout << "BOT_ADDED!!!\n";
    auto bot = std::make_shared<Enemy>();
    int count = rand() % m_users.size();

    bot->set_position(bot_x, bot_y);
    bot->set_target(count);

    //std::cout << "COUNT IS " << count << " SIZE IS " << m_users.size() << std::endl;

    m_enemies.push_back(bot);
    m_objects.push_back(bot);
    auto new_bot_message = new trans::NewBotMessage;
    new_bot_message->set_id(bot->get_id());
    new_bot_message->set_x(bot->get_position().x);
    new_bot_message->set_y(bot->get_position().y);
    new_bot_message->set_hp(bot->get_hp());
    new_bot_message->set_map_name(this->map_name);
    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_n_bot_msg(new_bot_message);
    server_message->set_type(trans::ServerToUserMessage::NewBot);
}

void Session::add_user(UserPtr user) {
    std::cout << "NEW PLAYER!!!\n";
    auto player = std::make_shared<Player>();

    //фикс баги с появлением в ком-то
    while (player->is_collide(m_objects, player->get_rect(), player->get_id())) {
        player->set_position({player->get_position().x + 10, player->get_position().y + 10});
    }

    player->add_land_obj(m_land_objects);
    m_users[user] = player;

    m_objects.push_back(player);

    auto new_player_message = new trans::NewPlayerMessage;
    new_player_message->set_id(player->get_id());
    new_player_message->set_username(user->get_username());
    new_player_message->set_x(player->get_position().x);
    new_player_message->set_y(player->get_position().y);
    new_player_message->set_map_name(this->map_name);
    new_player_message->set_hp(player->get_hp());

    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_np_msg(new_player_message);
    server_message->set_type(trans::ServerToUserMessage::NewPlayer);

}

void Session::add_bullet(PlayerPtr player, float x, float y, Direction b_dir, short weapon) {
    //функция аналогична с добавлением игрока за исключением того, что мы тут создаем вектор пуль, который автономно обрабатывается на сервере
    auto bullet = std::make_shared<Bullet>(sf::Vector2(x + 25, y + 25), b_dir, player->get_id());

    m_bullets.push_back(bullet);


    auto new_bullet_message = new trans::NewBulletMessage;

    new_bullet_message->set_p_id(player->get_id()); //возможно рудиментарное действие, но пока пусть останется
    new_bullet_message->set_id(bullet->get_id());
    new_bullet_message->set_x(x);
    new_bullet_message->set_y(y);
    new_bullet_message->set_name(n_bullet);
    new_bullet_message->set_hp(bullet->get_hp());


    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_nb_msg(new_bullet_message);
    server_message->set_type(trans::ServerToUserMessage::NewBullet);


    //std::cout << "BOOM BOOM :)\n";
}

void Session::notify_all() {
    sf::Packet packet;
    packet << m_messages;

    for (auto &m_user: m_users) {
        m_user.first->send_packet(packet);
    }

    m_messages.clear_vec_messages();
    // TODO: check user connection: if sending fails -> remove that user from m_users + add send DeletePlayerMessage to all
}

std::string &Session::get_map() {
    return map_name;
}

