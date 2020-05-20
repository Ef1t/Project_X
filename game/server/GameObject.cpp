//
// Created by tsv on 18.04.19.
//

#include "GameObject.h"

sf::Uint64 GameObject::next_id = 1;

GameObject::GameObject(short name)
        : m_id(next_id++),
        m_name(name) {}

sf::Uint64 GameObject::get_id() const {
    return m_id;
}

std::string &GameObject::get_name() {
    return name;
}
