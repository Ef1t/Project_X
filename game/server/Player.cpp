//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include <math.h>

#include "Player.h"

#define win_height 2560
#define win_lenght 2560

Player::Player(const sf::Vector2f &position)
        : m_position(position)
        , m_direction{0.0f, 0.0f}
        , m_velocity(PLAYER_VELOCITY)
        , GameObject(n_player, n_player_hp, n_player_dmg)
        , time_last_dgm(0)
        , time_last_land_dgm(0)
        , time_last_step(0)
        , time_per_fire(10)
        , time_per_fire_pistol (30)
        , time_per_fire_automat(10)
        , time_per_fire_shotgun(40)
        , initial(false)
        , creator(false) {}

void Player::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

    time_last_dgm += dt;
    time_last_land_dgm += dt;
    time_last_step += dt;

    if (hp <= 0) {
        alive = false;
        return;
    }

    // делаем нормальную скорость по диагонали
    float lenght = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
    if (lenght > 1) {
        m_direction.x /= sqrt(2);
        m_direction.y /= sqrt(2);
    }

    sf::Vector2f step = m_direction * (m_velocity * dt);

    std::shared_ptr<GameObject> near_obj;

    sf::Vector2f want_step = step;

    step = real_step(step, m_direction, get_rect(), objects, get_id(), near_obj);

    if (want_step != step && time_last_dgm > 1) {
        if (near_obj->m_name == n_enemy) {
            get_hp() -= near_obj->get_dmg();
//            std::cout << " damaga 2" << std::endl;
            time_last_dgm = 0;
        }
    }

    int dmg = 0;
    if (time_last_land_dgm > 3) {
        if (is_collide(land_obj, get_rect(), get_id(), dmg)) {
            get_hp() -= dmg;
            time_last_land_dgm = 0;
        }
    }

//    std::cout << "HP :" << get_hp() << std::endl;

    m_position += step;

    // ЛЮТЫЙ КОСТЫЛЬ
    if (m_position.x > win_lenght) {
        m_position.x -= 100;
    }
    if (m_position.x < 0) {
        m_position.x += 100;
    }
    if (m_position.y > win_height) {
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

void Player::add_land_obj(std::vector<std::shared_ptr<GameObject>> &objects) {
    land_obj.clear();
    for (auto obj : objects) {
        land_obj.push_back(obj);
    }
}
