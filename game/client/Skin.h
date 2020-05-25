//
// Created by tsv on 18.04.19.
//

#ifndef GAME_SKIN_H
#define GAME_SKIN_H


#include "Object.h"

#include <SFML/Graphics.hpp>

#include <string>

#include "Client.h"

using namespace sf;

class Skin  {
public:
    Skin (std::string path);

    Skin();


//protected:
    sf::Image heroimage; 
    sf::Texture herotexture;
    sf::Sprite herosprite;
    sf::Clock clock;
    float current_frame;
    float time = clock.getElapsedTime().asMicroseconds();

    void go_texture(Direction dir, float time, float& current_frame, Skin& m_actor);

    void go_texture_enemy(Direction dir, float time, float& current_frame, Skin& m_actor);


};


#endif //GAME_SKIN_H
