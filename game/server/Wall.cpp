//
// Created by Олег Реуцкий on 13.05.2020.
//

#include "Wall.h"

Wall::Wall(uint64_t x_1, uint64_t y_1, uint64_t x_2, uint64_t y_2, std::string_view name)
        : GameObject()
        , rect(x_1, y_1, x_2, y_2) {
    this->name = name;
}

 sf::FloatRect Wall::get_rect() {
    return rect;
}

void Wall::update(float dt,  std::vector<std::shared_ptr<GameObject>> &objects) {

}
