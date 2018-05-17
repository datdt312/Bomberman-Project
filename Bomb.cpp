#include "Bomb.h"

Bomb::Bomb(Player& player, Level& level)
{
    max_number_bomb = 1;
    UpdateLongBOMB(player);
    UpdateMaxBOMB(player);

    b_width = player.shape_width + 6;
    b_height = player.shape_height + 6;

    pos_Size_X = level.m_layers[0][0].getGlobalBounds().width;
    pos_Size_Y = level.m_layers[0][0].getGlobalBounds().height;

    ahihi_Bomb.setSize(sf::Vector2f(b_width, b_height));
    ahihi_Bomb.setFillColor(sf::Color::Cyan);
    ahihi_Bomb.setOrigin(sf::Vector2f(b_width/2, b_height/2));

    b_map_width = level.GetWidth();
    b_map_height = level.GetHeight();

    b_data.resize(b_map_height);
    for (int i=0; i<b_map_height; i++)
    {
        b_data[i].resize(b_map_width);
        for (int j=0; j<b_map_width; j++)
            b_data[i][j] = 0;
    }

    /// Create a new bomb
    //numberOfBomb = CreateNewBomb();

    if (!textureBomb.loadFromFile("img/Bomb.png"))
    {
        std::cout << "Cannot load bomaAnimation ! " << std::endl;
    }

    bomb_width = textureBomb.getSize().x / 4;
    bomb_height = textureBomb.getSize().y;
    ///std::cout << bomb_width << ' ' << bomb_height << std::endl;

    sheet_Bomb.setTexture(textureBomb);
    sheet_Bomb.setColor(sf::Color::White);
    sheet_Bomb.setOrigin(bomb_width/2,bomb_height/2);
    //sheet_Bomb.scale(0.8,0.8);


    /// Explode bomb

    if (!e_texture.loadFromFile("img/BombExplode.png"))
    {
        std::cout << "Cannot load Explode Picture ! " << std::endl;
    }

    e_txt_width = e_texture.getSize().x / 4;
    e_txt_height = e_texture.getSize().y / 7;

    ///std::cout << "e_txt: " << e_txt_width << " _ _ _ " << e_txt_height << std::endl;

}

Bomb::~Bomb()
{

}

void Bomb::UpdateLongBOMB(Player& mplayer)
{
    long_bomb = mplayer.longBomb;
}

void Bomb::UpdateMaxBOMB(Player& mplayer)
{
    max_number_bomb = mplayer.numberBomb;
}

void Bomb::CreateNewBomb(int X, int Y)
{
    BOOOM temp_Bomb;
    float posiX = GetBombX(X);
    float posiY = GetBombY(Y);
    ///
    temp_Bomb.bom_s = ahihi_Bomb;

    temp_Bomb.positionX = posiX;
    temp_Bomb.positionY = posiY;
    temp_Bomb.bom_s.setPosition(posiX, posiY);
    ///
    temp_Bomb.timeExplore.restart();
    ///
    temp_Bomb.GTX = X;
    temp_Bomb.GTY = Y;
    ///
    temp_Bomb.Bomb_sprite = sheet_Bomb;
    temp_Bomb.Bomb_sprite.scale(1.4, 1.4);
    temp_Bomb.Bomb_sprite.setPosition(posiX, posiY);
    ///
    temp_Bomb.time_animation.restart();
    ///
    shapeBomb.push_back(temp_Bomb);
}

float Bomb::GetBombX(int X)
{
    return (float)(X + 0.5) * pos_Size_X;
}
float Bomb::GetBombY(int Y)
{
    return (float)(Y + 0.5) * pos_Size_Y;
}

void Bomb::ChuyenNhuongCauThu(BOOOM MotQuaBom)
{
    EXPLODE temp;

    /// Set Location In Map
    temp.E_GTX = MotQuaBom.GTX;
    temp.E_GTY = MotQuaBom.GTY;

    /// Set Position
    temp.E_positionX = MotQuaBom.positionX;
    temp.E_positionY = MotQuaBom.positionY;

    /// Set Time
    temp.time_change.restart();

    /// Set Texture
    temp.e_ngang.setTexture(e_texture);
    temp.e_doc.setTexture(e_texture);
    temp.e_center.setTexture(e_texture);
    temp.e_down.setTexture(e_texture);
    temp.e_left.setTexture(e_texture);
    temp.e_up.setTexture(e_texture);
    temp.e_right.setTexture(e_texture);

    /// Set Scale
    float scl = 2;
    temp.e_ngang.scale(scl, scl);
    temp.e_doc.scale(scl, scl);
    temp.e_center.scale(scl, scl);
    temp.e_down.scale(scl, scl);
    temp.e_left.scale(scl, scl);
    temp.e_up.scale(scl, scl);
    temp.e_right.scale(scl, scl);


    /// Set Origin
    temp.e_ngang.setOrigin(e_txt_width/2, e_txt_height/2);
    temp.e_doc.setOrigin(e_txt_width/2, e_txt_height/2);
    temp.e_center.setOrigin(e_txt_width/2, e_txt_height/2);
    temp.e_down.setOrigin(e_txt_width/2, e_txt_height/2);
    temp.e_left.setOrigin(e_txt_width/2, e_txt_height/2);
    temp.e_up.setOrigin(e_txt_width/2, e_txt_height/2);
    temp.e_right.setOrigin(e_txt_width/2, e_txt_height/2);

    /// Set up
    UpdateExplodingBomb(temp);
    temp.e_long_bomb = long_bomb;

    /// Set Position for
    temp.e_center.setPosition(temp.E_positionX,temp.E_positionY);
    temp.e_doc.setPosition(temp.E_positionX,temp.E_positionY);
    temp.e_ngang.setPosition(temp.E_positionX,temp.E_positionY);



    /// PUSH IN THE BACK
    explode_bomb.push_back(temp);

}

