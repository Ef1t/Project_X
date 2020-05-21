//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position, bool state)
        : Object(id, position, n_player, state)
        , m_username(username)
        , m_actor()
        {
}

void Player::draw(sf::RenderWindow& window, float time, float& current_frame) {
    //std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";
    this->go_texture(m_dir,time,current_frame,this->m_actor);
    window.draw(m_actor.herosprite);
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

void Player::set_state(bool state) {
    m_state = state;
}
