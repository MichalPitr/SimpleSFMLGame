#include <iostream>
#include "Game.h"


int main()
{
    std::srand(static_cast<unsigned>(time(nullptr)));
    //init Game engine
    Game game;
    while (game.getWindowIsOpen() && !game.getEndGame())
    {

        // Update Game
        game.update();
        //Render Game
        game.render();
    }

    return 0;
}