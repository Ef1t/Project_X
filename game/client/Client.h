//
// Created by tsv on 18.04.19.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H


#include "messages/UserToServerMessage.h"
#include "messages/SessionCreatedMessage.h"
#include "messages/UserInitMessage.h"
#include "messages/ServerToUserMessage.h"
#include "common/User.h"
#include "Object.h"
#include "TmxLevel.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

using Objects = std::vector<ObjectPtr>;

class Client {
public:
    Client(const std::string& host, unsigned short port, const std::string& username);

    void create_session(std::string map_name);

    void join_to(sf::Uint64 session_id);

    int run();

private:
    UserPtr m_user;
    sf::RenderWindow m_window;
    Objects m_objects;
    Direction m_direction;
    TmxLevel m_level;

    void process_events();

    void receive_from_server();

    void render();

    void send_to_server();

    void apply_messages(const ServerToUserVectorMessage& messages);
};


#endif //GAME_CLIENT_H
