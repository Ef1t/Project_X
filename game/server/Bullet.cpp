//
// Created by yaroslav on 16.05.2020.
//

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f positon, Direction dir, short p_id) :
        m_position(positon),
        m_velocity(bullet_velocity),
        GameObject(n_bullet),
        b_dir(dir),
        player_id(p_id){
}


void Bullet::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

//    std:: cout << b_dir.up << " Up B-_dir in update\n";
//    std:: cout << b_dir.down << " Do B-_dir in update\n";
//    std:: cout << b_dir.right << " Le B-_dir in update\n";
//    std:: cout << b_dir.left << " Ri B-_dir in update\n";

    if (b_dir.up) {
        m_direction.y--;
    }
    if (b_dir.down) {
        m_direction.y++;
    }
    if (b_dir.left) {
        m_direction.x--;
    }
    if (b_dir.right) {
        m_direction.x++;
    }

    //std::cout << m_position.x << " m_pos_x\n";
    m_position += m_direction * (m_velocity * dt);
    //std::cout << m_position.x << " new m_pos_x\n";
}



void Bullet::apply(sf::Vector2f diretcion, Direction dir) {
   // GameObject::apply(diretcion, dir);
}

const Direction Bullet::get_route() {
    //
}

const sf::Vector2f Bullet::get_position() const {
    return m_position;
}

Bullet::Bullet(short name) : GameObject(name) {

}

sf::FloatRect Bullet::get_rect() {

}


