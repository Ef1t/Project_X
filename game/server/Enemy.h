//
// Created by ef1t on 16.05.2020.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "messages/UserToServerMessage.h"
#include <math.h>

const float ENEMY_VELOCITY = 5.0f;

class Enemy : public GameObject {
public:
    explicit Enemy(const sf::Vector2f& position = sf::Vector2f{50.0f, 50.0f});

    void movement(float dt, float tempX, float tempY);
    void update(float dt) override;
    const sf::Vector2f get_position() const;

private:
    sf::Vector2f m_position;
    float m_velocity;

    //Direction m_route; // Players route

};
using EnemyPtr = std::shared_ptr<Enemy>;


#endif //GAME_ENEMY_H
