//
// Created by tsv on 18.04.19.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H


#include <memory>
#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include "messages/UserToServerMessage.h"

//названия объектов
#define n_player 0
#define n_bullet 1
#define n_enemy 2

#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
public:
    GameObject(short name);

    sf::Uint64 get_id() const;

    std::string &get_name();

    virtual
    void update(float dt, std::vector<std::shared_ptr<GameObject>> &objects) = 0;

    virtual
    sf::FloatRect get_rect() = 0;


    virtual
    void apply(sf::Vector2f diretcion, Direction dir) = 0;

    virtual
    const Direction get_route() = 0;

    virtual
    const sf::Vector2f get_position() const = 0;

    short m_name;

protected:
    uint64_t m_id;
    std::string name;

private:
    static sf::Uint64 next_id;
    //Direction dir;
};

using GameObjectPtr = std::shared_ptr<GameObject>;

#endif //GAME_GAMEOBJECT_H
