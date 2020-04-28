//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SESSIONCREATEDMESSAGE_H
#define GAME_SESSIONCREATEDMESSAGE_H

#include <SFML/Network/Packet.hpp>

struct SessionCreatedMessage {
    sf::Uint64 session_id;
};

sf::Packet& operator<<(sf::Packet& packet, const SessionCreatedMessage& message);

sf::Packet& operator>>(sf::Packet& packet, SessionCreatedMessage& message);

#endif //GAME_SESSIONCREATEDMESSAGE_H
