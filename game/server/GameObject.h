//
// Created by tsv on 18.04.19.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H


#include <memory>
#include <SFML/Config.hpp>


class GameObject {
public:
    GameObject();

    sf::Uint64 get_id() const;

    virtual
    void update(float dt) = 0;

protected:
    uint64_t m_id;

private:
    static sf::Uint64 next_id;
};

using GameObjectPtr = std::shared_ptr<GameObject>;

#endif //GAME_GAMEOBJECT_H
