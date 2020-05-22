//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include <math.h>

#include "Player.h"

Player::Player(const sf::Vector2f &position)
        : m_position(position)
        , m_direction{0.0f, 0.0f}
        , m_velocity(PLAYER_VELOCITY)
        , GameObject(n_player, n_player_hp, n_player_dmg) {}

void Player::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

    if (hp <= 0) {
        is_alive() = false;
        return;
    }

        // делаем нормальную скорость по диагонали
    float lenght = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
    if (lenght > 1) {
        m_direction.x /= sqrt(2);
        m_direction.y /= sqrt(2);
    }

    sf::Vector2f step = m_direction * (m_velocity * dt);

    step = real_step(step, m_direction, get_rect(), objects, get_id());

    m_position += step;

    // ЛЮТЫЙ КОСТЫЛЬ
    if (m_position.x > 1280) {
        m_position.x -= 100;
    }
    if (m_position.x < 0) {
        m_position.x += 100;
    }
    if (m_position.y > 1280) {
        m_position.y -= 100;
    }
    if (m_position.y < 0) {
        m_position.y += 100;
    }
}

const sf::Vector2f Player::get_position() const {
    return m_position;
}

const Direction Player::get_route() {
    return m_route;
}

void Player::apply(sf::Vector2f direction, Direction dir) {
    m_direction = direction; // для перемещения
    m_route = dir; // для анимации

}

sf::FloatRect Player::get_rect() {
    sf::FloatRect rect;

    // смещение начала прямоугольника игрока от его позиции m_position
    float delta = 15;

    // размеры текстуры
    float texture_heigh = 95;
    float texture_width = 70;

    rect.top = m_position.y + delta;
    rect.left = m_position.x + delta;
    rect.height = texture_heigh - delta;
    rect.width = texture_width - delta;
    return rect;
}

void Player::set_position(sf::Vector2f pos) {
    m_position.x = pos.x;
    m_position.y = pos.y;
}
