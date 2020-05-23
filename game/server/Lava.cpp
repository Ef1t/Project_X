//
// Created by Олег Реуцкий on 23.05.2020.
//

#include "Lava.h"

Lava::Lava(uint64_t left, uint64_t top, uint64_t width, uint64_t heigth)
        : GameObject(n_lava, null_hp, n_lava_dmg)
        , rect(left, top, width, heigth)
        {}

void Lava::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

}

sf::FloatRect Lava::get_rect() {
    return rect;
}

void Lava::apply(sf::Vector2f diretcion, Direction dir) {

}

const Direction Lava::get_route() {
    return Direction();
}

const sf::Vector2f Lava::get_position() const {
    return sf::Vector2f();
}

