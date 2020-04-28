//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position)
        : Object(id, position)
        , m_username(username)
        , m_actor(10) {
}

void Player::draw(sf::RenderWindow& window) {
    std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";
    window.draw(m_actor);
}

void Player::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    m_actor.setPosition(m_position);
}
