//
// Created by yaroslav on 16.05.2020.
//


#include <iostream>
#include "Bullet.h"

Bullet::Bullet(sf::Uint64 id, const sf::Vector2f& position, bool state)
       :  Object(id, position, n_bullet, state)
        , shape(10.f){
}




void Bullet::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    shape.setPosition(position);
}

void Bullet::set_direction(const Direction dir) {


}

void Bullet::draw_stat(sf::RenderWindow &window) {
    shape.setPosition(m_position);
    window.draw(shape);
}

void Bullet::draw(sf::RenderWindow &window, float time, float &current_frame) {

}

void Bullet::set_state(bool state) {
    m_state = state;
}




