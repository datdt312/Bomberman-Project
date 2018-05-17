#include "Level.h"

#include <iostream>
#include <fstream>

#include "tinyxml.h"

Level::Level()
{
    //ctor
    numScale = 5;

    if (!LoadFromFile("map/ClassicBombMap.tmx"))
    {
        std::cout << "Load MAP failed !!!" << std::endl;
    }
    system("cls");
    std::ofstream fout;
    fout.open("map_information.txt");

    fout << "width      : " << width << std::endl;
    fout << "height     : " << height << std::endl;
    fout << "tileWidth  : " << tileWidth << std::endl;
    fout << "tileHeight : " << tileHeight << std::endl;
    fout << "spacing    : " << spacing << std::endl;
    fout << "margin     : " << margin << std::endl;


    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
            fout << m_data[i][j] << "\t";
        fout << std::endl;
    }

    if (!txt_destroy.loadFromFile("img/Block_Brick.png"))
    {
        std::cout << "Cannot load Block_Brick  Level ! " << std::endl;
    }
}

Level::~Level()
{
    //dtor
}

void Level::Initialize(size_t width, size_t height)
{
    /// [ data ]
    m_data.resize(height);
    for (int i=0; i<height; i++)
    {
        m_data[i].resize(width);

        for (int j=0; j<width; j++)
            m_data[i][j]="";
    }

    /// [ Layers ]
    m_layers.resize(height);

    for (int i=0; i<height; i++)
    {
        m_layers[i].resize(width);
    }
}

void Level::UpdateLevel(float deltaTime)
{

}

bool Level::LoadFromFile(const std::string& filename)
{
    TiXmlDocument levelFile(filename.c_str());

    if (!levelFile.LoadFile())
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    //Map element. This is the root element for the whole file.
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    //Set up misc map properties.
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    /// Set Up [ m_data ]
    Initialize(width, height);
    /// Done ^^!

    //Tileset stuff
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));
    spacing = atoi(tilesetElement->Attribute("spacing"));
    margin = atoi(tilesetElement->Attribute("margin"));



    //Tileset image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");
    while (imagepath[0]=='.' || imagepath[0]=='/')
        imagepath.erase(0,1);

    if (!tilesetImage.loadFromFile(imagepath))//Load the tileset image
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    tilesetImage.createMaskFromColor(sf::Color(255, 0, 255));

    tilesetTexture.loadFromImage(tilesetImage);
    tilesetTexture.setSmooth(false);

    //Columns and rows (of tileset image)
    int columns = tilesetTexture.getSize().x / tileWidth;
    int rows = tilesetTexture.getSize().y / tileHeight;

    std::vector <sf::Rect<int> > subRects;//container of subrects (to divide the tilesheet image up)

    //tiles/subrects are counted from 0, left to right, top to bottom
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            sf::Rect <int> rect;
            rect.top = y * (tileHeight + spacing);
            rect.height = tileHeight;
            rect.left = x * (tileWidth + spacing);
            rect.width = tileWidth;
            subRects.push_back(rect);
        }
    }

    //Layers
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;
        if (layerElement->Attribute("opacity") != NULL)//check if opacity attribute exists
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);//convert the (string) opacity element to float
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;//if the attribute doesnt exist, default to full opacity
        }

        //Tiles
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;//Work out the subrect ID to 'chop up' the tilesheet image.
            if (subRectToUse >= 0)//we only need to (and only can) create a sprite/tile if there is one to display
            {
                sf::Sprite sprite;//sprite for the tile
                sprite.setTexture(tilesetTexture);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);

                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));//Set opacity of the tile.

                m_layers[y][x] = sprite;
            }

            tileElement = tileElement->NextSiblingElement("tile");

            //increment x, y
            x++;
            if (x >= width)//if x has "hit" the end (right) of the map, reset it to the start (left)
            {
                x = 0;
                y++;
                if (y >= height)
                {
                    y = 0;
                }
            }
        }

        layerElement = layerElement->NextSiblingElement("layer");
    }

    //Objects

    TiXmlElement *objectGroupElement;
    if (map->FirstChildElement("objectgroup") != NULL)//Check that there is atleast one object layer
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)//loop through object layers
        {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement)//loop through objects
            {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int width = atoi(objectElement->Attribute("width"));
                int height = atoi(objectElement->Attribute("height"));

                int vtx = x / width;
                int vty = y / height;

                if (objectType == "solid"  || objectType == "weak")
                    m_data[vty][vtx] = objectType;
                if (objectType == "enemy")
                {
                    DataEnemy newer;
                    newer.de_x = vtx;
                    newer.de_y = vty;

                    enemy_data.push_back(newer);
                }

                //std::cout << vtx << ' ' << vty << ' ' << objectType << std::endl;

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    loaded = true;

    return true;
}

