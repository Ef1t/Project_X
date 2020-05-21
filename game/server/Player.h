//
// Created by tsv on 18.04.19.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <SFML/System/Vector2.hpp>
#include <vector>

#include "GameObject.h"
#include "messages/UserToServerMessage.h"

const float PLAYER_VELOCITY = 20.0f;

class Player : public GameObject {
public:
    explicit Player(const sf::Vector2f& position = sf::Vector2f{100.0f, 100.0f});

    void update(float dt,std::vector<std::shared_ptr<GameObject>> &objects) override;

    void apply(sf::Vector2f direction, Direction dir);

    const sf::Vector2f get_position() const;

    const Direction get_route();

    sf::FloatRect get_rect() override;

    bool is_collide;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;
    Direction m_route; // Players route
    sf::Vector2f last_non_zero_dir;

};

using PlayerPtr = std::shared_ptr<Player>;

#endif //GAME_PLAYER_H
