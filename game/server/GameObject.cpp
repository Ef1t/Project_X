//
// Created by tsv on 18.04.19.
//

#include "GameObject.h"

sf::Uint64 GameObject::next_id = 1;

GameObject::GameObject(short name, int hp, int dmg)
        : m_id(next_id++)
        , m_name(name)
        , alive(true)
        , hp(hp)
        , dmg(dmg) {}

sf::Uint64 GameObject::get_id() const {
    return m_id;
}

std::string &GameObject::get_name() {
    return name;
}

bool &GameObject::is_alive() {
    return alive;
}

int &GameObject::get_hp() {
    return hp;
}

int &GameObject::get_dmg() {
    return dmg;
}
