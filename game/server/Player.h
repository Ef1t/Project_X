//
// Created by tsv on 18.04.19.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <SFML/System/Vector2.hpp>
#include <vector>

#include "GameObject.h"
#include "messages/UserToServerMessage.h"
#include "Collision.h"

const float PLAYER_VELOCITY = 20.0f;

class Player : public GameObject, public Collision {
public:
    explicit Player(const sf::Vector2f& position = sf::Vector2f{600.0f, 600.0f});

    void update(float dt,std::vector<std::shared_ptr<GameObject>> &objects) override;

    void apply(sf::Vector2f diretcion, Direction dir) override ;

    const sf::Vector2f get_position() const override ;

    const Direction get_route() override ;

    sf::FloatRect get_rect() override;

    void set_position(sf::Vector2f pos);

    void add_land_obj(std::vector<std::shared_ptr<GameObject>> &objects);

    // GOVNOKODIM
    unsigned int time_per_fire; //коэффициент скоростельности (регулирует скорость стрельбы для одного оружия)


    unsigned int time_per_fire_pistol; //коэффициент скоростельности (регулирует скорость стрельбы для одного оружия)
    unsigned int time_per_fire_automat;
    unsigned int time_per_fire_shotgun;

    bool initial;

    bool creator;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
    float m_velocity;
    Direction m_route; // Players route
    float time_last_dgm;
    float time_last_land_dgm;
    float time_last_step;
    std::vector<std::shared_ptr<GameObject>> land_obj;


};

using PlayerPtr = std::shared_ptr<Player>;

#endif //GAME_PLAYER_H
