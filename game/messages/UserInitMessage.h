//
// Created by tsv on 18.04.19.
//

#ifndef GAME_USERINIT_H
#define GAME_USERINIT_H


#include <SFML/Network/Packet.hpp>

#include <string>
#include "transition.pb.h"


struct UserInitMessage {
    enum Action {
        Create = 0,
        Join,
    };

    Action action;
    std::string username;
    sf::Uint64 session_id;
    std::string map_name;
};

sf::Packet& operator<<(sf::Packet& packet, const trans::UserInitMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::UserInitMessage& message);

#endif //GAME_USERINIT_H
