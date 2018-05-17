#include <SFML/Graphics.hpp>

#include <iostream>
#include "Game.h"

int main()
{
    // Create the main window
    Game* m_game;
    m_game = new Game();
    m_game->Run();

    return EXIT_SUCCESS;
}
