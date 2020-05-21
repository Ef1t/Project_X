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
#include "Menus.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

using Objects = std::vector<ObjectPtr>;

class Client {
public:
    Client();

    void set_config(const std::string& host, unsigned short port, const std::string& username);
    Client(const std::string& host, unsigned short port, const std::string& username, sf::RenderWindow &window);

    sf::RenderWindow& get_window();

    void create_session(std::string map_name);

    void join_to(sf::Uint64 session_id);

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
    bool is_creator;

    void process_events();

    void receive_from_server();

    void render(float time, float& dir);

    void send_to_server();

    void apply_messages(const trans::ServerToUserVectorMessage& messages);

    void send_obj_to_server(std::vector<TmxObject> all_objects);

};


#endif //GAME_CLIENT_H
