//
// Created by ef1t on 16.05.2020.
//

#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, int target)
        : m_position(position)
        , GameObject(n_enemy, n_enemy_hp, n_enemy_dmg)
        , m_velocity(ENEMY_VELOCITY)
        , m_target(target) {
}

const sf::Vector2f Enemy::get_position() const {
    return m_position;
}

void Enemy::set_position(float new_x, float new_y) {
    m_position.x = new_x;
    m_position.y = new_y;
}

void Enemy::set_target(int new_target) {
    m_target = new_target;
}

sf::Uint64 Enemy::get_target() {
    return m_target;
}

void Enemy::movement(float dt, float tempX, float tempY, std::vector<std::shared_ptr<GameObject>> &objects) {

    if (hp <= 0) {
        is_alive() = false;
        return;
    }

    float dist = sqrt((tempX - m_position.x) * (tempX - m_position.x) + (tempY - m_position.y) * (tempY - m_position.y));

    sf::Vector2f step;
    step.x = m_velocity * dt * (tempX - m_position.x) / dist;
    step.y =  m_velocity * dt * (tempY - m_position.y) / dist;

    sf::Vector2f dir = {(tempX - m_position.x) / dist, (tempY - m_position.y) / dist};

    step = real_step(step, dir, get_rect(), objects, get_id());


    if (dist > 2) {
        m_position.x +=step.x;
        m_position.y += step.y;
    }
//    puts("x");
//    std::cout<<m_position.x;
//    puts("y");
//    std::cout<<m_position.y;
}

void Enemy::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects){

}

sf::FloatRect Enemy::get_rect() {
    sf::FloatRect rect;

    // смещение начала прямоугольника игрока от его позиции m_position
    float delta = 15;

    // размеры текстуры
    float texture_heigh = 50;
    float texture_width = 50;

    rect.top = m_position.y + delta;
    rect.left = m_position.x + delta;
    rect.height = texture_heigh - delta;
    rect.width = texture_width - delta;

    return rect;
}

const Direction Enemy::get_route() {
}

void Enemy::apply(sf::Vector2f diretcion, Direction dir) {
    
}



