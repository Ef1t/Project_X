//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <map>
#include <memory>

#include "Wall.h"
#include "Player.h"
#include "Bullet.h"
#include "GameObject.h"
#include "messages/ServerToUserMessage.h"
#include "messages/UserToServerMessage.h"
#include "common/User.h"
#include "transition.pb.h"
#include "Enemy.h"

#define win_height 1280
#define win_lenght 1280

//using Users = std::map<UserPtr, PlayerPtr>;
//using Bullets = std::map<UserPtr, BulletPtr>;

using Users = std::map<UserPtr, PlayerPtr>;

class Session {
public:
    Session();

    void update(float dt);

    bool is_end();

    sf::Uint64 get_id() const;

    void add_user(UserPtr user);

    void add_enemy();

    void add_bullet(PlayerPtr player, float x, float y, Direction b_dir);

    void add_enemy(float bot_x, float bot_y);

    std::string& get_map();

private:
    static sf::Uint64 next_id;
    sf::Uint64 m_id;
    Users m_users;
    //Bullets m_bullets;
    std::string map_name;
    std::vector<std::shared_ptr<GameObject>> m_objects;
    trans::ServerToUserVectorMessage m_messages;

    std::vector<BulletPtr> m_bullets;
    std::vector<EnemyPtr> m_enemies;


    void notify_all();

};


using SessionPtr = std::shared_ptr<Session>;

#endif //GAME_SESSION_H
