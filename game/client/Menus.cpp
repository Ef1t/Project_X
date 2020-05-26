//
// Created by denis on 25.05.2020.
//

#include <iostream>
#include "Menus.h"



void menuInit(sf::RenderWindow &window, std::string& username_str, std::string& host_str, std::string& port_str, std::string& command_str, std::string& lobby_str) {
    sf::Texture menuBGTexture, newGameInitTexture, newGameBloodTexture, joinInitTexture, joinBloodTexture, goInitTexture, goBloodTexture,
            exitInitTexture, exitBloodTexture;

    sf::Music music;
    music.openFromFile("../../client/music/menuTheme.wav");
    music.setVolume(2);
    music.play();

    menuBGTexture.loadFromFile("../../client/menuTextures/sandStorm.jpg");
    exitInitTexture.loadFromFile("../../client/menuTextures/exitInit.png");
    exitBloodTexture.loadFromFile("../../client/menuTextures/exitBlood.png");
    newGameInitTexture.loadFromFile("../../client/menuTextures/newGameInit.png");
    newGameBloodTexture.loadFromFile("../../client/menuTextures/newGameBlood.png");
    joinInitTexture.loadFromFile("../../client/menuTextures/joinInit.png");
    joinBloodTexture.loadFromFile("../../client/menuTextures/joinBlood.png");
    goInitTexture.loadFromFile("../../client/menuTextures/goInit.png");
    goBloodTexture.loadFromFile("../../client/menuTextures/goBlood.png");

    sf::Sprite menuBg(menuBGTexture);
    sf::Sprite newGameInit(newGameInitTexture);
    sf::Sprite newGameBlood(newGameBloodTexture);
    sf::Sprite joinInit(joinInitTexture);
    sf::Sprite joinBlood(joinBloodTexture);
    sf::Sprite goInit(goInitTexture);
    sf::Sprite goBlood(goBloodTexture);
    sf::Sprite exitInit(exitInitTexture);
    sf::Sprite exitBlood(exitBloodTexture);

    menuBg.setPosition(0, 0);
    newGameInit.setPosition(390, 100);
    newGameBlood.setPosition(390, 100);

    joinInit.setPosition(390, 200);
    joinBlood.setPosition(390, 200);

    goInit.setPosition(250, 660);
    goBlood.setPosition(250, 660);

    exitInit.setPosition(390, 300);
    exitBlood.setPosition(390, 300);

    bool newGameBloodDraw = false;
    bool joinBloodDraw = false;
    bool exitBloodDraw = false;
    bool initMenu = true;
    bool createMenu = false;
    bool joinMenu = false;
    bool exitMenu = false;
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
            if (event.type == sf::Event::TextEntered) {
                if (inUsernameInputField) {
                    if (event.text.unicode == '\b')
                        username_str.erase(username_str.end() - 1);
                    else
                        username_str += event.text.unicode;
                    textUsername.setString(username_str);
                }
                if (inHostInputField) {
                    if (event.text.unicode == '\b')
                        host_str.erase(host_str.end() - 1);
                    else
                        host_str += event.text.unicode;

                    textHost.setString(host_str);
                }
                if (inPortInputField) {
                    if (event.text.unicode == '\b')
                        port_str.erase(port_str.end() - 1);
                    else
                        port_str += event.text.unicode;
                    textPort.setString(port_str);
                }
            }

            if (sf::IntRect(goBlood.getPosition().x, goBlood.getPosition().y,
                            goBloodTexture.getSize().x, goBloodTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                goBloodDraw = true;
            else
                goBloodDraw = false;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::IntRect(goBlood.getPosition().x, goBlood.getPosition().y,
                                goBloodTexture.getSize().x, goBloodTexture.getSize().y).contains(sf::Mouse::getPosition(window))) {
                    createMenu = false;
                    joinMenu = false;
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
            window.draw(goBlood);
        else
            window.draw(goInit);

        window.display();
    }

    while(joinMenu) {
        window.draw(menuBg);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::TextEntered) {
                if (inUsernameInputField) {
                    if (event.text.unicode == '\b')
                        username_str.erase(host_str.end() - 1);
                    else
                        username_str += event.text.unicode;
                    textUsername.setString(username_str);
                }
                if (inHostInputField) {
                    if (event.text.unicode == '\b')
                        host_str.erase(host_str.end() - 1);
                    else
                        host_str += event.text.unicode;
                    textHost.setString(host_str);
                }
                if (inPortInputField) {
                    if (event.text.unicode == '\b')
                        port_str.erase(host_str.end() - 1);
                    else
                        port_str += event.text.unicode;
                    textPort.setString(port_str);
                }

                if (inLobbyInputField) {
                    if (event.text.unicode == '\b')
                        lobby_str.erase(host_str.end() - 1);
                    else
                        lobby_str += event.text.unicode;
                    textLobby.setString(lobby_str);
                }

            }

            if (sf::IntRect(goBlood.getPosition().x, goBlood.getPosition().y,
                            goBloodTexture.getSize().x, goBloodTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                goBloodDraw = true;
            else
                goBloodDraw = false;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::IntRect(goBlood.getPosition().x, goBlood.getPosition().y,
                                goBloodTexture.getSize().x, goBloodTexture.getSize().y).contains(sf::Mouse::getPosition(window)))
                    joinMenu = false;
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
            window.draw(goBlood);
        else
            window.draw(goInit);

        window.display();
    }

    music.stop();
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