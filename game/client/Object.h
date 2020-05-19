//
// Created by tsv on 18.04.19.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include <variant>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "messages/UserToServerMessage.h"
#include "transition.pb.h"

#include <memory>

#define n_player 0
#define n_bullet 1

class Object {
public:
    explicit Object(sf::Uint64 id, const sf::Vector2f& position, short object_name);

    //explicit Object( const sf::Vector2f& position);

    virtual
    void set_position(const sf::Vector2f& position);

    virtual
    void set_direction(const Direction dir);

    virtual
    void draw(sf::RenderWindow& window,  float time, float& current_frame) = 0; //вопрос, почему нельзя переопределить ее

    virtual
    void draw_stat(sf::RenderWindow& window) = 0;

   // virtual
   // void draw(sf::RenderWindow& window) = 0;


    Direction get_direction();

    sf::Uint64 get_id() const;

    float get_x() const;
    float get_y() const;



    short object_name;
    //short o_type;

protected:
    sf::Uint64 m_id;
    sf::Vector2f m_position;
    Direction m_dir;
    std::string m_name;

};

using ObjectPtr = std::shared_ptr<Object>;

#endif //GAME_OBJECT_H
