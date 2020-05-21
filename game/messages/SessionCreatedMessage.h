//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SESSIONCREATEDMESSAGE_H
#define GAME_SESSIONCREATEDMESSAGE_H

#include <SFML/Network/Packet.hpp>
#include "transition.pb.h"

struct SessionCreatedMessage {
    sf::Uint64 session_id;
};

sf::Packet& operator<<(sf::Packet& packet, const trans::SessionCreatedMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::SessionCreatedMessage& message);

#endif //GAME_SESSIONCREATEDMESSAGE_H
