#include "Enemies.h"

Enemies::Enemies(Level& mlevel)
{

    ene_m_w = mlevel.GetWidth();
    ene_m_h = mlevel.GetHeight();

    ene_m_tileWidth  = mlevel.GetTileWidth();
    ene_m_tileHeight = mlevel.GetTileHeight();

    if (!enemy_texture.loadFromFile("img/Enemy.png"))
    {
        std::cout << "Cannot load Enemy ! " << std::endl;
    }
    e_t_x = enemy_texture.getSize().x / 12;
    e_t_y = enemy_texture.getSize().y;
    //ctor

    SP_X = mlevel.GetTileWidth();
    SP_Y = mlevel.GetTileHeight();

    for (int i=0; i<mlevel.enemy_data.size(); i++)
    {
        E_N_E_M_Y ahi;
        ahi.Ene_X = mlevel.enemy_data[i].de_x;
        ahi.Ene_Y = mlevel.enemy_data[i].de_y;

        bosses.push_back(ahi);
    }

    srand(time(0));
    for (int i=0; i<bosses.size(); i++)
    {
        bosses[i].sp.setTexture(enemy_texture);
        bosses[i].sp.setOrigin(e_t_x/2, e_t_y/2);
        bosses[i].sp.scale(1.3, 1.3);

        bosses[i].positionX = (bosses[i].Ene_X + 0.5) * SP_X;
        bosses[i].positionY = (bosses[i].Ene_Y + 0.5) * SP_Y;

        bosses[i].sp.setPosition(bosses[i].positionX, bosses[i].positionY);

        bosses[i].live = true;
        bosses[i].ti_me.restart();

        bosses[i].sp.setTextureRect(sf::IntRect(0, 0, e_t_x, e_t_y));


        bosses[i].direction = rand()%4;

        if (bosses[i].direction == 0)
        {
            bosses[i].vx = 0;
            bosses[i].vy = -1;
        }
        else
        if (bosses[i].direction == 1)
        {
            bosses[i].vx = 1;
            bosses[i].vy = 0;
        }
        else
        if (bosses[i].direction == 2)
        {
            bosses[i].vx = 0;
            bosses[i].vy = 1;
        }
        else
        if (bosses[i].direction == 3)
        {
            bosses[i].vx = -1;
            bosses[i].vy = 0;
        }
    }
}

Enemies::~Enemies()
{
    //dtor
}

bool Enemies::CanMove(sf::Sprite spr, int vx, int vy, float posX, float posY, Level& mlevel, Bomb& mbomb)
{
    bool can_Move = true;

    int locX = Ene_GetX(posX) + vx;
    locX = (locX < 0) ? 0 : locX;
    locX = (locX > ene_m_w) ? ene_m_w : locX;

    int locY = Ene_GetY(posY) + vy;
    locY = (locY < 0) ? 0 : locY;
    locY = (locY > ene_m_h) ? ene_m_h : locY;

    if (vx == 0 && vy != 0 && can_Move)
    {
        for (int ix = -1; ix <= 1; ix++)
        {
            int newLocX = locX + ix;

            sf::Sprite temp;
            temp = mlevel.m_layers[locY][newLocX];

            if (temp.getGlobalBounds().intersects(spr.getGlobalBounds()))
            {
                can_Move = false;
                break;
            }
        }
    }
    if (vy == 0 && vx != 0 && can_Move)
    {
        for (int iy = -1; iy <= 1; iy++)
        {
            int newLocY = locY + iy;
            sf::Sprite temp;
            temp = mlevel.m_layers[newLocY][locX];

            if (temp.getGlobalBounds().intersects(spr.getGlobalBounds()))
            {
                can_Move = false;
                break;
            }
        }
    }

    for (int i=0; i<mbomb.shapeBomb.size(); i++)
    {
        if (mbomb.shapeBomb[i].Bomb_sprite.getGlobalBounds().intersects(spr.getGlobalBounds()))
        {
            can_Move = false;
            break;
        }
    }

    return can_Move;
}

void Enemies::UpdateEnemies(float deltatime, Level& mlevel, Bomb& mbomb)
{
    for (int i=0; i<bosses.size(); i++)
    {
        if (!bosses[i].live)
        {
            if (bosses[i].ti_me.getElapsedTime().asMilliseconds() >= 220)
            {
                bosses[i].ti_me.restart();
                bosses[i].rekt ++;
            }
            bosses[i].sp.setTextureRect(sf::IntRect(bosses[i].rekt * e_t_x, 0, e_t_x, e_t_y));
        }
        if (bosses[i].rekt > 12)
        {
            bosses.erase(bosses.begin()+i);
        }

    }

    for (int i=0; i<bosses.size(); i++)
    {
        if (bosses[i].live == true)
        {
            if (bosses[i].ti_me.getElapsedTime().asMilliseconds() >= 200)
            {
                if (bosses[i].rekt == 7)
                {
                    if (bosses[i].ti_me.getElapsedTime().asMilliseconds() >= 400)
                    {
                        bosses[i].ti_me.restart();
                    }
                }
                else
                {
                    bosses[i].ti_me.restart();
                    bosses[i].rekt = (bosses[i].rekt + 1) % 6;
                }
            }

            bosses[i].sp.setTextureRect(sf::IntRect(bosses[i].rekt * e_t_x, 0, e_t_x, e_t_y));
        }
    }


    for (int i=0; i<bosses.size(); i++)
    {
        if (bosses[i].live)
        {
            float oldPosX = bosses[i].positionX;
            float oldPosY = bosses[i].positionY;

            bosses[i].positionX += bosses[i].vx*movementSpeed;
            bosses[i].positionY += bosses[i].vy*movementSpeed;

            bosses[i].sp.setPosition(bosses[i].positionX, bosses[i].positionY);

            if (!CanMove(bosses[i].sp, bosses[i].vx, bosses[i].vy, bosses[i].positionX, bosses[i].positionY, mlevel, mbomb))
            {
                bosses[i].positionX = oldPosX;
                bosses[i].positionY = oldPosY;
                bosses[i].sp.setPosition(bosses[i].positionX, bosses[i].positionY);

                bosses[i].direction = rand()%4;

                if (bosses[i].direction == 0)
                {
                    bosses[i].vx = 0;
                    bosses[i].vy = -1;
                }
                else
                if (bosses[i].direction == 1)
                {
                    bosses[i].vx = 1;
                    bosses[i].vy = 0;
                }
                else
                if (bosses[i].direction == 2)
                {
                    bosses[i].vx = 0;
                    bosses[i].vy = 1;
                }
                else
                if (bosses[i].direction == 3)
                {
                    bosses[i].vx = -1;
                    bosses[i].vy = 0;
                }
            }
        }
    }
}


void Enemies::Draw(sf::RenderWindow& mWindow)
{
    for (int i=0; i<bosses.size(); i++)
    {
        mWindow.draw(bosses[i].sp);
    }
}



int Enemies::Ene_GetX(float posX)
{
    return (int)(posX / ene_m_tileWidth);
}
int Enemies::Ene_GetY(float posY)
{
    return (int)(posY / ene_m_tileHeight);
}
