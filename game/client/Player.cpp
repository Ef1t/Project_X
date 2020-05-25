//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position, int hp)
        : Object(id, position, n_player, hp)
        , m_username(username)
        , m_actor()
{
    m_hp_texture.loadFromFile("../../client/inGameTextures/health.png");
    m_hp_sprite.setTexture(m_hp_texture);
    m_font.loadFromFile("../../client/menuTextures/font.ttf");
}

void Player::draw(sf::RenderWindow& window, float time, float& current_frame) {
    //std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";

    hp_bar_green.setPosition(m_position.x + 50 - hp_bar_length / 2, m_position.y - 20);
    hp_bar_green.setSize(sf::Vector2f( hp_bar_length * ((double)m_hp / m_max_hp), 10));

    hp_bar_red.setPosition(hp_bar_green.getPosition().x + hp_bar_green.getSize().x, m_position.y - 20);
    hp_bar_red.setSize(sf::Vector2f( hp_bar_length  - hp_bar_green.getSize().x, 10));

    hp_bar_red.setPosition(hp_bar_green.getPosition().x + hp_bar_green.getSize().x, m_position.y - 20);
    hp_bar_red.setSize(sf::Vector2f( hp_bar_length  - hp_bar_green.getSize().x, 10));


    this->go_texture(m_dir,time,current_frame,this->m_actor);
    window.draw(m_actor.herosprite);
    window.draw(hp_bar_green);
    window.draw(hp_bar_red);
    //window.draw(m_hp_sprite);
    //window.draw(m_hp_text);
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

void Player::draw_hp_interface(RenderWindow &window, view::View &view) {

    if(m_position.x < 50)
        m_hp_text.setPosition(100, m_position.y + 200);

//    std::cout << view.get_view().getCenter().x << std::endl;
    std::cout << m_position.y << std::endl;
    m_hp_text.setFont(m_font);
    m_hp_text.setString(std::to_string(m_hp) + "/" + std::to_string(m_max_hp));
    m_hp_text.setCharacterSize(24);


    sf::Vector2f pos;
    if(m_position.x <= 200)
        pos.x = 450;
    else if (m_position.x >= 2280)
        pos.x = 2525;
    else
        pos.x = m_position.x + 250;

    if(m_position.y <= 140)
        pos.y = 325;
    else if (m_position.y >= 2280)
        pos.y = 2500;
    else
        pos.y = m_position.y + 200;

    m_hp_text.setPosition(pos.x, pos.y);
    m_hp_sprite.setPosition(pos.x - 30, pos.y);


    if ((double) m_hp / m_max_hp > 0.8) {
        m_hp_text.setFillColor(sf::Color::Green);
    }
    else if ((double) m_hp / m_max_hp > 0.35) {
        m_hp_text.setFillColor(sf::Color::Yellow);
    }
    else {
        m_hp_text.setFillColor(sf::Color::Red);
    }

    window.draw(m_hp_text);
    window.draw(m_hp_sprite);
}
