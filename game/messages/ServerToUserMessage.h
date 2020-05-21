//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SERVERTOUSERMESSAGE_H
#define GAME_SERVERTOUSERMESSAGE_H


#include <SFML/Network/Packet.hpp>
#include <SFML/System/Vector2.hpp>
#include "messages/UserToServerMessage.h"

#include <string>
#include <vector>
#include <variant>
#include "transition.pb.h"

struct NewPlayerMessage {
    sf::Uint64 id;
    std::string username;
    float x;
    float y;
    std::string map_name;
    Direction route;
};

sf::Packet& operator<<(sf::Packet& packet, const NewPlayerMessage& message);

sf::Packet& operator>>(sf::Packet& packet, NewPlayerMessage& message);


struct UpdatePlayerMessage {
    sf::Uint64 id;
    float x;
    float y;
    Direction route;
};

sf::Packet& operator<<(sf::Packet& packet, const UpdatePlayerMessage& message);

sf::Packet& operator>>(sf::Packet& packet, UpdatePlayerMessage& message);


struct ServerToUserMessage {
    enum MessageType {
        NewPlayer = 0,
        UpdatePlayer,
    };

    MessageType type;
    std::variant<NewPlayerMessage, UpdatePlayerMessage> value;
};

sf::Packet& operator<<(sf::Packet& packet, const ServerToUserMessage& message);

sf::Packet& operator>>(sf::Packet& packet, ServerToUserMessage& message);

sf::Packet& operator<<(sf::Packet& packet, const trans::ServerToUserMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::ServerToUserMessage& message);


struct ServerToUserVectorMessage {
    std::vector<ServerToUserMessage> messages;
};

sf::Packet& operator<<(sf::Packet& packet, const ServerToUserVectorMessage& message);

sf::Packet& operator>>(sf::Packet& packet, ServerToUserVectorMessage& message);

sf::Packet& operator<<(sf::Packet& packet, const trans::ServerToUserVectorMessage& message);

sf::Packet& operator>>(sf::Packet& packet, trans::ServerToUserVectorMessage& message);


#endif //GAME_SERVERTOUSERMESSAGE_H
