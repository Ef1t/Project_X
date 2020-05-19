//
// Created by ef1t on 16.05.2020.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "Object.h"
#include "TmxLevel.h"

#include "Skin.h"

#include <SFML/Graphics/CircleShape.hpp>

#include <string>

class Enemy : public Object, Skin {
public:
        Enemy(sf::Uint64 id, const sf::Vector2f& position);

        void draw(sf::RenderWindow& window, float time, float& current_frame) override;

        void set_position(const sf::Vector2f& position) override;

        void draw_stat(sf::RenderWindow& window) override;
//
//    void set_direction(Direction dir) override;

private:
    //Skin m_actor;
    sf::CircleShape shape;
public:

};

#endif //GAME_ENEMY_H
