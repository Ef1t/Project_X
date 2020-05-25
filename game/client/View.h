//
// Created by Олег Реуцкий on 11.05.2020.
//

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <SFML/Graphics.hpp>

namespace view {
    class View {
    public:
        void set_view(float x, float y, float map_width, float map_height);

        sf::View &get_view();

    private:
        sf::View view;
    };
}

#endif //GAME_VIEW_H
