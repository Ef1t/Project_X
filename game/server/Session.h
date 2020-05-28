//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <map>
#include <memory>
#include <string_view>

#include "Wall.h"
#include "Lava.h"
#include "Spike.h"
#include "Player.h"
#include "Bullet.h"
#include "GameObject.h"
#include "messages/ServerToUserMessage.h"
#include "messages/UserToServerMessage.h"
#include "common/User.h"
#include "transition.pb.h"
#include "Enemy.h"

#define win_height 2560
#define win_lenght 2560



//using Users = std::map<UserPtr, PlayerPtr>;
//using Bullets = std::map<UserPtr, BulletPtr>;

using Users = std::map<UserPtr, PlayerPtr>;

class Session {
public:
    Session(std::string_view map_name);

    void update(float dt);

    bool is_end();

    sf::Uint64 get_id() const;

    int add_user(UserPtr user);

    void add_enemy();

    void add_bullet(PlayerPtr player, float x, float y, Direction b_dir, short weapon, short number);

    void add_enemy(float bot_x, float bot_y);

    void add_player();
    void remove_player();
    sf::Uint64 get_players();

    Users get_useres();

    std::string& get_map();

    bool lobbyWait;

    static sf::Uint64 next_id;

    bool fool_init;

private:
    sf::Uint64 m_id;
    sf::Uint64 m_players;
    Users m_users;
    //Bullets m_bullets;
    std::string map_name;
    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::vector<std::shared_ptr<GameObject>> m_land_objects;
    trans::ServerToUserVectorMessage m_messages;

    std::vector<BulletPtr> m_bullets;
    std::vector<EnemyPtr> m_enemies;


    void notify_all();

};


using SessionPtr = std::shared_ptr<Session>;

#endif //GAME_SESSION_H
