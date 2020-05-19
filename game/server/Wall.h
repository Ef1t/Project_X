//
// Created by Олег Реуцкий on 13.05.2020.
//

#ifndef GAME_WALL_H
#define GAME_WALL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string_view>

#include "GameObject.h"

class Wall : public GameObject {
 public:
    Wall(uint64_t x_1, uint64_t y_1, uint64_t x_2, uint64_t y_2, std::string_view name);

    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) override;

    sf::FloatRect get_rect() override;

 private:
    sf::FloatRect rect;
};


#endif //GAME_WALL_H
