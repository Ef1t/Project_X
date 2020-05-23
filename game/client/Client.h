//
// Created by tsv on 18.04.19.
//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H


#include "messages/UserToServerMessage.h"
#include "messages/SessionCreatedMessage.h"
#include "messages/UserInitMessage.h"
#include "messages/ServerToUserMessage.h"

#include "transition.pb.h"
#include "common/User.h"
#include "Object.h"
#include "TmxLevel.h"
#include "View.h"
#include "Bullet.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

using Objects = std::vector<ObjectPtr>;

class Client {
public:
    Client(const std::string& host, unsigned short port, const std::string& username);

    void create_session(std::string map_name);

    void join_to(sf::Uint64 session_id);

    int run();

    void apply_dir_b();

private:
    UserPtr m_user;
    sf::RenderWindow m_window;
    Objects m_objects;
    Direction m_direction;
    Direction m_direction_bullet;
    TmxLevel m_level;
    bool is_map;
    View view;
    int this_player_id;
    bool is_creator;

    void process_events();

    void receive_from_server();

    void render(float time, float& dir);

    void send_to_server();

    void apply_messages(const trans::ServerToUserVectorMessage& messages);

    void send_obj_to_server(std::vector<TmxObject> &all_objects);

};


#endif //GAME_CLIENT_H
