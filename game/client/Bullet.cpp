//
// Created by yaroslav on 16.05.2020.
//


#include <iostream>
#include "Bullet.h"

Bullet::Bullet(sf::Uint64 id, const sf::Vector2f& position)
       :  Object(id, position, n_bullet)
        , shape(10.f){
}




void Bullet::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    std::cout << "Positon x , y = " << position.x << " " << position.y << '\n';
    shape.setPosition(position);
}

void Bullet::set_direction(const Direction dir) {


}

void Bullet::draw_stat(sf::RenderWindow &window) {
    //shape.setFillColor(sf::Color::Green);
    shape.setPosition(m_position);
   // std::cout << " X Bullet = " << m_position.x << "\n";
   // std::cout << " Y Bullet = " << m_position.y << "\n";
    window.draw(shape);
}

void Bullet::draw(sf::RenderWindow &window, float time, float &current_frame) {

}




