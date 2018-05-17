
#ifndef GAME_H
#define GAME_H



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Items.h"
#include "Level.h"
#include "Player.h"
#include "Bomb.h"
#include "Enemies.h"

class Game
{
    public:
        Game();
        ~Game();

        void Run();
        void UpdateGame(float deltaTime);
        void DrawGame();
        void SetScale(float x, float y);

    private:
        sf::RenderWindow m_window;
        sf::Music m_music;
        sf::Sound m_sound;


        Items* m_items;
        Level* m_level;
        Player* m_player;
        Bomb* m_bomb;
        Enemies* m_enemy;

        sf::Texture txt;
        sf::Sprite The_end;
        sf::Music game_over;
        sf::Clock go_time;
        bool goplay = false;
};

#endif // GAME_H
