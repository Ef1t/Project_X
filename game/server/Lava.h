//
// Created by Олег Реуцкий on 23.05.2020.
//

#ifndef GAME_LAVA_H
#define GAME_LAVA_H

#include "GameObject.h"

class Lava : public GameObject {
 public:

    Lava(uint64_t left, uint64_t top, uint64_t width, uint64_t heigth);

    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) override;

    sf::FloatRect get_rect() override;

    void apply(sf::Vector2f diretcion, Direction dir) override;

    const Direction get_route() override;

    const sf::Vector2f get_position() const override;

 private:
    sf::FloatRect rect;
};


#endif //GAME_LAVA_H
