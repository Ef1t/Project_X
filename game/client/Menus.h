//
// Created by denis on 21.05.2020.
//

#ifndef GAME_MENUS_H
#define GAME_MENUS_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void menuInit(sf::RenderWindow &window, std::string& username_str, std::string& host_str, std::string& port_str, std::string& command_str, std::string& lobby_str);

void menuDeath(sf::RenderWindow &window);

#endif //GAME_MENUS_H
