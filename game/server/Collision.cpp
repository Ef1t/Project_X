//
// Created by Олег Реуцкий on 20.05.2020.
//

#include <iostream>

#include "Collision.h"

//оч сложна нипонятна ниясна но работает
//по всем вопросам к Олегу Реуцкому ака бох стен
sf::Vector2f Collision::real_step(sf::Vector2f desired_step, sf::Vector2f direction, sf::FloatRect obj_rect,
                                  std::vector<std::shared_ptr<GameObject>> &objects, uint64_t id) {

    for (auto obj : objects) {
        if (obj->get_id() != id) {
            sf::FloatRect new_rect(obj_rect.left + desired_step.x, obj_rect.top + desired_step.y, obj_rect.width,
                                   obj_rect.height);
            if (obj->get_rect().intersects(new_rect)) {
                if ((direction.x != 0) || (direction.y != 0)) {
                    last_non_zero_dir = direction;
                }
                while (obj->get_rect().intersects(new_rect)) {
                    new_rect.left -= last_non_zero_dir.x;
                    new_rect.top -= last_non_zero_dir.y;
                }
                desired_step.x = new_rect.left - obj_rect.left - last_non_zero_dir.x;
                desired_step.y = new_rect.top - obj_rect.top - last_non_zero_dir.y;
            }
        }
    }
    return desired_step;
}

