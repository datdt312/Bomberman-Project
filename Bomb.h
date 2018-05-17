#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>

#include <deque>

#include "Level.h"
#include "Player.h"
#include "Enemies.h"

class Player;

class Enemies;

struct BOOOM
{
    int GTX;
    int GTY;
    float positionX;
    float positionY;
    sf::RectangleShape bom_s;
    sf::Sprite Bomb_sprite;
    sf::Clock timeExplore;
    sf::Clock time_animation;
    int anim = 0;
};

struct EXPLODE
{
    int e_long_bomb;
    sf::Clock time_change;
    int E_GTX;
    int E_GTY;
    float E_positionX;
    float E_positionY;

    int e_time = 0;

    int num_ngang = 6;
    sf::Sprite e_ngang;
    int num_doc = 5;
    sf::Sprite e_doc;

    int num_center = 0;
    sf::Sprite e_center;

    int num_left = 2;
    sf::Sprite e_left;

    int num_right = 3;
    sf::Sprite e_right;

    int num_up = 1;
    sf::Sprite e_up;

    int num_down = 4;
    sf::Sprite e_down;



};

class Bomb
{
    public:
        Bomb(Player& player, Level& level);
        ~Bomb();

        void Draw(sf::RenderWindow& mWindow, Level& mlevel, Player& mplayer, Enemies& menemy);
        void CreateNewBomb(int X, int Y);

        void UpdateLongBOMB(Player& mplayer);
        void UpdateMaxBOMB(Player& mplayer);

        void ChuyenNhuongCauThu(BOOOM MotQuaBom);

        float GetBombX(int X);
        float GetBombY(int Y);

        bool CheckBlock(sf::Sprite sp, Level& mlevel);

        void UpdateExplodingBomb(EXPLODE& temp);
        void UpdateBomb(Player& mplayer);

        bool CheckPlayerDie(sf::Sprite sp, Player& mplayer);
        bool CheckEnemyDie(sf::Sprite sp, sf::Sprite ene);

    public:
        sf::Clock b_clock;

        size_t b_width, b_height;
        size_t b_map_width, b_map_height;
        std::vector< std::vector<bool> > b_data;
        size_t pos_Size_X, pos_Size_Y;

        sf::Texture textureBomb;
        sf::Sprite sheet_Bomb;
        sf::RectangleShape ahihi_Bomb;

        std::deque<BOOOM> shapeBomb;

        sf::Texture e_texture;
        int e_txt_width, e_txt_height;
        std::deque<EXPLODE> explode_bomb;


        size_t bomb_width, bomb_height;
        float Frame;
        int long_bomb = 1;
        int max_number_bomb = 1;

        float speed_Change = 0.1;

};

#endif // BOMB_H
