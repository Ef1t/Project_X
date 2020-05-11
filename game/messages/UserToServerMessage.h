//
// Created by tsv on 18.04.19.
//

#ifndef GAME_USERTOSERVERMESSAGE_H
#define GAME_USERTOSERVERMESSAGE_H

#include <SFML/Network/Packet.hpp>
#include <memory>

struct Direction {
    bool up;
    bool left;
    bool right;
    bool down;
};

sf::Packet& operator<<(sf::Packet& packet, const Direction& direction);

sf::Packet& operator>>(sf::Packet& packet, Direction& direction);


struct UserToServerMessage {
    enum MessageType {
        Move = 0,
    };

    MessageType type;

    union {
        Direction direction;
    };
};



sf::Packet& operator<<(sf::Packet& packet, const UserToServerMessage& message);

sf::Packet& operator>>(sf::Packet& packet, UserToServerMessage& message);

//std::vector<UserToServerMessage> UTSM_vector;
//using UTSM_PTR = std::shared_ptr<UserToServerMessage>;
using UTSM_vector = std::vector<UserToServerMessage>;

#endif //GAME_USERTOSERVERMESSAGE_H
