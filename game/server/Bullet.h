//
// Created by yaroslav on 16.05.2020.
//
#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#define bullet_velocity 10.0

class Bullet: public GameObject {
public:
    Bullet(sf::Vector2f position, Direction dir, short p_id);

   explicit Bullet(short name);

    void update(float dt) override;

    const sf::Vector2f get_position() const override ;

    void apply(sf::Vector2f diretcion, Direction dir) override ;


    const Direction get_route() override ;

    //void add_bullet();

private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;
    Direction b_dir;  // траектория пули
    short player_id;

};

using BulletPtr = std::shared_ptr<Bullet>;
#endif //GAME_BULLET_H
