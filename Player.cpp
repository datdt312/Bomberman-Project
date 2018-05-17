#include "Player.h"

Player::Player(Level& level)
{
    ///std::cout << "level: " << std::endl;

    m_w = level.GetWidth();
    m_h = level.GetHeight();

    m_width = level.GetTileWidth();
    m_height = level.GetTileHeight();

    stepSizeX = m_width;
    SpawnX = (1*m_width + m_width * 1 / 2);
    stepSizeY = m_height;
    SpawnY = (1*m_height + m_height * 1 / 2);


    shape_width = m_width - 14;
    shape_height = m_height - 14;

    ///std::cout << m_width << "...." << m_height << std::endl; [16;16]
    shape.setSize(sf::Vector2f(shape_width, shape_height));
    shape.setOrigin(sf::Vector2f(shape_width / 2, shape_height / 2));
    ///std::cout << std::endl << std::endl << shape.getSize().x << " ; " << shape.getSize().y << std::endl; [14;14]
    //shape.setFillColor(sf::Color::Red);
    shape.setFillColor(sf::Color::Transparent);

    oldVx = oldVy = -2;

    if (!mTexurePlayer.loadFromFile("img/bombermanMoveNew.png"))
    {
        std::cout << "Cannot load Player!!!" << std::endl;
    }

    sizeX = sizeTextureX = mTexurePlayer.getSize().x / 3 ;
    sizeY = sizeTextureY = mTexurePlayer.getSize().y / 4 ;

    mPlayer.setTexture(mTexurePlayer);
    //mPlayer.scale(1.4,1.4);
    mPlayer.setOrigin(sizeX / 2, sizeY / 2 + 5);


    mPlayer.setPosition(SpawnX, SpawnY);
    shape.setPosition(SpawnX, SpawnY);
    posX = shape.getPosition().x;
    posY = shape.getPosition().y;
    std::cout << "________Shape_________ " << std::endl;
    std::cout << "Origin:  " << shape.getOrigin().x << ' ' << shape.getOrigin().y << std::endl;
    std::cout << "sizeX: " << sizeX << std::endl << "sizeY: " << sizeY << std::endl;
    std::cout << "Global Bound :top   : " << shape.getGlobalBounds().top << std::endl;
    std::cout << "Global Bound :left  : " << shape.getGlobalBounds().left << std::endl;
    std::cout << "Global Bound :width : " << shape.getGlobalBounds().width << std::endl;
    std::cout << "Global Bound :height: " << shape.getGlobalBounds().height << std::endl;



    if (!die_Texture.loadFromFile("img/bombermanDieNew.png"))
    {
        std::cout << "Cannot load bombermanDie in Player ! " << std::endl;
    }
    d_txt_x = die_Texture.getSize().x / 9;
    d_txt_y = die_Texture.getSize().y;
    die_Sprite.setTexture(die_Texture);
    die_Sprite.setOrigin(d_txt_x / 2, d_txt_y / 2);

}

Player::~Player()
{
}

void Player::UpdatePlayer(Level& level, Bomb& bomb, Enemies& enemy, float deltaTime)
{
    if (!Is_Die)
    {
        int vx = 0;
        int vy = 0;

        bool DatBom = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            vx += -1;
            MoveSide = 3;
            Frame += speedRun*2;
        }
        else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            vx += 1;
            MoveSide = 1;
            Frame += speedRun*2;
        }
        else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            vy += -1;
            MoveSide = 0;
            Frame += speedRun*2;
        }
        else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            vy += 1;
            MoveSide = 2;
            Frame += speedRun*2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            DatBom = true;
            //std::cout << "SPACE" << std::endl;
        }

        Is_Moving = (vx!=0 || vy!=0) ? true:false;

        /// Processing . . .

        int oldposX = posX;
        int oldposY = posY;

        posX += vx * deltaTime * speedRun;
        posY += vy * deltaTime * speedRun;

        shape.setPosition(posX, posY);
        mPlayer.setPosition(posX, posY);

        if (!canMove(vx, vy, level))
        {
            posX = oldposX;
            posY = oldposY;
            shape.setPosition(posX, posY);
            mPlayer.setPosition(posX, posY);
        }

        if (DatBom && bomb.b_data[GetY()][GetX()]==0 && bomb.shapeBomb.size() < numberBomb)
        {
            bomb.b_data[GetY()][GetX()] = 1;
            bomb.CreateNewBomb(GetX(), GetY());
        }

        for (int e=0; e<enemy.bosses.size(); e++)
        {
            if (enemy.bosses[e].sp.getGlobalBounds().intersects(shape.getGlobalBounds()))
            {
                Is_Die = true;
                break;
            }
        }
    }
}

bool Player::canMove(int vx, int vy, Level& level)
{
    int locX = GetX() + vx;
    locX = (locX < 0) ? 0 : locX;
    locX = (locX > m_w) ? m_w : locX;

    int locY = GetY() + vy;
    locY = (locY < 0) ? 0 : locY;
    locY = (locY > m_h) ? m_h : locY;

    bool canMove = true;

    if (vx == 0 && vy != 0 && canMove)
    {
        for (int ix = -1; ix <= 1; ix++)
        {
            int newLocX = locX + ix;

            sf::Sprite temp;
            temp = level.m_layers[locY][newLocX];

            if (temp.getGlobalBounds().intersects(shape.getGlobalBounds()))
            {
                canMove = false;
                break;
            }
        }
    }
    if (vy == 0 && vx != 0 && canMove)
    {
        for (int iy = -1; iy <= 1; iy++)
        {
            int newLocY = locY + iy;
            sf::Sprite temp;
            temp = level.m_layers[newLocY][locX];

            if (temp.getGlobalBounds().intersects(shape.getGlobalBounds()))
            {
                canMove = false;
                break;
            }
        }
    }
    return canMove;
}


void Player::SPEED_UP()
{
    speedRun += 0.02;
}

void Player::LONG_BOMB_UP()
{
    longBomb += 1;
}

void Player::NUMBER_BOMB_UP()
{
    numberBomb += 1;
}

int Player::GetX()
{
    return (int)(posX / m_width);
}
int Player::GetY()
{
    return (int)(posY / m_height);
}

void Player::Draw(sf::RenderWindow &mWindow, Bomb& mbomb)
{
    if (!Is_Die)
    {
        if (MoveSide>=0)
        {
            mPlayer.setTextureRect(sf::IntRect(((int)Frame % 3) * sizeTextureX, MoveSide * sizeTextureY, sizeTextureX, sizeTextureY));
            MoveSide = -MoveSide;
        }
        else
        {
            mPlayer.setTextureRect(sf::IntRect(0, -MoveSide * sizeTextureY, sizeTextureX, sizeTextureY));
        }

        if (!Is_Moving)
            Frame = 0;

        ///std::cout << "_Block_ : " << GetX() << " . " << GetY() << std::endl;



        ///mWindow.draw(mPlayer);
        mWindow.draw(shape);
        mWindow.draw(mPlayer);

        //mWindow.draw(mPlayer);
    }
    else
    {
        if (clock_DIE.getElapsedTime().asMilliseconds() >= 300)
        {
            clock_DIE.restart();
            time_DIE ++;
        }
        die_Sprite.setTextureRect(sf::IntRect(time_DIE * d_txt_x, 0, d_txt_x, d_txt_y));
        die_Sprite.setPosition(posX, posY);
        mWindow.draw(die_Sprite);

        if (time_DIE > 9)
        {
            GAME_OVER = true;
            return;
        }
    }

}
