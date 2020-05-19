//
// Created by tsv on 18.04.19.
//
#include "SessionCreatedMessage.h"

sf::Packet& operator<<(sf::Packet& packet, const SessionCreatedMessage& message) {
    return packet << message.session_id;
}

sf::Packet& operator>>(sf::Packet& packet, SessionCreatedMessage& message) {
    return packet >> message.session_id;
}

sf::Packet& operator<<(sf::Packet& packet, const trans::SessionCreatedMessage& message);

sf::Packet &operator<<(sf::Packet &packet, const trans::SessionCreatedMessage &message) {
    std::string code;
    message.SerializeToString(&code);
    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::SessionCreatedMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);
    return packet;
}