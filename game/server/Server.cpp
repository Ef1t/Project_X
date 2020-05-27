//
// Created by tsv on 18.04.19.
//

#include "Server.h"
#include "common/User.h"
#include "messages/UserInitMessage.h"

#include <SFML/System/Clock.hpp>

#include <cstring>
#include <algorithm>
#include <iostream>
#include <messages/SessionCreatedMessage.h>


Server::Server(unsigned short port)
        : m_port(port)
        , m_sessions()
        , m_listener() {
    if (m_listener.listen(m_port) != sf::Socket::Done) {
        throw std::runtime_error(std::strerror(errno));
    }
    m_listener.setBlocking(false);
}

Server::~Server() {
    m_listener.close();
}

[[noreturn]] int Server::run() {
    auto clock = sf::Clock();
    sf:: Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time TimeSinceLastEvent = sf::Time::Zero;
    while (true) {
        accept_new_user();

        TimeSinceLastEvent += clock.restart();
        while (TimeSinceLastEvent > TimePerFrame) {
            for (auto session = m_sessions.begin(); session != m_sessions.end(); ++session) {
                if ((*session)->is_end()) {
                    session = m_sessions.erase(session);
                } else {
                    if ((*session)->lobbyWait) {
                        receiveWaitingStatus(*session);
                        sendUsersConnected(*session);
                    } else {
                        (*session)->update(TimeSinceLastEvent.asSeconds());
                    }
                }
            }
            TimeSinceLastEvent -= TimePerFrame;
        }
    }
}

void Server::accept_new_user() {
    UserSocket socket = std::make_unique<sf::TcpSocket>();

    if (m_listener.accept(*socket) == sf::Socket::Done) {
        sf::Packet packet;
        socket->receive(packet);
        // FIXME: if user stuck - server stuck too

        trans::UserInitMessage message;
        packet >> message;

        std::cout << "New user: " << message.username() << " " << static_cast<int>(message.action()) << " "
                  << message.session_id() << std::endl;

        UserPtr user = std::make_shared<User>(message.username(), std::move(socket));

        switch (message.action()) {
            case trans::UserInitMessage::Create: {
                SessionPtr session = std::make_shared<Session>(message.map_name());
                //session->get_map() = message.map_name();
                session->add_user(user);

                m_sessions.push_back(session);

                trans::SessionCreatedMessage response;
                response.set_session_id(session->get_id());

                packet.clear();
                packet << response;

                user->send_packet(packet);

                break;
            }
            case trans::UserInitMessage::Join: {
                auto session = std::find_if(
                        m_sessions.begin(), m_sessions.end(),
                        [&message = std::as_const(message)](const SessionPtr& session) -> bool {
                            return session->get_id() == message.session_id();
                        }
                );

                trans::NewPlayerMessage np_message;
                if (session == m_sessions.end() || !(*session)->lobbyWait) {
                    np_message.set_map_name("JOIN_ERR");
                    packet.clear();
                    packet << np_message;
                    user->send_packet(packet);
                    break;
                }

                int id = (*session)->add_user(user);

                np_message.set_id(id);
                packet.clear();
                packet << np_message;
                user->send_packet(packet);

                break;
            }
        }
    }

//    for(auto session: m_sessions) {
//        sf::Packet packet;
//        trans::ServerToUserLobbyWaitingMessage msg;
//        std::string names;
//        if (session->lobbyWait) {
//            for(auto user: session->get_useres()) {
//                names += user.first->get_username() + "\n";
//            }
//            msg.set_names(names);
//            packet << msg;
//            for(auto user: session->get_useres()) {
//                user.first->send_packet(packet);
//            }
//        }
//    }
}

void Server::sendUsersConnected(std::shared_ptr<Session> session) {
    trans::ServerToUserLobbyWaitingMessage message;
    sf::Packet packet;
    std::string names;
    for (auto user: session->get_useres()) {
        names += user.first->get_username() + " is in lobby!\n";
    }
    message.set_names(names);
    message.set_waitingisover(!(session->lobbyWait));
    packet << message;
    int i = 0;
    for (auto user: session->get_useres()) {
        user.first->send_packet(packet);
        i++;
    }
    //std::cout << "CURRENT AMOUNT OF USERS " << i << std::endl;
}

void Server::receiveWaitingStatus(std::shared_ptr<Session> session) {
    trans::UserToServerLobbyWaitingMessage message;
    sf::Packet packet;
    //auto user = session->get_useres().begin()->first;
    for (auto user : session->get_useres()) {
        user.first->receive_packet(packet);
        packet >> message;
        if (message.waitingisover())
            session->lobbyWait = false;
    }
}
