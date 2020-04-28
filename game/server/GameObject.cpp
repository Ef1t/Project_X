//
// Created by tsv on 18.04.19.
//

#include "GameObject.h"

sf::Uint64 GameObject::next_id = 1;

GameObject::GameObject()
        : m_id(next_id++) {
}

sf::Uint64 GameObject::get_id() const {
    return m_id;
}
