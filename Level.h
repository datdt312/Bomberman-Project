#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>
#include <deque>
#include <map>

const float S_SIZE = 2.5;

struct Layer
{
    int opacity;
    std::vector <sf::Sprite> tiles;
};

struct DESTROYING
{
    sf::Clock m_tic_tac;
    sf::Sprite des;

    int D_X;
    int D_Y;
    float Pos_X;
    float Pos_Y;

    int start_rect = 2;
};

struct DataEnemy
{
    int de_x;
    int de_y;
};

class Level
{
    public:

        size_t numScale;
        bool loaded = false;
        Level();
        virtual ~Level();

        // Init map  [ m_data ]
        void Initialize(size_t width, size_t height);

        //Loads the map. Returns false if it fails.
        bool LoadFromFile(const std::string& filename);

        void UpdateLevel(float deltaTime);

        /// Get Tile Type at index (x,y)
        /// <param="x">x'th index</param>
        /// <param="y">y'th index</param>
        /// <returns>TileType object</returns>
        std::string GetTile(size_t x, size_t y);

        /// Get level width in tiles
        /// <returns>Width</returns>
        size_t GetWidth() const;
        size_t GetTileWidth() const;

        /// Get level height in tiles
        /// <returns>Height</returns>
        size_t GetHeight() const;
        size_t GetTileHeight() const;

        void SetDrawingBounds(sf::Rect<float> bounds);

        void Draw(sf::RenderWindow& window);

        void SetScale(float numX, float numY);
        void UpdateAfterScale_Level();

        void SetDestroyBrick(int x, int y);


    public:

        std::vector< std::vector< std::string > > m_data;

        std::vector< DataEnemy > enemy_data;

        std::vector< std::vector< sf::Sprite > > m_layers;

        sf::Texture txt_destroy;
        sf::Sprite NULL_SPRITE;
        std::deque< DESTROYING > m_destroying;



    private:

        /// Another
        //Width(tiles), height(tiles), tile width(pixels), tile height(pixels) of the map.
        size_t width, height, tileWidth, tileHeight, spacing, margin;

        //Used to offset the tile number.
        int firstTileID;

        //Used to clip anything off screen.
        sf::Rect <float> drawingBounds;

        //The tileset image.
        sf::Image tilesetImage;

        //The tileset texture.
        sf::Texture tilesetTexture;



};

#endif // LEVEL_H
