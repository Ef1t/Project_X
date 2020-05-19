//
// Created by tsv on 18.04.19.
//

#include <iostream>

#include "Session.h"
#include "messages/ServerToUserMessage.h"

sf::Uint64 Session::next_id = 10;

Session::Session()
        : m_id(next_id++), m_users(), m_messages() {
}

void Session::update(float dt) {
    for (auto &m_user : m_users) {
        sf::Packet packet;
        auto &user = m_user.first;
        auto &player = m_user.second;
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
                                       message.direction().right(), message.direction().down()};
                player->apply(dir, direction);
            }
            if (message.type() == trans::UserToServerMessage::Wall) {
                m_objects.push_back(std::make_shared<Wall>(message.rect().x_1(),
                                                           message.rect().y_1(),
                                                           message.rect().x_2(),
                                                           message.rect().y_2(),
                                                           "Wall"));
            }
        }
        user->receive_socket(socket);
    }
    for (auto &item: m_users) {
        auto &player = item.second;
        player->update(dt * 10, m_objects);

        auto *direction = new trans::UpdatePlayerMessage::Direction;
        direction->set_up(player->get_route().up);
        direction->set_down(player->get_route().down);
        direction->set_left(player->get_route().left);
        direction->set_right(player->get_route().right);

        auto *update_message = new trans::UpdatePlayerMessage;
        update_message->set_id(player->get_id());
        update_message->set_x(player->get_position().x);
        update_message->set_y(player->get_position().y);
        update_message->set_allocated_direction(direction);

        auto server_message = m_messages.add_vec_messages();
        server_message->set_type(trans::ServerToUserMessage::UpdatePlayer);
        server_message->set_allocated_upd_msg(update_message);

    }

    notify_all();
}

bool Session::is_end() {
    return m_users.empty();
}

sf::Uint64 Session::get_id() const {
    return m_id;
}

void Session::add_user(UserPtr user) {
    std::cout << "NEW PLAYER!!!\n";
    auto player = std::make_shared<Player>();
    m_users[user] = player;

    auto new_player_message = new trans::NewPlayerMessage;
    new_player_message->set_id(player->get_id());
    new_player_message->set_username(user->get_username());
    new_player_message->set_x(player->get_position().x);
    new_player_message->set_y(player->get_position().y);
    new_player_message->set_map_name(this->map_name);

    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_np_msg(new_player_message);

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

