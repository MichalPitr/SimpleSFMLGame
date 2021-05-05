//
// Created by michal on 05.05.21.
//

#include "Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game() {
    delete this->window;
}

void Game::update() {
    this->pollEvents();

    if (!this->endGame)
    {
        this->updateMousePos();
        this->updateText();
        this->updateEnemies();
    }
    //end game condition
    if (this->health <= 0){
        this->endGame = true;
    }

}

void Game::render() {
    /*
     * @return void
     *  - Clear old frame
     *  - Render objects
     *  - Display frame to the window
     */
    this->window->clear();

    //Draw Game
//    this->window->draw(this->enemy);
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}

void Game::initVariables() {
    this->endGame = false;
    this->window = nullptr;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 15.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Falling Blocks",
                                        sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

}

void Game::initEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);

}

bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyReleased:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}



void Game::updateMousePos() {
    /*
     * @return void
     * updates the mouse positions wrt window.
     */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::spawnEnemy() {
    /*
     * @return void
     *
     * Spawns enemies and sets their colors and positions
     *  - Sets a random position
     *  - Sets a random color
     *  - Adds enemy to vector
     */
    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.f
            );

    this->enemy.setFillColor(sf::Color::Green);

    //Spawn enemy
    this->enemies.push_back(this->enemy);

}

void Game::updateEnemies() {

    /*
     * Updates the enemy spawn timer and spawns enemies if not max enemies spawned.
     * moves enemies downwards
     * remove enemy at the edge of the screen
     */

    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //move enemies
    for (int i = 0; i < this->enemies.size(); i++) {
        bool deleted {false};

        this->enemies[i].move(0.f, 2.f);

        //Check if enemy ran out of screen, delete
        if (this->enemies[i].getPosition().y > this->videoMode.height) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }

    //check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->mouseHeld)
        {
            this->mouseHeld = true;
            bool deleted {false};
            for (size_t i = 0; i < this->enemies.size() && !deleted; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    //delete enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin()+i);

                    this->points += 1;
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e: this->enemies){
        target.draw(e);
    }
}

bool Game::getEndGame() const {
    return this->endGame;
}

void Game::initFonts() {
    if(this->font.loadFromFile("../media/UbuntuMono-B.ttf"))
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << '\n';
}

void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << '\n'
        <<"Health: " << this->health << '\n';
    this->uiText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}



