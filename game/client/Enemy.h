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
        Enemy(sf::Uint64 id, const sf::Vector2f& position, int hp);

        void draw(sf::RenderWindow& window, float time, float& current_frame) override;

        void set_position(const sf::Vector2f& position) override;

        void draw_stat(sf::RenderWindow& window) override;

        void set_direction(const Direction dir) override;

        void set_hp(int hp) override ;

        void update_dir_enemy(float x, float y) override;



private:
    //Skin m_actor;
    Skin mr_enemy;

public:

};

#endif //GAME_ENEMY_H
