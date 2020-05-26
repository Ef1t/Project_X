//
// Created by Олег Реуцкий on 11.05.2020.
//

#include "View.h"

void View::set_view(float x, float y, float map_width, float map_height) {
    float temp_x = x;
    float  temp_y = y;
//    if (x < 192) temp_x = 192;
//    if (y < 132) temp_y = 132;
//    if (x > map_width - 292) temp_x = map_width - 292;
//    if (y > map_height - 256) temp_y = map_height - 256;

    view.setCenter(temp_x + 50, temp_y + 60);
}

sf::View & View::get_view() {
    return view;
}

void View::set_view(sf::View sf_view) {
    view = sf_view;
}
