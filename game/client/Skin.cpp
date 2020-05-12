//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Skin.h"


    Skin::Skin() {
    heroimage.loadFromFile("../../images/pigcop_vest.png");
    herotexture.loadFromImage((heroimage));
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(sf::IntRect(0,192,96,96));
    //herosprite.setTextureRect(IntRect(0,192,96,96));
    herosprite.setPosition(250, 250);


}


void Skin::go_texture(Direction dir, float time, float& current_frame, Skin& m_actor) {
    if (dir.left) { //если нажата клавиша стрелка влево или англ буква А
        current_frame += 12*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 2) current_frame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect(16+82 , 105 * int(current_frame), 85 , 95)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        //std::cout << "llllllllllllllllllllll" << "\n";
    }

    if (dir.right) {
        current_frame += 12*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 2) current_frame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect((16+82*2) , 105 * int(current_frame), -85 , 95)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        // std::cout << "rrrrrrrrrrrrrr" << "\n";
    }

    if (dir.up) {
        current_frame += 11*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 2) current_frame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect((24+82*9) , 105 * int(current_frame), 90 , 95)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        //std::cout << "uuuuuuuuuuuuu" << "\n";
        //std::cout << current_frame << "  BLABLA   \n";
    }

    if (dir.down) {
        current_frame += 11*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 2) current_frame -= 2; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect(16 , 105 * int(current_frame), 82 , 90)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        //std::cout << "dddddddddddddddddd" << "\n";
        // std::cout << current_frame << "BLABLA\n";

    }


}