void Bomb::UpdateExplodingBomb(EXPLODE& temp)
{
    temp.e_ngang.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_ngang*e_txt_height, e_txt_width, e_txt_height));
    temp.e_doc.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_doc*e_txt_height, e_txt_width, e_txt_height));
    temp.e_center.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_center*e_txt_height, e_txt_width, e_txt_height));
    temp.e_down.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_down*e_txt_height, e_txt_width, e_txt_height));
    temp.e_left.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_left*e_txt_height, e_txt_width, e_txt_height));
    temp.e_up.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_up*e_txt_height, e_txt_width, e_txt_height));
    temp.e_right.setTextureRect(sf::IntRect(temp.e_time*e_txt_width, temp.num_right*e_txt_height, e_txt_width, e_txt_height));
}

void Bomb::UpdateBomb(Player& mplayer)
{
    UpdateLongBOMB(mplayer);
    UpdateMaxBOMB(mplayer);

    if (shapeBomb.size() > 0)
    {
        if (shapeBomb[0].timeExplore.getElapsedTime().asSeconds() >= 2.5)
        {
            if (!mplayer.Is_Die)
                ChuyenNhuongCauThu(shapeBomb[0]);
            shapeBomb.pop_front();

        }
    }
    if (explode_bomb.size() > 0)
    {
        for (int i = 0; i < explode_bomb.size(); i++)
        {
            if (explode_bomb[i].time_change.getElapsedTime().asMilliseconds() >= 200 && explode_bomb[i].e_time < 4)
            {
                explode_bomb[i].time_change.restart();
                explode_bomb[i].e_time ++;
                //std::cout << i << " _ _ _ " << explode_bomb[i].e_time << std::endl;
                UpdateExplodingBomb(explode_bomb[i]);
            }
            else
            if (explode_bomb[i].e_time >= 4)
            {
                b_data[explode_bomb[i].E_GTY][explode_bomb[i].E_GTX]=0;
                explode_bomb.erase(explode_bomb.begin()+i,explode_bomb.begin()+i+1);
            }
        }
    }
}

bool Bomb::CheckBlock(sf::Sprite sp, Level& mlevel)
{
    if (mlevel.m_data[sp.getPosition().y / pos_Size_Y-0.5][sp.getPosition().x/ pos_Size_X-0.5] != "")
        return 1;
    return 0;
}

bool Bomb::CheckPlayerDie(sf::Sprite sp, Player& mplayer)
{
    if (sp.getGlobalBounds().intersects(mplayer.shape.getGlobalBounds()))
        return 1;
    return 0;
}

bool Bomb::CheckEnemyDie(sf::Sprite sp, sf::Sprite ene)
{
    if (sp.getGlobalBounds().intersects(ene.getGlobalBounds()))
        return 1;
    return 0;
}

