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
    sf::Music music;
    music.openFromFile("/home/yaroslav/X/Project_X/game/client/music/Overworld.wav");
    music.play();
    //music.setLoop(true);

  //  sf::SoundBuffer buffer;
    //buffer.loadFromFile("/home/yaroslav/X/Project_X/game/client/sounds/shoot.ogg");
    //sf::Sound sound;
    //sound.setBuffer(buffer);
    //sound.play();

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
