//
// Created by ef1t on 16.05.2020.
//

#include "Enemy.h"
#include "Object.h"

Enemy::Enemy(sf::Uint64 id, const sf::Vector2f& position, int hp)
        : Object(id, position, n_enemy, hp)
        , shape(30.) { }

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

    hp_bar_green.setPosition(m_position.x + shape.getRadius() - hp_bar_length / 2, m_position.y - 20);
    hp_bar_green.setSize(sf::Vector2f( hp_bar_length * ((double)m_hp / m_max_hp), 10));

    hp_bar_red.setPosition(hp_bar_green.getPosition().x + hp_bar_green.getSize().x, m_position.y - 20);
    hp_bar_red.setSize(sf::Vector2f( hp_bar_length  - hp_bar_green.getSize().x, 10));

    window.draw(shape);
    window.draw(hp_bar_green);
    window.draw(hp_bar_red);
}

void Enemy::set_hp(int hp) {
    m_hp = hp;
}

void Enemy::set_direction(const Direction dir) {

}