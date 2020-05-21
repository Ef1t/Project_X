//
// Created by ef1t on 16.05.2020.
//

#include "Enemy.h"
#include "Object.h"

Enemy::Enemy(sf::Uint64 id, const sf::Vector2f& position)
        : Object(id, position, n_enemy, 1) //TODO: добавить state
        , shape(30) {
}

void Enemy::draw(sf::RenderWindow& window, float time, float& current_frame) {
    //std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";
//    this->go_texture(m_dir,time,current_frame,this->m_actor);
//    window.draw(m_actor.herosprite);
}

void Enemy::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    //m_actor.setPosition(m_position);
    shape.setPosition(m_position);
}

void Enemy::draw_stat(sf::RenderWindow& window) {
    shape.setPosition(m_position);
    window.draw(shape);
}

void Enemy::set_state(bool state) {
    m_state = state;
}

void Enemy::set_direction(const Direction dir) {

}