#ifndef ITEMS_H
#define ITEMS_H

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Level.h"
#include "Player.h"

class Level;

class Player;

class Items
{
    public:
        Items(Level& mlevel);
        virtual ~Items();
        void Draw(sf::RenderWindow& mWindow);
        void UpdateItems(Player& mplayer);

    public:

        size_t SpawnXXX;
        size_t SpawnYYY;

        sf::Sprite NONE_SPRITE;

        sf::Texture t_b_01;
        sf::Sprite bomb01;

        sf::Texture t_r_01;
        sf::Sprite range01;

        sf::Texture t_s_01;
        sf::Sprite speed01;
        sf::Sprite speed02;

        sf::RectangleShape ab;
};

#endif // ITEMS_H
