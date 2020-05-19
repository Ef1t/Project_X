//
// Created by ef1t on 16.05.2020.
//

#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position)
        : m_position(position)
        , m_velocity(ENEMY_VELOCITY) {
}

const sf::Vector2f Enemy::get_position() const {
    return m_position;
}

void Enemy::movement(float dt, float tempX, float tempY) {
    double dist = sqrt((tempX - m_position.x) * (tempX - m_position.x) + (tempY - m_position.y) * (tempY - m_position.y));
    if (dist > 2) {
        m_position.x += m_velocity * dt * (tempX - m_position.x) / dist;
        m_position.y += m_velocity * dt * (tempY - m_position.y) / dist;
    }
    puts("x");
    std::cout<<m_position.x;
    puts("y");
    std::cout<<m_position.y;
}

void Enemy::update(float dt){

}


