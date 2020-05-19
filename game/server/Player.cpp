//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include <math.h>

#include "Player.h"

Player::Player(const sf::Vector2f &position)
        : m_position(position), m_direction{0.0f, 0.0f}, m_velocity(PLAYER_VELOCITY) {}

void Player::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

    // делаем нормальную скорость по диагонале
    float lenght = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
    if (lenght > 1) {
        m_direction.x /= sqrt(2);
        m_direction.y /= sqrt(2);
    }

    //оч сложна нипонятна ниясна но работает
    //по всем вопросам к Олегу Реуцкому ака бох стен
    //TODO: вынести коллизии в отдельный класс
    //NOTE: старайтесь избегать углов :)
    sf::Vector2f step = m_direction * (m_velocity * dt);
    for (auto obj : objects) {
        sf::FloatRect new_rect(get_rect().left + step.x, get_rect().top + step.y, get_rect().width, get_rect().height);
        if (obj->get_rect().intersects(new_rect)) {
            if ((m_direction.x != 0) || (m_direction.y != 0)) {
                last_non_zero_dir = m_direction;
            }
            while (obj->get_rect().intersects(new_rect)) {
                new_rect.left -= last_non_zero_dir.x;
                new_rect.top -= last_non_zero_dir.y;
//                std::cout << obj->get_id() << " dicrease " << last_non_zero_dir.x << " " << last_non_zero_dir.y
//                          << std::endl;
            }
            step.x = new_rect.left - get_rect().left - last_non_zero_dir.x;
            step.y = new_rect.top - get_rect().top - last_non_zero_dir.y;
//            std::cout << obj->get_id() << " true ";
        } else {
//            std::cout << obj->get_id() << " false ";
        }
    }
//    std::cout << std::endl;
    m_position += step;
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
