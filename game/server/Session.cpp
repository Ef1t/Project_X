//
// Created by tsv on 18.04.19.
//

#include "Session.h"
#include "messages/ServerToUserMessage.h"
#include "iostream"

sf::Uint64 Session::next_id = 10;

Session::Session()
        : m_id(next_id++)
        , m_users()
        , m_messages() {
}

void Session::update(float dt) {
    for (auto & m_user : m_users) {
        sf::Packet packet;
        auto& user = m_user.first;
        auto& player = m_user.second;
        UserSocket socket = user->get_socket();
        if (socket->receive(packet) == sf::Socket::Done) {
            UserToServerMessage message;
            packet >> message;
            switch (message.type) {
                case UserToServerMessage::Move:
                    sf::Vector2f dir;
                    if (message.direction.up) {
                        dir.y--;
                    }
                    if (message.direction.down) {
                        dir.y++;
                    }
                    if (message.direction.left) {
                        dir.x--;
                    }
                    if (message.direction.right) {
                        dir.x++;
                    }
                    player->apply(dir, message.direction); // добавил хранение направления
                    //std::cout<<player->get_route().up<<" up \n";
            }
//            std::cout << message.direction.up << message.direction.down << message.direction.left
//                      << message.direction.right << "\n";
        }
        user->receive_socket(socket);
    }
    for (auto& item: m_users) {
        auto& player = item.second;
        player->update(dt * 20);

        UpdatePlayerMessage update_player_message = {player->get_id(), player->get_position().x, player->get_position().y, player->get_route()}; //запихнуть направление сюда
        //std::cout<<player->get_route().up<<" UP message \n"; //добавил get_route
        ServerToUserMessage server_message = {ServerToUserMessage::UpdatePlayer, update_player_message};
        m_messages.messages.push_back(server_message);
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


    NewPlayerMessage new_player_message = {
            player->get_id(), user->get_username(), player->get_position().x, player->get_position().y, this->map_name, player->get_route() //добавил get_route
    };
    //std::cout<<player->get_route().up<<" UP message NEW \n";
    ServerToUserMessage server_message = {.type=ServerToUserMessage::NewPlayer};
    server_message.value = new_player_message;

    m_messages.messages.push_back(server_message);
}

void Session::notify_all() {
    sf::Packet packet;
    packet << m_messages;

//    for (const ServerToUserMessage& message: m_messages.messages) {
//        if (message.type == ServerToUserMessage::NewPlayer) {
//            NewPlayerMessage message_new = std::get<NewPlayerMessage>(message.value);
//            //m_objects.push_back(std::make_shared<Player>(message_new.id, message_new.username, message_new.position));
//            std::cout << "NEW" << message_new.id << " " << message_new.x << " " << message_new.y << "\n";
//        }
//        else if (message.type == ServerToUserMessage::UpdatePlayer) {
//            UpdatePlayerMessage message_upd = std::get<UpdatePlayerMessage>(message.value);
//            std::cout << "UPD" << message_upd.id << " " << message_upd.x << " " << message_upd.y << "\n";
//            }
//        }

    for (auto & m_user: m_users) {
        m_user.first->send_packet(packet);
    }
    m_messages.messages.clear();
    // TODO: check user connection: if sending fails -> remove that user from m_users + add send DeletePlayerMessage to all
}

std::string &Session::get_map() {
    return map_name;
}

