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
    bool fire;
};

struct FireDirection {
    bool f_up;
    bool f_left;
    bool f_right;
    bool f_down;
};

struct Weapon {
    bool pistol;
    bool automat;
    bool shotgun;
};

sf::Packet& operator<<(sf::Packet& packet, const trans::UserToServerMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::UserToServerMessage& message);


sf::Packet& operator<<(sf::Packet& packet, const trans::UserToServerLobbyWaitingMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::UserToServerLobbyWaitingMessage& message);





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

//struct UserToServerVectorMessage {
//    UTSM_vector messages;
//};
//
//sf::Packet& operator<<(sf::Packet& packet, const trans::UserToServerVectorMessage& message);
//
//sf::Packet& operator>>(sf::Packet& packet, trans::UserToServerVectorMessage& message);

#endif //GAME_USERTOSERVERMESSAGE_H
