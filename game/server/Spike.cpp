//
// Created by Олег Реуцкий on 23.05.2020.
//

#include "Spike.h"

Spike::Spike(uint64_t left, uint64_t top, uint64_t width, uint64_t heigth)
        : GameObject(n_spike, null_hp, n_spike_dmg)
        , rect(left, top, width, heigth)
{}

void Spike::update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) {

}

sf::FloatRect Spike::get_rect() {
    return rect;
}

void Spike::apply(sf::Vector2f diretcion, Direction dir) {

}

const Direction Spike::get_route() {
    return Direction();
}

const sf::Vector2f Spike::get_position() const {
    return sf::Vector2f();
}

