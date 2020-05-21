//
// Created by ef1t on 16.05.2020.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "messages/UserToServerMessage.h"
#include <math.h>
#include "Collision.h"

const float ENEMY_VELOCITY = 30.0f;

 class Enemy : public GameObject, public Collision {
public:
    explicit Enemy(const sf::Vector2f& position = sf::Vector2f{50.f, 50.f});

    void movement(float dt, float tempX, float tempY, std::vector<std::shared_ptr<GameObject>> &objects);

    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) override;

    void apply(sf::Vector2f diretcion, Direction dir) override;

    const sf::Vector2f get_position() const override;

     void set_position(float new_x, float new_y);

    sf::FloatRect get_rect() override;

    const Direction get_route() override;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;

    //Direction m_route; // Players route

};
using EnemyPtr = std::shared_ptr<Enemy>;


#endif //GAME_ENEMY_H
