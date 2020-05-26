//
// Created by yaroslav on 16.05.2020.
//
#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "Collision.h"
#define pistolet 0
#define aut 1
#define drobovik 2

#define pistolet_dmg 3
#define aut_dmg 1
#define drobovik_dmg 3

#define bullet_velocity 450.0

class Bullet: public GameObject, public Collision {
public:
    Bullet(sf::Vector2f position, Direction dir, short p_id, short weap, short number);

    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) override;

    const sf::Vector2f get_position() const override ;

    void apply(sf::Vector2f diretcion, Direction dir) override ;

    const Direction get_route() override ;

    sf::FloatRect get_rect() override;

    short get_name_weapon();

    //void add_bullet();

    short bullet_number;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;
    Direction b_dir;  // траектория пули
    short player_id;
    short name_weapon;

};

using BulletPtr = std::shared_ptr<Bullet>;
#endif //GAME_BULLET_H
