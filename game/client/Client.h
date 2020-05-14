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

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include "transition.pb.h"

using Objects = std::vector<ObjectPtr>;

class Client {
public:
    Client(const std::string& host, unsigned short port, const std::string& username);

    void create_session(std::string map_name);

    void join_to(sf::Uint64 session_id);

    //void add_objects(std::vector<TmxObject> all_objects);

    int run();



private:
    UserPtr m_user;
    sf::RenderWindow m_window;
    Objects m_objects;
    Direction m_direction;
    TmxLevel m_level;
    bool is_map;
    View view;
    int this_player_id;

    void process_events();

    void receive_from_server();

    void render(float time, float& dir);

    void send_to_server();

    void apply_messages(const trans::ServerToUserVectorMessage& messages);


};


#endif //GAME_CLIENT_H
