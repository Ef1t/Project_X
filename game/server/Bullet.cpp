//
// Created by yaroslav on 16.05.2020.
//

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f positon, Direction dir, short p_id) :
        m_position(positon),
        m_velocity(bullet_velocity),
        GameObject(n_bullet, null_hp, n_player_dmg),
        b_dir(dir),
        player_id(p_id) {

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

}

void Bullet::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

//    std:: cout << b_dir.up << " Up B-_dir in update\n";
//    std:: cout << b_dir.down << " Do B-_dir in update\n";
//    std:: cout << b_dir.right << " Le B-_dir in update\n";
//    std:: cout << b_dir.left << " Ri B-_dir in update\n";



    m_position += m_direction * (m_velocity * dt * 20);
    if (collide_and_dmg(objects, n_enemy, get_rect(), get_dmg())) {
        alive = false;
    }
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

sf::FloatRect Bullet::get_rect() {
    sf::FloatRect rect;

    // смещение начала прямоугольника игрока от его позиции m_position
    float delta = 0;

    // размеры текстуры
    float texture_heigh = 10;
    float texture_width = 10;

    rect.top = m_position.y + delta;
    rect.left = m_position.x + delta;
    rect.height = texture_heigh - delta;
    rect.width = texture_width - delta;

    return rect;
}


