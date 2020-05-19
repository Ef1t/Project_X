//
// Created by tsv on 18.04.19.
//

#include "Session.h"
#include "messages/ServerToUserMessage.h"
#include "iostream"

sf::Uint64 Session::next_id = 10;

Session::Session()
        : m_id(next_id++)
        , m_users()
        , m_messages() {
}

void Session::update(float dt) {
    for (auto & m_user : m_users) {
        sf::Packet packet;
        auto& user = m_user.first;
        auto& player = m_user.second;
        UserSocket socket = user->get_socket();
        if (socket->receive(packet) == sf::Socket::Done) {
            trans::UserToServerMessage message;
            packet >> message;
           // std:: cout << message.b_direction().up() << " Bullet UP\n";
            //std:: cout << message.b_direction().down() << " Bullet D\n";
           // std:: cout << message.b_direction().right() << " Bullet R\n";
           // std:: cout << message.b_direction().left() << " Bullet L\n";
           // std::cout << '\n';
            if (message.type() == trans::UserToServerMessage::Move) {
                sf::Vector2f dir;
                if (message.direction().up()) {
                    dir.y--;
                }
                if (message.direction().down()) {
                    dir.y++;
                }
                if (message.direction().left()) {
                    dir.x--;
                }
                if (message.direction().right()) {
                    dir.x++;
                }
                //std::cout << player->get_route().fire << " Firesdasadasdsaadsds\n";
                Direction direction = {message.direction().up(), message.direction().left(), message.direction().right(),
                                       message.direction().down(), message.direction().fire()};
                player->apply(dir, direction);

                Direction b_direction = {message.b_direction().up(), message.b_direction().left(), message.b_direction().right(), message.b_direction().down()};

                if (player->get_route().fire == 1) { //если нажата клавижа space, создаем пулю
                    add_bullet(user,player->get_id(), player->get_position().x, player->get_position().y, b_direction);

                    //add_bullet(player->get_id(), 500, 500);

                }


            }
            //стрельба
        }
        user->receive_socket(socket);
    }
    for (auto& item: m_users) {
        auto& player = item.second;

        if (player->m_name == n_player) {
        player->update(dt * 10);
        //std::cout << player->get_route().fire << " Fire\n";
        //std::cout << player->get_route().up << " W\n";

       // std::cout << player->m_name << " Name object\n";

        auto *direction = new trans::UpdatePlayerMessage::Direction;
        direction->set_up(player->get_route().up);
        direction->set_down(player->get_route().down); //почему не зануляются??
        direction->set_left(player->get_route().left);
        direction->set_right(player->get_route().right);

        auto *update_message = new trans::UpdatePlayerMessage;
        update_message->set_id(player->get_id());
        update_message->set_x(player->get_position().x);
        update_message->set_y(player->get_position().y);
        update_message->set_allocated_direction(direction);


        auto server_message = m_messages.add_vec_messages();
        server_message->set_type(trans::ServerToUserMessage::UpdatePlayer);
        server_message->set_allocated_upd_msg(update_message); }



       // if(player->m_name == n_bullet) {
         //   std:: cout << "Hello< Bullet!)\n";
      //  }

        //if (player->get_route().fire == 1) { //если нажата клавижа space, создаем пулю
           // add_bullet(item.first,player->get_id(), player->get_position().x, player->get_position().y);
            //add_bullet(player->get_id(), 500, 500);

       // }
        



    }
      //std::cout << m_bullets.size() << "= SIZE\n";
    for (auto& bullet: m_bullets) {


        //bullet->apply();
       // std::cout << "AAAAAAAAAAA\n";
        //std::cout << bullet->get_position().x << "  BUllet X\n";
        //std::cout << bullet->get_position().y << "  Bullet Y\n";
        puts("");
        bullet->update(dt);
        auto iter = m_bullets.cbegin();
        int i = 0;
        ++i;
        std:: cout << i << " i\n";
       if ((bullet->get_position().x > 1000) || (bullet->get_position().y > 1000) || (bullet->get_position().x < 0) || (bullet->get_position().y < 0) ) {
            std::cout << " JOE\n";
//            m_bullets.erase(m_bullets.begin() + i);
            auto *update_message_bul = new trans::UpdateBulletMessage;
            update_message_bul->set_state(0);
            update_message_bul->set_name(n_bullet);
            auto server_message = m_messages.add_vec_messages();
            server_message->set_type(trans::ServerToUserMessage::UpdateBullet);
            server_message->set_allocated_ub_msg(update_message_bul);
        } else {
        std::cout << m_bullets.size() << " Size\n";
        //std::cout << bullet->get_position().x << "  New BUllet X\n";
       // std::cout << bullet->get_position().y << "  New Bullet Y\n";

////        auto *direction = new trans::UpdateBulletMessage::Direction;
////        direction->set_up(player->get_route().up);
////        direction->set_down(player->get_route().down); //почему не зануляются??
////        direction->set_left(player->get_route().left);
////        direction->set_right(player->get_route().right);
//
           auto *update_message_bul = new trans::UpdateBulletMessage;
        //update_message->set_id(player->get_id());
        update_message_bul->set_state(1);
        update_message_bul->set_x(bullet->get_position().x);
        update_message_bul->set_y(bullet->get_position().y);
        update_message_bul->set_name(n_bullet);
        //update_message->set_allocated_direction(direction);
//

        auto server_message = m_messages.add_vec_messages();
        server_message->set_type(trans::ServerToUserMessage::UpdateBullet);
        server_message->set_allocated_ub_msg(update_message_bul);
        }
//
//
//
//
    }

   /* for (auto& item: m_bullets) {
        auto& bullet = item.second;
        bullet->update(dt);
        auto *update_bullet_message = new trans::UpdateBulletMessage;
        update_bullet_message->set_x(bullet->get_position().x);
        update_bullet_message->set_y(bullet->get_position().y);
        std::cout << bullet->get_position().x << " X\n";
        std::cout << bullet->get_position().y << " Y\n";
    } */

    notify_all();
}

