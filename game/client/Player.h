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
    Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window, float time, float& current_frame) override;

    void set_position(const sf::Vector2f& position) override;

    void set_direction(Direction dir) override;

    //virtual void go_texure(Direction dir, float time, float& current_frame) = 0;

   // void go_texure1(Direction dir, float time, float& current_frame);
   //Direction get_direction();

private:
    std::string m_username;
    Skin m_actor;

public:

};


#endif //GAME_PLAYER_H
