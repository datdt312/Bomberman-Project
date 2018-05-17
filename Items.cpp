#include "Items.h"

Items::Items(Level& mlevel)
{
    //ctor
    SpawnXXX = mlevel.GetTileWidth();
    SpawnYYY = mlevel.GetTileHeight();

    std::cout << "SPAWN XXX YYY " << SpawnXXX << " _ _ _ " << SpawnYYY << std::endl;

    if (!t_b_01.loadFromFile("img/items/bomb01.png"))
    {
        std::cout << "Cannot load BOMB ITEM ! " << std::endl;
    }
    bomb01.setTexture(t_b_01);
    bomb01.setOrigin(t_b_01.getSize().x/2, t_b_01.getSize().y/2);
    bomb01.scale(0.6, 0.6);
    bomb01.setPosition((1+0.5)*SpawnXXX, (3+0.5)*SpawnYYY);

    if (!t_r_01.loadFromFile("img/items/range01.png"))
    {
        std::cout << "Cannot load RANGE ITEM ! " << std::endl;
    }
    range01.setTexture(t_r_01);
    range01.setOrigin(t_r_01.getSize().x/2,t_r_01.getSize().y/2);
    range01.setPosition((6+0.5)*SpawnXXX, (3+0.5)*SpawnYYY);
    range01.scale(0.6, 0.6);

    if (!t_s_01.loadFromFile("img/items/speed01.png"))
    {
        std::cout << "Cannot load SPEED ITEM ! " << std::endl;
    }
    speed01.setTexture(t_s_01);

    std::cout << "SPD RECT " << t_s_01.getSize().x << " - - - " << t_s_01.getSize().y << std::endl;
    speed01.setOrigin(t_s_01.getSize().x/2,t_s_01.getSize().y/2);
    speed01.setPosition((2+0.5)*SpawnXXX, (1+0.5)*SpawnYYY);
    speed01.scale(0.6, 0.6);

    speed02 = speed01;
    speed02.setPosition((3+0.5)*SpawnXXX, (7+0.5)*SpawnYYY);


}

Items::~Items()
{
    //dtor
}

void Items::UpdateItems(Player& mplayer)
{
    if (speed01.getGlobalBounds().intersects(mplayer.shape.getGlobalBounds()))
    {
        mplayer.SPEED_UP();
        std::cout << "SPEED RUN" << mplayer.speedRun << std::endl;
        speed01 = NONE_SPRITE;
    }
    if (speed02.getGlobalBounds().intersects(mplayer.shape.getGlobalBounds()))
    {
        mplayer.SPEED_UP();
        std::cout << "SPEED RUN" << mplayer.speedRun << std::endl;
        speed02 = NONE_SPRITE;
    }
    if (range01.getGlobalBounds().intersects(mplayer.shape.getGlobalBounds()))
    {
        mplayer.LONG_BOMB_UP();
        range01 = NONE_SPRITE;
    }
    if (bomb01.getGlobalBounds().intersects(mplayer.shape.getGlobalBounds()))
    {
        mplayer.NUMBER_BOMB_UP();
        bomb01 = NONE_SPRITE;
    }
}

void Items::Draw(sf::RenderWindow& mWindow)
{
    mWindow.draw(speed01);
    mWindow.draw(speed02);
    mWindow.draw(bomb01);
    mWindow.draw(range01);
}