void Level::SetDestroyBrick(int x, int y)
{
    DESTROYING temp;

    temp.m_tic_tac.restart();
    temp.D_X = x;
    temp.D_Y = y;

    temp.des.setTexture(txt_destroy);
    temp.des.scale(1.0/16*tileWidth,1.0/16*tileHeight);
    temp.Pos_X = m_layers[y][x].getPosition().x;
    temp.Pos_Y = m_layers[y][x].getPosition().y;
    temp.des.setPosition(temp.Pos_X, temp.Pos_Y);
    temp.des.setTextureRect(sf::IntRect(temp.start_rect*temp.des.getLocalBounds().width,0,16,16));

    m_destroying.push_back(temp);
}


void Level::SetDrawingBounds(sf::Rect<float> bounds)
{
    drawingBounds = bounds;

    //Adjust the rect so that tiles are drawn just off screen, so you don't see them disappearing.
    drawingBounds.top -= tileHeight;
    drawingBounds.left -= tileWidth;
    drawingBounds.width += tileWidth;
    drawingBounds.height += tileHeight;
}

void Level::Draw(sf::RenderWindow& window)
{
    for (int t=0; t<m_destroying.size(); t++)
    {
        if (m_destroying[t].m_tic_tac.getElapsedTime().asMilliseconds() >= 150 && m_destroying[t].start_rect < 9)
        {
            m_destroying[t].m_tic_tac.restart();
            m_destroying[t].start_rect ++;
            m_destroying[t].des.setTextureRect(sf::IntRect(m_destroying[t].start_rect*m_destroying[t].des.getLocalBounds().width,0,16,16));
            m_layers[m_destroying[t].D_Y][m_destroying[t].D_X] = m_destroying[t].des;
        }
        else
        if (m_destroying[t].start_rect >= 9)
        {
            m_layers[m_destroying[t].D_Y][m_destroying[t].D_X] = NULL_SPRITE;
            m_data[m_destroying[t].D_Y][m_destroying[t].D_X] = "";
            m_layers[m_destroying[t].D_Y][m_destroying[t].D_X].setPosition(m_destroying[t].Pos_X, m_destroying[t].Pos_Y);
        }
    }
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            window.draw(m_layers[i][j]);

}

void Level::SetScale(float numX, float numY)
{
    if (loaded)
    {
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                m_layers[i][j].scale(numX, numY);
                size_t plX, plY;
                plX = m_layers[i][j].getPosition().x;
                plY = m_layers[i][j].getPosition().y;
                m_layers[i][j].setPosition(plX * numX, plY * numY);

                plX = m_layers[i][j].getPosition().x;
                plY = m_layers[i][j].getPosition().y;

            }
        }
        tileWidth = tileWidth * numX;
        tileHeight = tileHeight * numY;
    }
}




















std::string Level::GetTile(size_t x, size_t y)
{
	return m_data[y][x];
}

size_t Level::GetWidth() const
{
	return width;
}

size_t Level::GetHeight() const
{
	return height;
}

size_t Level::GetTileWidth() const
{
    return tileWidth;
}

size_t Level::GetTileHeight() const
{
    return tileHeight;
}
