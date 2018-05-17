#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "Level.h"
#include "Bomb.h"
#include "Items.h"
#include "Enemies.h"

class Bomb;

class Items;

class Enemies;

class Player
{
    public:
        Player(Level& level);
        ~Player();

        bool LoadFromFile(const std::string& path);

        void UpdatePlayer(Level& level, Bomb& bomb, Enemies& enemy, float deltaTime);
        bool canMove(int vx, int vy, Level& level);

        float sizeX; float sizeY;
        float sizeTextureX; float sizeTextureY;
        float posX; float posY;

        void SetScale(float x, float y);
        void UpdateAfterScale_Player(Level& level);

        int GetX();
        int GetY();

        void Draw(sf::RenderWindow &mWindow, Bomb& mbomb);


        /// [0]: Up
        /// [1]: Right
        /// [2]: Down
        /// [3]: Left
        int MoveSide=2;
        //std::vector<sf::Event::KeyEvent> Movement;

        void SPEED_UP();
        void LONG_BOMB_UP();
        void NUMBER_BOMB_UP();

    public:
        std::deque<Bomb*>* player_Bombs;
        size_t m_width, m_height;
        int m_w, m_h;

        size_t shape_width, shape_height;

        size_t stepSizeX, stepSizeY;
        int oldVx, oldVy;
        size_t SpawnX, SpawnY;

        sf::Texture mTexurePlayer;
        sf::Sprite mPlayer;
        sf::RectangleShape shape;

        bool Is_Die = false;
        bool Is_Moving = false;

        float Frame=0;
        float oldFrame = -1;
        float speedRun=0.05;
        int numberBomb= 1;
        int longBomb = 1;

        sf::Texture die_Texture;
        sf::Sprite die_Sprite;
        int time_DIE = 0;
        sf::Clock clock_DIE;
        size_t d_txt_x;
        size_t d_txt_y;

        bool GAME_OVER = false;
};

#endif // PLAYER_H
