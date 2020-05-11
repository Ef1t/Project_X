//
// Created by tsv on 18.04.19.
//

#include "Session.h"
#include "messages/ServerToUserMessage.h"
#include "iostream"
#include "transition.pb.h"

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
            //UserToServerMessage message;
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
                player->apply(dir);
            }
//            switch (message.type()) {
//                case UserToServerMessage::Move:
//                    sf::Vector2f dir;
//                    if (message.direction.up) {
//                        dir.y--;
//                    }
//                    if (message.direction.down) {
//                        dir.y++;
//                    }
//                    if (message.direction.left) {
//                        dir.x--;
//                    }
//                    if (message.direction.right) {
//                        dir.x++;
//                    }
//                    player->apply(dir);
//            }
//            std::cout << message.direction.up << message.direction.down << message.direction.left
//                      << message.direction.right << "\n";
        }
        user->receive_socket(socket);
    }
    for (auto& item: m_users) {
        auto& player = item.second;
        player->update(dt * 10);
        //auto *update_message = new trans::UpdatePlayerMessage;
        auto *update_message = new trans::UpdatePlayerMessage;

        update_message->set_id(player->get_id());
        update_message->set_x(player->get_position().x);
        update_message->set_y(player->get_position().y);

        auto server_message = m_messages.add_vec_messages();
        server_message->set_type(trans::ServerToUserMessage::UpdatePlayer);
        server_message->set_allocated_upd_msg(update_message);
        //server_message.set_type(trans::ServerToUserMessage::UpdatePlayer);
        //server_message.set_allocated_upd_msg(update_message);
        //UpdatePlayerMessage update_player_message = {player->get_id(), player->get_position().x, player->get_position().y};
        //ServerToUserMessage server_message = {ServerToUserMessage::UpdatePlayer, update_player_message};

        //m_messages.messages.push_back(server_message);
        //m_messages.add_vec_messages();
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


    auto new_player_message = new trans::NewPlayerMessage ;
    new_player_message->set_id(player->get_id());
    new_player_message->set_username(user->get_username());
    new_player_message->set_x(player->get_position().x);
    new_player_message->set_y(player->get_position().y);
//    NewPlayerMessage new_player_message = {
//            player->get_id(), user->get_username(), player->get_position().x, player->get_position().y
//    };

    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_np_msg(new_player_message);
    //ServerToUserMessage server_message = {.type=ServerToUserMessage::NewPlayer};
    //server_message.value = new_player_message;

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
    m_messages.clear_vec_messages();
    // TODO: check user connection: if sending fails -> remove that user from m_users + add send DeletePlayerMessage to all
}

