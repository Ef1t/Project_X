//
// Created by tsv on 18.04.19.
//

#include "Object.h"

Object::Object(sf::Uint64 id, const sf::Vector2f& position, short object_name, bool state)
        : m_id(id)
        , m_position(position) ,
        object_name(object_name),
        m_state(state){
}

/*Object::Object(const sf::Vector2f& position)
        : m_position(position) {
}*/

void Object::set_position(const sf::Vector2f& position) {
    m_position = position;
}

sf::Uint64 Object::get_id() const {
    return m_id;
}

float Object::get_x() const {
    m_position.x;
}

float Object::get_y() const {
    m_position.y;
}

void Object::set_direction(Direction dir) {
    m_dir = dir;
}

Direction Object::get_direction() {
    return m_dir;
}

bool Object::get_state() const {
    return m_state;
}