void Bomb::Draw(sf::RenderWindow& mWindow, Level& mlevel, Player& mplayer, Enemies& menemy)
{
    for (int id=0; id<shapeBomb.size(); id++)
    {

        if (shapeBomb[id].time_animation.getElapsedTime().asMilliseconds() >= 700)
        {
            shapeBomb[id].time_animation.restart();
            shapeBomb[id].anim = (shapeBomb[id].anim + 1) % 4;
        }
        shapeBomb[id].Bomb_sprite.setTextureRect(sf::IntRect(shapeBomb[id].anim * bomb_width, 0, bomb_width, bomb_height));
        mWindow.draw(shapeBomb[id].Bomb_sprite);
    }

    /// Draw Explode bomb
    for (int i=0; i<explode_bomb.size(); i++)
    {
        mWindow.draw(explode_bomb[i].e_center);
        if (CheckPlayerDie(explode_bomb[i].e_center, mplayer))
        {
            mplayer.Is_Die = true;
        }

        for (int e=0; e<menemy.bosses.size(); e++)
        {
            if (CheckEnemyDie(explode_bomb[i].e_center, menemy.bosses[e].sp))
            {
                menemy.bosses[e].live = false;
                menemy.bosses[e].rekt = 7;
            }
        }

        /// LEFT
        for (int t=1; t<=explode_bomb[i].e_long_bomb; t++)
        {
            if (t<explode_bomb[i].e_long_bomb)
            {
                explode_bomb[i].e_ngang.setPosition(GetBombX(explode_bomb[i].E_GTX-t),GetBombY(explode_bomb[i].E_GTY));
                if (CheckPlayerDie(explode_bomb[i].e_ngang, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_ngang, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_ngang, mlevel))
                    mWindow.draw(explode_bomb[i].e_ngang);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY][explode_bomb[i].E_GTX-t]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX-t, explode_bomb[i].E_GTY);
                    break;
                }
            }
            else
            {
                explode_bomb[i].e_left.setPosition(GetBombX(explode_bomb[i].E_GTX-t),GetBombY(explode_bomb[i].E_GTY));
                if (CheckPlayerDie(explode_bomb[i].e_left, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_left, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }


                if (!CheckBlock(explode_bomb[i].e_left, mlevel))
                    mWindow.draw(explode_bomb[i].e_left);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY][explode_bomb[i].E_GTX-t]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX-t, explode_bomb[i].E_GTY);
                    break;
                }
            }
        }
        /// RIGHT
        for (int t=1; t<=explode_bomb[i].e_long_bomb; t++)
        {
            if (t<explode_bomb[i].e_long_bomb)
            {
                explode_bomb[i].e_ngang.setPosition(GetBombX(explode_bomb[i].E_GTX+t),GetBombY(explode_bomb[i].E_GTY));
                if (CheckPlayerDie(explode_bomb[i].e_ngang, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_ngang, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_ngang, mlevel))
                    mWindow.draw(explode_bomb[i].e_ngang);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY][explode_bomb[i].E_GTX+t]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX+t, explode_bomb[i].E_GTY);
                    break;
                }
            }
            else
            {
                explode_bomb[i].e_right.setPosition(GetBombX(explode_bomb[i].E_GTX+t),GetBombY(explode_bomb[i].E_GTY));
                if (CheckPlayerDie(explode_bomb[i].e_right, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_right, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_right, mlevel))
                    mWindow.draw(explode_bomb[i].e_right);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY][explode_bomb[i].E_GTX+t]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX+t, explode_bomb[i].E_GTY);
                    break;
                }
            }
        }
        /// UP
        for (int t=1; t<=explode_bomb[i].e_long_bomb; t++)
        {
            if (t<explode_bomb[i].e_long_bomb)
            {

                explode_bomb[i].e_doc.setPosition(GetBombX(explode_bomb[i].E_GTX),GetBombY(explode_bomb[i].E_GTY-t));
                if (CheckPlayerDie(explode_bomb[i].e_doc, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_doc, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_doc, mlevel))
                    mWindow.draw(explode_bomb[i].e_doc);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY-t][explode_bomb[i].E_GTX]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX, explode_bomb[i].E_GTY-t);
                    break;
                }
            }
            else
            {
                explode_bomb[i].e_up.setPosition(GetBombX(explode_bomb[i].E_GTX),GetBombY(explode_bomb[i].E_GTY-t));
                if (CheckPlayerDie(explode_bomb[i].e_up, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_up, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_up, mlevel))
                    mWindow.draw(explode_bomb[i].e_up);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY-t][explode_bomb[i].E_GTX]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX, explode_bomb[i].E_GTY-t);
                    break;
                }
            }
        }
        /// DOWN
        for (int t=1; t<=explode_bomb[i].e_long_bomb; t++)
        {
            if (t<explode_bomb[i].e_long_bomb)
            {
                explode_bomb[i].e_doc.setPosition(GetBombX(explode_bomb[i].E_GTX),GetBombY(explode_bomb[i].E_GTY+t));
                if (CheckPlayerDie(explode_bomb[i].e_doc, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                 for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_doc, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_doc, mlevel))
                    mWindow.draw(explode_bomb[i].e_doc);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY+t][explode_bomb[i].E_GTX]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX, explode_bomb[i].E_GTY+t);
                    break;
                }
            }
            else
            {
                explode_bomb[i].e_down.setPosition(GetBombX(explode_bomb[i].E_GTX),GetBombY(explode_bomb[i].E_GTY+t));
                if (CheckPlayerDie(explode_bomb[i].e_down, mplayer))
                {
                    mplayer.Is_Die = true;
                }
                 for (int e=0; e<menemy.bosses.size(); e++)
                {
                    if (CheckEnemyDie(explode_bomb[i].e_down, menemy.bosses[e].sp))
                    {
                        menemy.bosses[e].live = false;
                        menemy.bosses[e].rekt = 7;
                    }
                }
                if (!CheckBlock(explode_bomb[i].e_down, mlevel))
                    mWindow.draw(explode_bomb[i].e_down);
                else
                {
                    if (mlevel.m_data[explode_bomb[i].E_GTY+t][explode_bomb[i].E_GTX]=="weak")
                        mlevel.SetDestroyBrick(explode_bomb[i].E_GTX, explode_bomb[i].E_GTY+t);
                    break;
                }
            }
        }
    }
}
