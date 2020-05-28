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
#include <SFML/Graphics/RectangleShape.hpp>

#define n_player 0
#define n_bullet 1
#define n_enemy 2

#define hp_bar_length 50

class Object {
public:
    explicit Object(sf::Uint64 id, const sf::Vector2f& position, short object_name, int hp);
    
    virtual
    void set_position(const sf::Vector2f& position);

    virtual
    void set_direction(const Direction dir);

    virtual
    void set_hp(int hp) = 0;

    virtual
    void draw(sf::RenderWindow& window,  float time, float& current_frame) = 0; //вопрос, почему нельзя переопределить ее

    virtual
    void draw_stat(sf::RenderWindow& window) = 0;

    virtual
    void update_dir_enemy(float x, float y) = 0;

    Direction get_direction();

    sf::Uint64 get_id() const;

    float get_x() const;
    float get_y() const;

    int get_hp() const;
    short object_name;
    int kills_count;
    std::string m_name;
    bool name_init;
protected:
    sf::Uint64 m_id;
    sf::Vector2f m_position;
    Direction m_dir;
    int m_hp;
    int m_max_hp;

    sf::RectangleShape hp_bar_green;
    sf::RectangleShape hp_bar_red;
};

using ObjectPtr = std::shared_ptr<Object>;

#endif //GAME_OBJECT_H
