//
// Created by yaroslav on 16.05.2020.
//
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "messages/UserToServerMessage.h"
#include "transition.pb.h"
#include <SFML/Graphics/CircleShape.hpp>

#include <memory>
#include "Object.h"
#ifndef GAME_BULLET_H
#define GAME_BULLET_H

class Bullet : public Object {
public:

    Bullet(sf::Uint64 id, const sf::Vector2f& position);

    void set_position(const sf::Vector2f& position) override ;

    void set_direction(const Direction dir) override ;

    void draw_stat(sf::RenderWindow& window) override;

    void draw(sf::RenderWindow& window,  float time, float& current_frame) override ;

private:
    sf::CircleShape shape;
    //sf::Vector2f m_position;
    std::string m_username;


};








#endif //GAME_BULLET_H
