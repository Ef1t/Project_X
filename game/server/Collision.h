//
// Created by Олег Реуцкий on 20.05.2020.
//

#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <vector>
#include <memory>

#include "GameObject.h"

class Collision {
 public:
    sf::Vector2f real_step(sf::Vector2f desired_step, sf::Vector2f direction, sf::FloatRect obj_rect,
                           std::vector<std::shared_ptr<GameObject>> &objects, uint64_t id, std::shared_ptr<GameObject> &near_obj);

    bool collide_and_dmg(std::vector<std::shared_ptr<GameObject>> &objects, int state, sf::FloatRect this_obj_rect, int dmg);

    bool is_collide(std::vector<std::shared_ptr<GameObject>> &objects, sf::FloatRect this_obj_rect, int id);

    bool is_collide(std::vector<std::shared_ptr<GameObject>> &objects, sf::FloatRect this_obj_rect, int id, int &dmg);

 private:
    sf::Vector2f last_non_zero_dir;
};


#endif //GAME_COLLISION_H
