//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include "Player.h"
#include "messages/ServerToUserMessage.h"
#include "messages/UserToServerMessage.h"

#include <map>
#include <memory>
#include "common/User.h"

using Users = std::map<UserPtr, PlayerPtr>;

class Session {
public:
    Session();

    void update(float dt);

    bool is_end();

    sf::Uint64 get_id() const;

    void add_user(UserPtr user);

private:
    static sf::Uint64 next_id;
    sf::Uint64 m_id;
    Users m_users;
    ServerToUserVectorMessage m_messages;

    void notify_all();
};


using SessionPtr = std::shared_ptr<Session>;

#endif //GAME_SESSION_H
