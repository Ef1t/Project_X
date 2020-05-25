//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position, int hp)
        : Object(id, position, n_player, hp)
        , m_username(username)
        , m_actor("../../images/pigcop_vest.png")
        {
}

void Player::draw(sf::RenderWindow& window, float time, float& current_frame) {
    //std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";


    hp_bar_green.setPosition(m_position.x + 50 - hp_bar_length / 2, m_position.y - 20);
    hp_bar_green.setSize(sf::Vector2f( hp_bar_length * ((double)m_hp / m_max_hp), 10));

    hp_bar_red.setPosition(hp_bar_green.getPosition().x + hp_bar_green.getSize().x, m_position.y - 20);
    hp_bar_red.setSize(sf::Vector2f( hp_bar_length  - hp_bar_green.getSize().x, 10));

    std::cout << m_hp << std::endl;
    //std::cout << hp_bar_length * ((double)m_hp / m_max_hp) << std::endl;
    //std::cout << hp_bar_length  - hp_bar_green.getSize().x << std::endl;

    this->go_texture(m_dir,time,current_frame,this->m_actor);
    window.draw(m_actor.herosprite);
    window.draw(hp_bar_green);
    window.draw(hp_bar_red);
}

void Player::draw_stat(sf::RenderWindow& window) {

}

void Player::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    //m_actor.setPosition(m_position);
    m_actor.herosprite.setPosition(m_position);
}

void Player::set_direction(const Direction dir) {
    m_dir = dir;

}

void Player::set_hp(int hp) {
    m_hp = hp;
}

void Player::update_dir_enemy(float x, float y) {

}
