
#include "Game.h"

Game::Game()
{
    m_window.create(sf::VideoMode(992, 480), "SFML window", sf::Style::Resize);
    m_window.setFramerateLimit(60);

    if (!m_music.openFromFile("music/knock_knock_twice_8_bits.ogg"))
    {
        std::cout << "Cannot load Music ! " << std::endl;
    }

    m_music.setVolume(100);
    m_music.setLoop(true);
    m_music.play();

    m_level = new Level();
    m_level->SetScale(2, 2);

    m_items = new Items(*m_level);

    m_player = new Player(*m_level);

    m_bomb = new Bomb(*m_player, *m_level);

    m_enemy = new Enemies(*m_level);

    if (!txt.loadFromFile("img/blog-game-over.png"))
    {
        std::cout << "Cannot load GAME_OVER ! " << std::endl;
    }
    The_end.setTexture(txt);
    The_end.scale(1.0/txt.getSize().x*m_window.getSize().x, 1.0/txt.getSize().y*m_window.getSize().y);

    if (!game_over.openFromFile("music/Game_Over.ogg"))
    {
        std::cout << "Cannot load music GAME_OVER ! " << std::endl;
    }

}

Game::~Game()
{


}

void Game::Run()
{
    sf::Clock clock;

    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }
        }
        float dt = clock.getElapsedTime().asMilliseconds();
        //std::cout << "Time:  " << dt << std::endl;
        UpdateGame(dt);
        clock.restart();
        DrawGame();
    }
}


void Game::DrawGame()
{
    m_window.clear(sf::Color(153, 255, 102));
    //system("cls");
    //m_window.clear();
    if (!m_player->GAME_OVER)
    {

        m_items->Draw(m_window);

        m_bomb->Draw(m_window, *m_level, *m_player, *m_enemy);

        m_level->Draw(m_window);

        ///std::cout << m_bomb->numberOfBomb << std::endl;

        m_enemy->Draw(m_window);

        m_player->Draw(m_window, *m_bomb);
        ///std::cout << m_player->Frame << std::endl;
    }
    else
    {
        if (!goplay)
        {
            goplay = true;
            m_music.stop();
            game_over.play();
            go_time.restart();
        }
        m_window.draw(The_end);
        if (go_time.getElapsedTime().asSeconds()>2)
        {
            m_window.close();
            system("exit");
            return;
        }
    }


    m_window.display();
}

void Game::UpdateGame(float deltaTime)
{
    m_bomb->UpdateBomb(*m_player);
    m_player->UpdatePlayer(*m_level, *m_bomb, *m_enemy, deltaTime);
    m_items->UpdateItems(*m_player);
    m_level->UpdateLevel(deltaTime);
    m_enemy->UpdateEnemies(deltaTime, *m_level, *m_bomb);
}
