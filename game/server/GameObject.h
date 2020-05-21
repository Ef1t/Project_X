//
// Created by tsv on 18.04.19.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H


#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <string>


class GameObject {
public:
    GameObject();

    sf::Uint64 get_id() const;

    std::string &get_name();

    virtual
    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) = 0;

    virtual
    sf::FloatRect get_rect() = 0;

protected:
    uint64_t m_id;
    std::string name;

private:
    static sf::Uint64 next_id;
};

using GameObjectPtr = std::shared_ptr<GameObject>;

#endif //GAME_GAMEOBJECT_H
