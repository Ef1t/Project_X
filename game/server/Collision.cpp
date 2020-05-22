//
// Created by Олег Реуцкий on 20.05.2020.
//

#include <iostream>

#include "Collision.h"

//оч сложна нипонятна ниясна но работает
//по всем вопросам к Олегу Реуцкому ака бох стен
sf::Vector2f Collision::real_step(sf::Vector2f desired_step,
                                  sf::Vector2f direction,
                                  sf::FloatRect obj_rect,
                                  std::vector<std::shared_ptr<GameObject>> &objects,
                                  uint64_t id) {

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

bool Collision::collide_and_dmg(std::vector<std::shared_ptr<GameObject>> &objects, int obj_num_name, sf::FloatRect this_obj_rect, int dmg) {
    for (auto obj : objects) {
        if ((obj->m_name == obj_num_name) && obj->get_rect().intersects(this_obj_rect)) {
            obj->get_hp() -= dmg;
            return true;
        }
    }
    return false;
}

bool Collision::is_collide(std::vector<std::shared_ptr<GameObject>> &objects, sf::FloatRect this_obj_rect, int id) {
    for (auto obj : objects) {
        if (obj->get_id() != id) {
            if (obj->get_rect().intersects(this_obj_rect)) {
                return true;
            }
        }
    }
    return false;
}

//bool Collision::not_collide(sf::FloatRect &collide_obj_rect, sf::Vector2f dir, sf::FloatRect this_obj_rect,
//                            std::vector<std::shared_ptr<GameObject>> &objects, uint64_t id) {
//    for (auto obj : objects) {
//        if (obj->get_id() != id) {
//            if (obj->get_rect().intersects(this_obj_rect)) {
//                collide_obj_rect = obj->get_rect();
//                return false;
//            }
//        }
//    }
//    return true;
//}


