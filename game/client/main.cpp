//
// Created by tsv on 18.04.19.
//

#include "Client.h"
#include "Menus.h"

#include <iostream>
void usage() {
    std::cerr << "Usage: ./client <username> <host> <port> (create <map_name> | join <lobby_num>)" << std::endl;
}

std::string username_str;
std::string host_str;
std::string port_str;
std::string command_str;
std::string map_str;
std::string lobby_str;




int main(int ac, const char* av[]) {
    bool withMenu = true;  // To operate with arguments - set the value to false
    if (!withMenu) {
        if (ac < 5) {
            usage();
            return -1;
        }

        Client client;
        username_str = av[1];
        host_str = av[2];
        port_str = av[3];
        command_str = av[4];
        lobby_str = av[5];
        //menuInit(client.get_window(), username_str, host_str, port_str, command_str, lobby_str);

        std::cout << "username: " << username_str << std::endl;

        auto username = std::string(username_str);
        auto host = std::string(host_str);
        auto port = static_cast<unsigned short>(std::stoul(port_str));

        client.set_config(host, port, username);

        if (command_str == "create") {
            //auto map_name = std::string(av[5]);
            auto map_name = std::string("map.tmx");
            client.create_session(map_name);
        } else if (command_str == "join") {
            //auto session_id = static_cast<sf::Uint64>(std::stoul(std::string(av[5])));
            auto session_id = static_cast<sf::Uint64>(std::stoul(lobby_str));
            client.join_to(session_id);
        } else {
            usage();
            return -1;
        }

        return client.run();
    }
    //music.setLoop(true);

  //  sf::SoundBuffer buffer;
    //buffer.loadFromFile("/home/yaroslav/X/Project_X/game/client/sounds/shoot.ogg");
    //sf::Sound sound;
    //sound.setBuffer(buffer);
    //sound.play();


    Client client;
    int join_error = 0;
    start:
    menuInit(client.get_window(), username_str, host_str, port_str, command_str, lobby_str, join_error);

    //menuDeath(client.get_window(), 100);
    if (command_str == "exit") {
        client.get_window().close();
        return EXIT_SUCCESS;
    }
    //menuDeath(client.get_window());

    std::cout << "username: " << username_str << std::endl;

    auto username = std::string(username_str);
    auto host = std::string(host_str);
    auto port = static_cast<unsigned short>(std::stoul(port_str));

    try {
        client.set_config(host, port, username);
    } catch (const std::exception& err) {
        goto start;
    }

    if (command_str == "create") {
        //auto map_name = std::string(av[5]);
        auto map_name = std::string("map.tmx");
        client.create_session(map_name);
        menuLobby(client.get_window(), client);

    } else if (command_str == "join") {
        //auto session_id = static_cast<sf::Uint64>(std::stoul(std::string(av[5])));
        auto session_id = static_cast<sf::Uint64>(std::stoul(lobby_str));
        if (client.join_to(session_id)) {
            join_error = 1;
            goto start;
        }
        menuLobby(client.get_window(), client);
    } else {
        usage();
        return -1;
    }

    sf::Music music;
    music.openFromFile("../../client/music/SuperMusic.wav");
    music.play();
    music.setVolume(3);

    return client.run();
}