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
#include <SFML/Audio.hpp>

#include <string>

using Objects = std::vector<ObjectPtr>;

class Client {
public:
    Client(const std::string& host, unsigned short port, const std::string& username);

    void create_session(std::string map_name);

    void join_to(sf::Uint64 session_id);

    int run();

    void apply_dir_b();

    void choise_of_weapon();

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
    FireDirection m_fire_dir;
    Weapon m_weapon;
    Weapon choise_weapon;

    void process_events();

    void receive_from_server();

    void render(float time, float& dir, float& dir_en);

    void send_to_server();

    void apply_messages(const trans::ServerToUserVectorMessage& messages);

    void send_obj_to_server(std::vector<TmxObject> &all_objects);

    void play_sound();



    sf::SoundBuffer buffer;
    //buffer.loadFromFile("/home/yaroslav/X/Project_X/game/client/sounds/shoot.ogg");
    sf::Sound sound;

};


#endif //GAME_CLIENT_H
