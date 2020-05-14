//
// Created by tsv on 18.04.19.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "messages/UserToServerMessage.h"
#include "transition.pb.h"

#include <memory>

class Object {
public:
    explicit Object(sf::Uint64 id, const sf::Vector2f& position);

    virtual
    void set_position(const sf::Vector2f& position);

    virtual
    void set_direction(const Direction dir);

    virtual
    void draw(sf::RenderWindow& window,  float time, float& current_frame) = 0;

    //virtual void go_texure1(Direction dir, float time, float& current_frame) = 0;

    //virtual
    //void go_texure(Direction dir, float time, float& current_frame) = 0;


    //void set_direction(Direction dir);

    Direction get_direction();

    sf::Uint64 get_id() const;

    float get_x() const;
    float get_y() const;

protected:
    sf::Uint64 m_id;
    sf::Vector2f m_position;
    Direction m_dir;

};

using ObjectPtr = std::shared_ptr<Object>;

#endif //GAME_OBJECT_H
