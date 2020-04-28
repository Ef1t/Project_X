//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "ServerToUserMessage.h"

// TODO: implement me

// We cant just simple send Vector2f via packet. So we send X and Y differently to the packet.
// variant FIXME: SHOLD WE USE PROTOBUF FOR THAT?

// NewPlayerMessage
sf::Packet& operator<<(sf::Packet& packet, const NewPlayerMessage& message) {
    return packet << message.id << message.username << message.x << message.y;
}

sf::Packet& operator>>(sf::Packet& packet, NewPlayerMessage& message) {
    return packet >> message.id >> message.username >> message.x >> message.y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UpdatePlayerMessage
sf::Packet& operator<<(sf::Packet& packet, const UpdatePlayerMessage& message) {
    return packet << message.id << message.x << message.y;
}

sf::Packet& operator>>(sf::Packet& packet, UpdatePlayerMessage& message) {

    return packet >> message.id >> message.x >> message.y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ServerToUserMessage
sf::Packet& operator<<(sf::Packet& packet, const ServerToUserMessage& message) {
    packet << message.type;

    NewPlayerMessage msg_new;
    UpdatePlayerMessage msg_upd;
    switch (message.type) {
        case (ServerToUserMessage::NewPlayer):
            msg_new = std::get<NewPlayerMessage>(message.value);
            packet << msg_new;
            break;
        case (ServerToUserMessage::UpdatePlayer):
            msg_upd = std::get<UpdatePlayerMessage>(message.value);
            packet << msg_upd;
            //std::cout << "SENDED" << " X " << msg_upd.x << "Y " << msg_upd.y << "\n";
            break;
        default:
            break;
    }

    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, ServerToUserMessage& message) {
    int messageType = 0;
    packet >> messageType;
    message.type = static_cast<ServerToUserMessage::MessageType>(messageType);

    NewPlayerMessage tmp_new;
    UpdatePlayerMessage tmp_update;
    switch (message.type) {
        case (ServerToUserMessage::NewPlayer):
            packet >> tmp_new;
            std::cout << "NEW" << " ID " << tmp_new.id << " X " << tmp_new.x << " Y " << tmp_new.y << "\n",
            message.value = tmp_new;
            break;
        case (ServerToUserMessage::UpdatePlayer):
            packet >> tmp_update;
            //std::cout << "RECEIVE" << " X " << tmp_update.x << " Y " << tmp_update.y << "\n",
            message.value = tmp_update;
        default:
            break;
    }

    return packet;
}


//ServerToUserVectorMessage
sf::Packet& operator<<(sf::Packet& packet, const ServerToUserVectorMessage& message) {
    packet.clear();
    int size = message.messages.size();
    packet << size;  // Firstly we should know size of array, then send an elements of the array
    for (ServerToUserMessage const& letter: message.messages) {
        packet << letter;
    }

    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, ServerToUserVectorMessage& message) {
    message.messages.clear();
    int arr_size;
    packet >> arr_size;  // Firstly we should know size of array, then receive an elements of the array
    for (int i = 0; i < arr_size; i++) {
        ServerToUserMessage letter;
        packet >> letter;
        message.messages.push_back(letter);
    }

    return packet;
}