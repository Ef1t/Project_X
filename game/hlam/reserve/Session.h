//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "Player.h"
#include "Bullet.h"
#include "messages/ServerToUserMessage.h"
#include "messages/UserToServerMessage.h"

#include <map>
#include <memory>
#include "common/User.h"
#include "transition.pb.h"

//using Users = std::map<UserPtr, PlayerPtr>;
//using Bullets = std::map<UserPtr, BulletPtr>;

using Users = std::map<UserPtr, GameObjectPtr>;

class Session {
public:
    Session();

    void update(float dt);

    bool is_end();

    sf::Uint64 get_id() const;

    void add_user(UserPtr user);

    void add_bullet(UserPtr user,sf::Uint64 id, float x, float y, Direction b_dir);

    std::string& get_map();

private:
    static sf::Uint64 next_id;
    sf::Uint64 m_id;
    Users m_users;
    //Bullets m_bullets;
    std::string map_name;
    trans::ServerToUserVectorMessage m_messages;
    std::vector<BulletPtr> m_bullets;

    void notify_all();
};


using SessionPtr = std::shared_ptr<Session>;

#endif //GAME_SESSION_H
