//
// Created by tsv on 18.04.19.
//

#include "Client.h"

#include <iostream>
void usage() {
    std::cerr << "Usage: ./client <username> <host> <port> (create <map_name> | join <lobby_num>)" << std::endl;
}

int main(int ac, const char* av[]) {
    if (ac < 5) {
        usage();
        return -1;
    }

    auto username = std::string(av[1]);
    auto host = std::string(av[2]);
    auto port = static_cast<unsigned short>(std::stoul(std::string(av[3])));
    Client client(host, port, username);

    auto cmd = std::string(av[4]);

    if (cmd == "create") {
        auto map_name = std::string(av[5]);
        client.create_session(map_name);
    } else if (cmd == "join") {
        auto session_id = static_cast<sf::Uint64>(std::stoul(std::string(av[5])));
        client.join_to(session_id);
    } else {
        usage();
        return -1;
    }

    return client.run();
}
