//
// Created by tsv on 18.04.19.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "messages/UserToServerMessage.h"

const float PLAYER_VELOCITY = 10.0f;

class Player : public GameObject {
public:
    explicit Player(const sf::Vector2f& position = sf::Vector2f{100.0f, 100.0f});

    void update(float dt) override;

    void apply(sf::Vector2f diretcion, Direction dir);

    const sf::Vector2f get_position() const;

    const Direction get_route();

private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;
    Direction m_route; //направление игрока

};

using PlayerPtr = std::shared_ptr<Player>;

#endif //GAME_PLAYER_H
