//
// Created by tsv on 18.04.19.
//
#include "UserToServerMessage.h"

sf::Packet& operator<<(sf::Packet& packet, const trans::UserToServerMessage& message) {
    std::string code;
    message.SerializeToString(&code);
    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::UserToServerMessage& message) {
    std::string code;
    packet >> code;

    message.ParseFromString(code);

    return packet;
}


sf::Packet& operator<<(sf::Packet& packet, const trans::UserToServerLobbyWaitingMessage& message) {
    std::string code;
    message.SerializeToString(&code);
    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::UserToServerLobbyWaitingMessage& message) {
    std::string code;
    packet >> code;

    message.ParseFromString(code);

    return packet;
}

//sf::Packet &operator<<(sf::Packet &packet, const trans::UserToServerVectorMessage &message) {
//    std::string code;
//    message.SerializeToString(&code);
//
//    return packet << code;
//}
//
//sf::Packet &operator>>(sf::Packet &packet, trans::UserToServerVectorMessage &message) {
//    std::string code;
//    packet >> code;
//    message.ParseFromString(code);
//
//    return packet;
//}
