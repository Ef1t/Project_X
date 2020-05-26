//
// Created by Олег Реуцкий on 13.05.2020.
//

#ifndef GAME_WALL_H
#define GAME_WALL_H

#include <iostream>
#include <string_view>

#include "GameObject.h"

class Wall : public GameObject {
 public:
    Wall(uint64_t left, uint64_t top, uint64_t width, uint64_t heigth, std::string_view name);

    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) override;

    sf::FloatRect get_rect() override;

    void apply(sf::Vector2f diretcion, Direction dir) override;

    const Direction get_route() override;

    const sf::Vector2f get_position() const override;

 private:
    sf::FloatRect rect;
};


#endif //GAME_WALL_H
