//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SERVER_H
#define GAME_SERVER_H


#include "Session.h"

#include <SFML/Network/TcpListener.hpp>

#include "messages/ServerToUserMessage.h"
#include "messages/UserToServerMessage.h"

#include <memory>
#include <string>
#include <vector>

using Sessions = std::vector<SessionPtr>;

class Server {
public:
    explicit Server(unsigned short port);

    ~Server();

    [[noreturn]] int run();

private:
    unsigned short m_port;
    Sessions m_sessions;
    sf::TcpListener m_listener;

    void accept_new_user();

    void sendUsersConnected(std::shared_ptr<Session> sesion);

    void receiveWaitingStatus(std::shared_ptr<Session> sesion);
};


#endif //GAME_SERVER_H
