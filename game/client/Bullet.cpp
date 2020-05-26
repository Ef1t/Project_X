//
// Created by yaroslav on 16.05.2020.
//


#include <iostream>
#include "Bullet.h"

Bullet::Bullet(sf::Uint64 id, const sf::Vector2f& position, bool state)
       :  Object(id, position, n_bullet, state)
        , shape(6.f){

    bullet_texture.loadFromFile("../../client/inGameTextures/bullet.png");
    bullet_sprite.setTexture(bullet_texture);
}




void Bullet::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    shape.setPosition(position);
}

void Bullet::set_direction(const Direction dir) {


}

void Bullet::draw_stat(sf::RenderWindow &window) {
    bullet_sprite.setPosition(m_position);
    window.draw(bullet_sprite);
    //shape.setPosition(m_position);
    //window.draw(shape);
    /*sf::Image heroimage;
    heroimage.loadFromFile("../../images/bullet.png");
    sf::Texture herotexture;
    herotexture.loadFromImage((heroimage));
    sf::Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(sf::IntRect(0,0,16,16));
    //herosprite.setTextureRect(IntRect(0,192,96,96));
    herosprite.setPosition(0, 0);
    window.draw(herosprite); */
}

void Bullet::draw(sf::RenderWindow &window, float time, float &current_frame) {

}

void Bullet::set_hp(int hp) {
    m_hp = hp;
}

void Bullet::update_dir_enemy(float x, float y) {

}




