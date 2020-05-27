//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "ServerToUserMessage.h"

// NewPlayerMessage

sf::Packet& operator<<(sf::Packet& packet, const trans::NewBulletMessage& message) {
    std::string code;
    message.SerializeToString(&code);

    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::NewBulletMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}


sf::Packet& operator<<(sf::Packet& packet, const trans::ServerToUserLobbyWaitingMessage& message) {
    std::string code;
    message.SerializeToString(&code);

    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::ServerToUserLobbyWaitingMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NewPlayerMessage;

sf::Packet& operator<<(sf::Packet& packet, const trans::NewPlayerMessage& message) {
    std::string code;
    message.SerializeToString(&code);

    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::NewPlayerMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Packet& operator<<(sf::Packet& packet, const trans::UpdatePlayerMessage& message) {
    std::string code;
    message.SerializeToString(&code);

    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::UpdatePlayerMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::Packet& operator<<(sf::Packet& packet, const trans::ServerToUserMessage& message) {
    std::string code;
    message.SerializeToString(&code);

    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::ServerToUserMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, const trans::ServerToUserVectorMessage& message) {
    std::string code;
    message.SerializeToString(&code);

    return packet << code;
}

sf::Packet& operator>>(sf::Packet& packet, trans::ServerToUserVectorMessage& message) {
    std::string code;
    packet >> code;
    message.ParseFromString(code);

    return packet;
}