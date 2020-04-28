//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(const sf::Vector2f& position)
        : m_position(position)
        , m_direction{0.0f, 0.0f}
        , m_velocity(PLAYER_VELOCITY) {
}

void Player::update(float dt) {
    m_position += m_direction * (m_velocity * dt);
}

const sf::Vector2f Player::get_position() const {
    //std::cout << m_position.x << " " << m_position.y << "\n";
    return m_position;
}

void Player::apply(sf::Vector2f diretcion) {
    m_direction = diretcion;
}

