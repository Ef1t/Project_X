//
// Created by Олег Реуцкий on 13.05.2020.
//

#include "Wall.h"

Wall::Wall(uint64_t left, uint64_t top, uint64_t width, uint64_t heigth, std::string_view name)
        : GameObject()
        , rect(left, top, width, heigth) {
    this->name = name;
}

 sf::FloatRect Wall::get_rect() {
    return rect;
}

void Wall::update(float dt,  std::vector<std::shared_ptr<GameObject>> &objects) {

}
