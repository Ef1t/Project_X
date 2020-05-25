//
// Created by tsv on 18.04.19.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include "Object.h"
#include "TmxLevel.h"

#include "Skin.h"

#include <SFML/Graphics/CircleShape.hpp>

#include <string>

class Player : public Object, Skin {
public:
    Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position, int hp);

    void draw(sf::RenderWindow& window, float time, float& current_frame) override;

    void draw_stat(sf::RenderWindow& window) override ;

    void draw_hp_interface(sf::RenderWindow& window, view::View& view) override;

    void set_position(const sf::Vector2f& position) override;

    void set_direction(Direction dir) override;

    void set_hp(int hp) override;

private:
    std::string m_username;
    Skin m_actor;

    sf::Texture m_hp_texture;
    sf::Sprite m_hp_sprite;

    sf::Font m_font;
    sf::Text m_hp_text;

public:

};


#endif //GAME_PLAYER_H
