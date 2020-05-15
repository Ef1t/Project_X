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
    return m_position;
}

const Direction Player::get_route() {
    return m_route;
}

void Player::apply(sf::Vector2f diretcion, Direction dir) {
    m_direction = diretcion; // сделать вектор игроков
    m_route = dir;
}

