//
// Created by michal on 05.05.21.
//

#ifndef SFMLAPP_GAME_H
#define SFMLAPP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
/*
 *  Class that acts as the game engine.
 */

class Game
{
private:
    //Variable
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    //Text
    sf::Text uiText;

    //Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Functions
    void initVariables();
    void initFonts();
    void initText();
    void initWindow();
    void initEnemies();

public:
    //Constructors / Desctructors
    Game();
    virtual ~Game();

    //Accessors
    bool getWindowIsOpen() const;
    bool getEndGame() const;

    //functions
    void spawnEnemy();
    void pollEvents();
    void updateText();
    void updateEnemies();
    void update();

    void renderEnemies(sf::RenderTarget& target);
    void renderText(sf::RenderTarget& target);
    void render();
    void updateMousePos();

};


#endif //SFMLAPP_GAME_H