bool Session::is_end() {
    return m_users.empty();
}

sf::Uint64 Session::get_id() const {
    return m_id;
}

void Session::add_user(UserPtr user) {
    std::cout << "NEW PLAYER!!!\n";
    auto player = std::make_shared<Player>();
    m_users[user] = player;



    auto new_player_message = new trans::NewPlayerMessage ;
    new_player_message->set_id(player->get_id());
    new_player_message->set_username(user->get_username());
    new_player_message->set_x(player->get_position().x);
    new_player_message->set_y(player->get_position().y);
    new_player_message->set_map_name(this->map_name);

    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_np_msg(new_player_message);
    server_message->set_type(trans::ServerToUserMessage::NewPlayer);

}

void  Session::add_bullet(UserPtr user, sf::Uint64 id, float x, float y, Direction b_dir) {
    auto bullet = std::make_shared<Bullet>(sf::Vector2(x+25, y+25), b_dir);
    //std::cout << b_dir.up << " b_dir UP\n";
//    std::cout << b_dir.down << " b_dir Down\n";
//    std::cout << b_dir.right << " b_dir Right\n";
//    std::cout << b_dir.left << " b_dir Left\n";
    //std::cout  << "\n";
    m_bullets.push_back(bullet);
    //std::cout << bullet->get_position().x << "  BUllet X\n";
    //std::cout << bullet->get_position().y << "  Bullet Y\n";


    //for(int i = 0; i < m_bullets.size(); ++i)
      //  std::cout << m_bullets.size() << "= size\n";
    //m_users[user] = bullet;
    //user->bullets.push_back(id,x,y);
    auto new_bullet_message = new trans::NewBulletMessage;
   // new_bullet_message->set_id(player->get_id());
    //new_bullet_message->set_x(player->get_position().x);
    new_bullet_message->set_id(id);            //ХЗ ПОЧЕМУ НЕ РАБОТАЕТ
    new_bullet_message->set_x(x);
    new_bullet_message->set_y(y);
    new_bullet_message->set_name(n_bullet);
    //std::cout << "X = " << x << "\n";
    //std::cout << "Y = " << y << "\n";

    //new_bullet_message.


    auto server_message = m_messages.add_vec_messages();
    server_message->set_allocated_nb_msg(new_bullet_message);
    server_message->set_type(trans::ServerToUserMessage::NewBullet);


    std:: cout << "BOOM BOOM :)\n";
}

void Session::notify_all() {
    sf::Packet packet;
    packet << m_messages;

    for (auto & m_user: m_users) {
       // std::cout << "X = " << m_user.second->get_position().x << "\n";
       // std::cout << "y = " << m_user.second->get_position().y << "\n";
        m_user.first->send_packet(packet);


    }

    //for (auto & m_bullet: m_bullets) {
     //   std:: cout << "Update BOOM BOOM :)\n";
     //   m_bullet.first->send_packet(packet);
   // }

    m_messages.clear_vec_messages();
    // TODO: check user connection: if sending fails -> remove that user from m_users + add send DeletePlayerMessage to all
}

std::string &Session::get_map() {
    return map_name;
}

