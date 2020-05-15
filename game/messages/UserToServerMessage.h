//
// Created by tsv on 18.04.19.
//

#ifndef GAME_USERTOSERVERMESSAGE_H
#define GAME_USERTOSERVERMESSAGE_H

#include <SFML/Network/Packet.hpp>
#include <memory>
#include "transition.pb.h"

struct Direction {
    bool up;
    bool left;
    bool right;
    bool down;
};

sf::Packet& operator<<(sf::Packet& packet, const trans::UserToServerMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::UserToServerMessage& message);

struct UserToServerMessage {
    enum MessageType {
        Move = 0,
    };

    MessageType type;

    union {
        Direction direction;
    };
};

using UTSM_vector = std::vector<UserToServerMessage>;

#endif //GAME_USERTOSERVERMESSAGE_H
