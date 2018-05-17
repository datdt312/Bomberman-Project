#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Bomb.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <bits/stdc++.h>

struct E_N_E_M_Y
{
    sf::Sprite sp;

    float positionX;
    float positionY;

    int Ene_X;
    int Ene_Y;
    sf::Clock ti_me;
    int rekt = 0;
    bool live;  /// [true]: live    [false]: die

    int direction;
    int vx;
    int vy;
    /// [0]: Up
    /// [1]: Right
    /// [2]: Down
    /// [3]: Left

};

class Bomb;

class Enemies
{
    public:
        Enemies(Level& mlevel);
        virtual ~Enemies();

        void UpdateEnemies(float deltatime, Level& mlevel, Bomb& mbomb);
        bool CanMove(sf::Sprite spr, int vx, int vy, float posX, float posY, Level& mlevel, Bomb& mbomb);
        void Draw(sf::RenderWindow& mWindow);

        int Ene_GetX(float posX);
        int Ene_GetY(float posY);

    public:

        int ene_m_w, ene_m_h;
        float ene_m_tileWidth;
        float ene_m_tileHeight;

        float movementSpeed = 1;

        sf::Texture enemy_texture;
        size_t e_t_x;
        size_t e_t_y;
        std::vector< E_N_E_M_Y > bosses;

        size_t SP_X;
        size_t SP_Y;


    protected:

    private:
};

#endif // ENEMIES_H
