//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position, int hp)
        : Object(id, position, n_player, hp)
        , m_username(username)
        , m_actor("../../images/pigcop_vest.png")
        , cur_frame_pl(0)
        {
    m_skull_texture.loadFromFile("../../client/inGameTextures/skull.png");
    m_hp_bar_texture.loadFromFile("../../client/inGameTextures/hp_bar.png");
    m_font.loadFromFile("../../client/menuTextures/font.ttf");
    m_skull_sprite.setTexture(m_skull_texture);
    m_hp_bar_sprite.setTexture(m_hp_bar_texture);
}

void Player::draw(sf::RenderWindow& window, float time, float& current_frame) {
    //std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";

    sf::Text kills_text;
    kills_text.setFont(m_font);
    kills_text.setFillColor(sf::Color::Red);
    kills_text.setString("X       " + std::to_string(kills_count));

    sf::Text hp_text;
    hp_text.setFont(m_font);
    if ((double) m_hp / m_max_hp > 0.8)
        hp_text.setFillColor(sf::Color::Green);
    else if ((double) m_hp / m_max_hp > 0.35)
        hp_text.setFillColor(sf::Color::Yellow);
    else
        hp_text.setFillColor(sf::Color::Red);


    hp_text.setString(std::to_string(m_hp));

    hp_text.setPosition(m_position.x + 290, m_position.y + 195);
    m_hp_bar_sprite.setPosition(m_position.x + 260, m_position.y + 200);

    kills_text.setPosition(m_position.x + 230, m_position.y - 120);
    m_skull_sprite.setPosition(m_position.x + 250, m_position.y - 120);


    hp_bar_green.setPosition(m_position.x + 50 - hp_bar_length / 2, m_position.y - 20);
    hp_bar_green.setSize(sf::Vector2f( hp_bar_length * ((double)m_hp / m_max_hp), 10));

    hp_bar_red.setPosition(hp_bar_green.getPosition().x + hp_bar_green.getSize().x, m_position.y - 20);
    hp_bar_red.setSize(sf::Vector2f( hp_bar_length  - hp_bar_green.getSize().x, 10));

    //std::cout << m_hp << std::endl;
    //std::cout << hp_bar_length * ((double)m_hp / m_max_hp) << std::endl;
    //std::cout << hp_bar_length  - hp_bar_green.getSize().x << std::endl;

    this->go_texture(m_dir,time,cur_frame_pl,this->m_actor);
    window.draw(m_actor.herosprite);
    window.draw(hp_bar_green);
    window.draw(hp_bar_red);
    window.draw(m_skull_sprite);
    window.draw(kills_text);
    window.draw(m_hp_bar_sprite);
    window.draw(hp_text);

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
