//
// Created by tsv on 18.04.19.
//

#include <iostream>
#include "Player.h"

Player::Player(sf::Uint64 id, const std::string& username, const sf::Vector2f& position)
        : Object(id, position)
        , m_username(username)
        , m_actor() {
}


void Player::draw(sf::RenderWindow& window, float time, float& current_frame) {
    //std::cout << "ID " << get_id() << " X " << m_position.x << " Y " << m_position.y << "\n";
    this->go_texture(m_dir,time,current_frame,this->m_actor);
    window.draw(m_actor.herosprite);
}

void Player::set_position(const sf::Vector2f& position) {
    Object::set_position(position);
    //m_actor.setPosition(m_position);
    m_actor.herosprite.setPosition(m_position);
}

void Player::set_direction(const Direction dir) {
    m_dir = dir;

}

/*void Player::go_texure(Direction dir, float time, float& current_frame) {
   // std::cout << "time = " << time << "\n";
    if (dir.left) { //если нажата клавиша стрелка влево или англ буква А
        current_frame += 12*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 3) current_frame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect(96 * int(current_frame), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        //std::cout << "llllllllllllllllllllll" << "\n";
    }

    if (dir.right) {
        current_frame += 12*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 3) current_frame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect(96 * int(current_frame), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
       // std::cout << "rrrrrrrrrrrrrr" << "\n";
    }

    if (dir.up) {
        current_frame += 11*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 3) current_frame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect(96 * int(current_frame), 288, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        //std::cout << "uuuuuuuuuuuuu" << "\n";
        //std::cout << current_frame << "  BLABLA   \n";
    }

    if (dir.down) {
        current_frame += 11*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (current_frame > 3) current_frame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
        m_actor.herosprite.setTextureRect(IntRect(96 * int(current_frame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
        //std::cout << "dddddddddddddddddd" << "\n";
       // std::cout << current_frame << "BLABLA\n";

    }

} */

