//
// Created by denis on 25.05.2020.
//

#include <iostream>
#include "Menus.h"



void menuInit(sf::RenderWindow &window, std::string& username_str, std::string& host_str, std::string& port_str, std::string& command_str, std::string& lobby_str, int join_error) {
    sf::Texture menuBGTexture, newGameInitTexture, newGameBloodTexture, joinInitTexture, joinBloodTexture, goInitTexture, goBloodTexture,
            exitInitTexture, exitBloodTexture, backInitTexture, backBloodTexture, createInitTexture, createBloodTexture, joinLobbyInitTexture, joinLobbyBloodTexture;

    sf::Music music;
    music.openFromFile("../../client/music/menuTheme.wav");
    music.setVolume(1);
    music.play();

    backInitTexture.loadFromFile("../../client/menuTextures/backInit.png");
    backBloodTexture.loadFromFile("../../client/menuTextures/backBlood.png");
    menuBGTexture.loadFromFile("../../client/menuTextures/sandStorm.jpg");
    exitInitTexture.loadFromFile("../../client/menuTextures/exitInit.png");
    exitBloodTexture.loadFromFile("../../client/menuTextures/exitBlood.png");
    newGameInitTexture.loadFromFile("../../client/menuTextures/newGameInit.png");
    newGameBloodTexture.loadFromFile("../../client/menuTextures/newGameBlood.png");
    joinInitTexture.loadFromFile("../../client/menuTextures/joinInit.png");
    joinBloodTexture.loadFromFile("../../client/menuTextures/joinBlood.png");

    createInitTexture.loadFromFile("../../client/menuTextures/createInit.png");
    createBloodTexture.loadFromFile("../../client/menuTextures/createBlood.png");

    joinLobbyInitTexture.loadFromFile("../../client/menuTextures/joinLobbyInit.png");
    joinLobbyBloodTexture.loadFromFile("../../client/menuTextures/joinLobbyBlood.png");

    sf::Sprite menuBg(menuBGTexture);
    sf::Sprite newGameInit(newGameInitTexture);
    sf::Sprite newGameBlood(newGameBloodTexture);
    sf::Sprite joinInit(joinInitTexture);
    sf::Sprite joinBlood(joinBloodTexture);
    sf::Sprite goInit(goInitTexture);
    sf::Sprite goBlood(goBloodTexture);
    sf::Sprite exitInit(exitInitTexture);
    sf::Sprite exitBlood(exitBloodTexture);
    sf::Sprite backInit(backInitTexture);
    sf::Sprite backBlood(backBloodTexture);

    sf::Sprite createInit(createInitTexture);
    sf::Sprite createBlood(createBloodTexture);

    sf::Sprite joinLobbyInit(joinLobbyInitTexture);
    sf::Sprite joinLobbyBlood(joinLobbyBloodTexture);

    menuBg.setPosition(0, 0);
    newGameInit.setPosition(390, 100);
    newGameBlood.setPosition(390, 100);

    joinInit.setPosition(390, 200);
    joinBlood.setPosition(390, 200);

    goInit.setPosition(250, 660);
    goBlood.setPosition(250, 660);

    exitInit.setPosition(390, 300);
    exitBlood.setPosition(390, 300);

    backInit.setPosition(1050, 610);
    backBlood.setPosition(1050, 610);

    joinLobbyInit.setPosition(650, 600);
    joinLobbyBlood.setPosition(650, 600);

    createInit.setPosition(650, 600);
    createBlood.setPosition(650, 600);




    start:

    bool newGameBloodDraw = false;
    bool joinBloodDraw = false;
    bool backBloodDraw = false;
    bool exitBloodDraw = false;
    bool initMenu = true;
    bool createMenu = false;
    bool joinMenu = false;
    bool exitMenu = false;

    if (join_error) {
        initMenu = false;
        joinMenu = true;
    }

    username_str.clear();
    host_str.clear();
    port_str.clear();
    command_str.clear();
    lobby_str.clear();


    while (initMenu) {
        window.draw(menuBg);

        sf::Event event;
        while (window.pollEvent(event)) {

            if (sf::IntRect(newGameInit.getPosition().x, newGameInit.getPosition().y,
                            newGameInit.getTextureRect().width, newGameInit.getTextureRect().height).contains(
                    sf::Mouse::getPosition(window)))
                newGameBloodDraw = true;
            else
                newGameBloodDraw = false;

            if (sf::IntRect(joinInit.getPosition().x, joinInit.getPosition().y,
                            joinInit.getTextureRect().width, joinInit.getTextureRect().height).contains(
                    sf::Mouse::getPosition(window)))
                joinBloodDraw = true;
            else
                joinBloodDraw = false;

            if (sf::IntRect(exitInit.getPosition().x, exitInit.getPosition().y,
                            exitInit.getTextureRect().width, exitInit.getTextureRect().height).contains(
                    sf::Mouse::getPosition(window)))
                exitBloodDraw = true;
            else
                exitBloodDraw = false;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::IntRect(newGameInit.getPosition().x, newGameInit.getPosition().y,
                                newGameInit.getTextureRect().width, newGameInit.getTextureRect().height).contains(
                        sf::Mouse::getPosition(window))) {
                    initMenu = false;
                    createMenu = true;
                    command_str = "create";
                }

                if (sf::IntRect(joinInit.getPosition().x, joinInit.getPosition().y,
                                joinInit.getTextureRect().width, joinInit.getTextureRect().height).contains(
                        sf::Mouse::getPosition(window))) {
                    initMenu = false;
                    joinMenu = true;
                    command_str = "join";
                }

                if (sf::IntRect(exitInit.getPosition().x, exitInit.getPosition().y,
                                exitInit.getTextureRect().width, exitInit.getTextureRect().height).contains(
                        sf::Mouse::getPosition(window))) {
                    initMenu = false;
                    exitMenu = true;
                    command_str = "exit";
                }

            }
        }
        if (newGameBloodDraw)
            window.draw(newGameBlood);
        else
            window.draw(newGameInit);

        if (joinBloodDraw)
            window.draw(joinBlood);
        else
            window.draw(joinInit);

        if (exitBloodDraw)
            window.draw(exitBlood);
        else
            window.draw(exitInit);

        window.display();
    }

    sf::Font font;
    font.loadFromFile("../../client/menuTextures/font.ttf");


    sf::Text textUsernameInvite;
    textUsernameInvite.setFont(font);
    textUsernameInvite.setString("Username:");
    textUsernameInvite.setCharacterSize(24);
    textUsernameInvite.setFillColor(sf::Color::Red);
    textUsernameInvite.setPosition(300, 50);

    sf::Text textHostInvite;
    textHostInvite.setFont(font);
    textHostInvite.setString("Host:");
    textHostInvite.setCharacterSize(24);
    textHostInvite.setFillColor(sf::Color::Red);
    textHostInvite.setPosition(300, 200);

    sf::Text textPortInvite;
    textPortInvite.setFont(font);
    textPortInvite.setString("Port:");
    textPortInvite.setCharacterSize(24);
    textPortInvite.setFillColor(sf::Color::Red);
    textPortInvite.setPosition(300, 350);

    sf::Text textLobbyInvite;
    textLobbyInvite.setFont(font);
    textLobbyInvite.setString("Lobby #:");
    textLobbyInvite.setCharacterSize(24);
    textLobbyInvite.setFillColor(sf::Color::Red);
    textLobbyInvite.setPosition(300, 500);

    sf::RectangleShape usernameInputField(sf::Vector2f(500, 50));
    usernameInputField.setFillColor(sf::Color::Black);
    usernameInputField.setPosition(100, 100);

    sf::RectangleShape hostInputField(sf::Vector2f(500, 50));
    hostInputField.setFillColor(sf::Color::Black);
    hostInputField.setPosition(100, 250);

    sf::RectangleShape portInputField(sf::Vector2f(500, 50));
    portInputField.setFillColor(sf::Color::Black);
    portInputField.setPosition(100, 400);

    sf::RectangleShape lobbyInputField(sf::Vector2f(500, 50));
    lobbyInputField.setFillColor(sf::Color::Black);
    lobbyInputField.setPosition(100, 550);


    sf::Text joinErrorText;
    joinErrorText.setFont(font);
    joinErrorText.setString("Join Error");
    joinErrorText.setCharacterSize(34);
    joinErrorText.setFillColor(sf::Color::Red);
    joinErrorText.setPosition(650, 550);



    sf::Text textUsername;
    textUsername.setFont(font);
    textUsername.setString("");
    textUsername.setCharacterSize(24);
    textUsername.setFillColor(sf::Color::Red);
    textUsername.setPosition(100, 100);

    sf::Text textHost;
    textHost.setFont(font);
    textHost.setString("");
    textHost.setCharacterSize(24);
    textHost.setFillColor(sf::Color::Red);
    textHost.setPosition(100, 250);

    sf::Text textPort;
    textPort.setFont(font);
    textPort.setString("");
    textPort.setCharacterSize(24);
    textPort.setFillColor(sf::Color::Red);
    textPort.setPosition(100, 400);

    sf::Text textLobby;
    textLobby.setFont(font);
    textLobby.setString("");
    textLobby.setCharacterSize(24);
    textLobby.setFillColor(sf::Color::Red);
    textLobby.setPosition(100, 550);

    bool goBloodDraw = false;
    bool inUsernameInputField = false;
    bool inHostInputField = false;
    bool inPortInputField = false;
    bool inLobbyInputField = false;

    while (createMenu) {
        window.draw(menuBg);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered && ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                    (event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= '0' && event.text.unicode <= '9') ||
                    (event.text.unicode == '.') || (event.text.unicode == '\b'))) {
                if (inUsernameInputField) {
                    if (event.text.unicode == '\b') {
                        if (username_str.length() > 0)
                            username_str.erase(username_str.end() - 1);
                    }
                    else
                        username_str += event.text.unicode;
                    textUsername.setString(username_str);
                }
                if (inHostInputField) {
                    if (event.text.unicode == '\b') {
                        if (host_str.length() > 0)
                            host_str.erase(host_str.end() - 1);
                    }
                    else
                        host_str += event.text.unicode;

                    textHost.setString(host_str);
                }
                if (inPortInputField) {
                    if (event.text.unicode == '\b') {
                        if (port_str.length() > 0)
                            port_str.erase(port_str.end() - 1);
                    }
                    else
                        port_str += event.text.unicode;
                    textPort.setString(port_str);
                }
            }

            if (sf::IntRect(createBlood.getPosition().x, createBlood.getPosition().y,
                            createBloodTexture.getSize().x, createBloodTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                goBloodDraw = true;
            else
                goBloodDraw = false;

            if (sf::IntRect(backInit.getPosition().x, backInit.getPosition().y,
                                 backInitTexture.getSize().x, backInitTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                backBloodDraw = true;
            else
                backBloodDraw = false;



            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::IntRect(createBlood.getPosition().x, createBlood.getPosition().y,
                                createBloodTexture.getSize().x, createBloodTexture.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    createMenu = false;
                    joinMenu = false;
                }

                else if (sf::IntRect(backInit.getPosition().x, backInit.getPosition().y,
                                     backInitTexture.getSize().x, backInitTexture.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    join_error = 0;
                    goto start;
                }

                if (sf::IntRect(usernameInputField.getPosition().x, usernameInputField.getPosition().y,
                                usernameInputField.getSize().x, usernameInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = true;
                    inHostInputField = false;
                    inPortInputField = false;
                }

                if (sf::IntRect(hostInputField.getPosition().x, hostInputField.getPosition().y,
                                hostInputField.getSize().x, hostInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = false;
                    inHostInputField = true;
                    inPortInputField = false;
                }

                if (sf::IntRect(portInputField.getPosition().x, portInputField.getPosition().y,
                                portInputField.getSize().x, portInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = false;
                    inHostInputField = false;
                    inPortInputField = true;
                }
            }

        }

        window.draw(textUsernameInvite);
        window.draw(textHostInvite);
        window.draw(textPortInvite);


        window.draw(usernameInputField);
        window.draw(hostInputField);
        window.draw(portInputField);

        window.draw(textUsername);
        window.draw(textHost);
        window.draw(textPort);

        if(goBloodDraw)
            window.draw(createBlood);
        else
            window.draw(createInit);

        if(backBloodDraw)
            window.draw(backBlood);
        else
            window.draw(backInit);

        window.display();
    }

    joinMenuLabel:
    while(joinMenu) {
        window.draw(menuBg);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered && ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
               (event.text.unicode >= 'a' && event.text.unicode <= 'z') || (event.text.unicode >= '0' && event.text.unicode <= '9') ||
               (event.text.unicode == '.') || (event.text.unicode == '\b'))) {
                if (inUsernameInputField) {
                    if (event.text.unicode == '\b') {
                        if (username_str.length() > 0)
                            username_str.erase(username_str.end() - 1);
                    }
                    else
                        username_str += event.text.unicode;
                    textUsername.setString(username_str);
                }
                if (inHostInputField) {
                    if (event.text.unicode == '\b') {
                        if (host_str.length() > 0)
                            host_str.erase(host_str.end() - 1);
                    }
                    else
                        host_str += event.text.unicode;
                    textHost.setString(host_str);
                }
                if (inPortInputField) {
                    if (event.text.unicode == '\b') {
                        if (port_str.length() > 0)
                            port_str.erase(port_str.end() - 1);
                    }
                    else
                        port_str += event.text.unicode;
                    textPort.setString(port_str);
                }

                if (inLobbyInputField) {
                    if (event.text.unicode == '\b') {
                        if (lobby_str.length() > 0)
                            lobby_str.erase(lobby_str.end() - 1);
                    }
                    else
                        lobby_str += event.text.unicode;
                    textLobby.setString(lobby_str);
                }

            }

            if (sf::IntRect(joinLobbyInit.getPosition().x, joinLobbyInit.getPosition().y,
                            joinLobbyInitTexture.getSize().x, joinLobbyInitTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                goBloodDraw = true;
            else
                goBloodDraw = false;

            if (sf::IntRect(backInit.getPosition().x, backInit.getPosition().y,
                    backInitTexture.getSize().x, backInitTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                backBloodDraw = true;
            else
                backBloodDraw = false;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::IntRect(joinLobbyInit.getPosition().x, joinLobbyInit.getPosition().y,
                                joinLobbyInitTexture.getSize().x, joinLobbyInitTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                    joinMenu = false;

                else if (sf::IntRect(backInit.getPosition().x, backInit.getPosition().y,
                                     backInitTexture.getSize().x, backInitTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                    goto start;

                else if (sf::IntRect(usernameInputField.getPosition().x, usernameInputField.getPosition().y,
                                     usernameInputField.getSize().x, usernameInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = true;
                    inHostInputField = false;
                    inPortInputField = false;
                    inLobbyInputField = false;
                }

                else if (sf::IntRect(hostInputField.getPosition().x, hostInputField.getPosition().y,
                                     hostInputField.getSize().x, hostInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = false;
                    inHostInputField = true;
                    inPortInputField = false;
                    inLobbyInputField = false;
                }

                else if (sf::IntRect(portInputField.getPosition().x, portInputField.getPosition().y,
                                     portInputField.getSize().x, portInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = false;
                    inHostInputField = false;
                    inPortInputField = true;
                    inLobbyInputField = false;
                }

                else if (sf::IntRect(lobbyInputField.getPosition().x, lobbyInputField.getPosition().y,
                                     lobbyInputField.getSize().x, lobbyInputField.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    inUsernameInputField = false;
                    inHostInputField = false;
                    inPortInputField = false;
                    inLobbyInputField = true;
                }

                else {
                    inUsernameInputField = false;
                    inHostInputField = false;
                    inPortInputField = false;
                    inLobbyInputField = false;
                }
            }

        }

        window.draw(textUsernameInvite);
        window.draw(textHostInvite);
        window.draw(textPortInvite);
        window.draw(textLobbyInvite);


        window.draw(usernameInputField);
        window.draw(hostInputField);
        window.draw(portInputField);
        window.draw(lobbyInputField);

        window.draw(textUsername);
        window.draw(textHost);
        window.draw(textPort);
        window.draw(textLobby);

        if(goBloodDraw)
            window.draw(joinLobbyBlood);
        else
            window.draw(joinLobbyInit);

        if(backBloodDraw)
            window.draw(backBlood);
        else
            window.draw(backInit);

        if (join_error) {
            window.draw(joinErrorText);
        }

        window.display();
    }

    //music.stop();
}

void menuDeath(sf::RenderWindow &window, int kills) {
    sf::Texture menuBGTexture, exitInitTexture, exitBloodTexture, uRDeadTexture, scoreTexture;
    //sf::Music music;
    //music.openFromFile("../../client/music/menuTheme.wav");
    //music.play();

    sf::Text score_text;
    sf::Font font;
    font.loadFromFile("../../client/menuTextures/font.ttf");
    score_text.setFont(font);
    score_text.setString(std::to_string(kills));
    score_text.setFillColor(sf::Color::Red);
    score_text.setPosition(565, 230);

    scoreTexture.loadFromFile("../../client/menuTextures/finalScore.png");
    sf::Sprite score(scoreTexture);
    score.setPosition(100, 200);

    menuBGTexture.loadFromFile("../../client/menuTextures/death.jpg");
    sf::Sprite menuBg(menuBGTexture);
    menuBg.setPosition(0, 0);

    uRDeadTexture.loadFromFile("../../client/menuTextures/urDead.png");
    sf::Sprite uRDead(uRDeadTexture);
    uRDead.setPosition(100, 100);

    std::cout << "LOADED" << std::endl;

    exitInitTexture.loadFromFile("../../client/menuTextures/exitFGInit.png");
    sf::Sprite exitInit(exitInitTexture);
    exitInit.setPosition(400, 400);

    exitBloodTexture.loadFromFile("../../client/menuTextures/exitFGBlood.png");
    sf::Sprite exitBlood(exitBloodTexture);
    exitBlood.setPosition(400, 400);

    bool exitMenu = true;

    bool exitBloodDraw = false;
    while (exitMenu) {
        window.draw(menuBg);

        sf::Event event;
        while (window.pollEvent(event)) {

            if (sf::IntRect(exitInit.getPosition().x, exitInit.getPosition().y,
                            exitInit.getTextureRect().width, exitInit.getTextureRect().height).contains(
                    sf::Mouse::getPosition(window)))
                exitBloodDraw = true;
            else
                exitBloodDraw = false;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::IntRect(exitInit.getPosition().x, exitInit.getPosition().y,
                                exitInit.getTextureRect().width, exitInit.getTextureRect().height).contains(
                        sf::Mouse::getPosition(window))) {
                    exitMenu = false;
                }
            }
        }
        if (exitBloodDraw)
            window.draw(exitBlood);
        else
            window.draw(exitInit);

        window.draw(uRDead);
        window.draw(score);
        window.draw(score_text);

        window.display();
    }
}


void menuLobby(sf::RenderWindow &window, Client& client) {
    sf::Packet packet;
    sf::Texture menuBGTexture, goInitTexture, goBloodTexture, idBloodTexture, urLobbyIDTexture;

    sf::Text users_text;
    sf::Text id_text;
    sf::Font font;
    font.loadFromFile("../../client/menuTextures/font.ttf");
    users_text.setFont(font);
    id_text.setFont(font);

    //score_text.setString("qwe");
    users_text.setFillColor(sf::Color::Red);
    id_text.setFillColor(sf::Color::Red);
    users_text.setPosition(10, 5);
    id_text.setPosition(665, 345);

    id_text.setString(std::to_string(client.session_id));

    urLobbyIDTexture.loadFromFile("../../client/menuTextures/idBlood.png");
    sf::Sprite urLobbyID(urLobbyIDTexture);
    urLobbyID.setPosition(500, 300);

    menuBGTexture.loadFromFile("../../client/menuTextures/sandStorm.jpg");
    sf::Sprite menuBG(menuBGTexture);
    menuBG.setPosition(0, 0);

    goBloodTexture.loadFromFile("../../client/menuTextures/goLobbyBlood.png");
    sf::Sprite goBlood(goBloodTexture);
    goBlood.setPosition(500, 600);

    goInitTexture.loadFromFile("../../client/menuTextures/goLobbyInit.png");
    sf::Sprite goInit(goInitTexture);
    goInit.setPosition(500, 600);

    bool lobbyMenu = true;
    bool goBloodDraw = false;
    bool isSended = false;


    std::shared_ptr<User> usr = client.get_user();
    while (lobbyMenu) {

        trans::UserToServerLobbyWaitingMessage msg_end;
        msg_end.set_waitingisover(false);
        if (client.is_creator) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (sf::IntRect(goInit.getPosition().x, goInit.getPosition().y,
                                goInit.getTextureRect().width, goInit.getTextureRect().height).contains(
                        sf::Mouse::getPosition(window))) {
                    goBloodDraw = true;
                } else {
                    goBloodDraw = false;
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (sf::IntRect(goInit.getPosition().x, goInit.getPosition().y,
                                    goInit.getTextureRect().width, goInit.getTextureRect().height).contains(
                            sf::Mouse::getPosition(window))) {
                        msg_end.set_waitingisover(true);
                    }
                }
            }
        }

        packet.clear();
        packet << msg_end;
        usr->send_packet(packet);

        packet.clear();

        while (usr->receive_packet(packet) != sf::Socket::Done) {
        }

        trans::ServerToUserLobbyWaitingMessage message;
        packet >> message;
        if (message.waitingisover()) {
            std::cout << "WAITING IS OVER" << std::endl;
            lobbyMenu = false;
            continue;
        }

        users_text.setString(message.names());

        window.draw(menuBG);
        if (client.is_creator) {
            if (goBloodDraw)
                window.draw(goBlood);
            else
                window.draw(goInit);
        }
        window.draw(users_text);
        window.draw(urLobbyID);
        window.draw(id_text);
        window.draw(users_text);
        window.display();
    }
}