//
// Created by tsv on 18.04.19.
//
#include "UserInitMessage.h"

sf::Packet& operator<<(sf::Packet& packet, const trans::UserInitMessage& message) {
    std::string code;
    message.SerializeToString(&code);
    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::UserInitMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}