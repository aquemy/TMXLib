#ifndef TILESET
#define TILESET

#include <SFML/Graphics.hpp>
#include <tmx/tileset.hpp>
#include <tmx/image.hpp>

class Tileset
{
public:
    Tileset(tmx::Tileset& source) :
        firstgid(source.getFirstGid()),
        tilewidth(source.getTilewidth()),
        tileheight(source.getTileheight())
    {
        image.loadFromFile(source.getImage().getSource());
    }
    
    void draw(sf::RenderWindow& rw) const
    {
        sf::Sprite sprite(image);
        rw.draw(sprite);
    }

    int firstgid = 0;      ///< ID for the first tile of the tileset
    int tilewidth = 0;     ///< Width of a tile
    int tileheight = 0;    ///< Height of a tile
    sf::Texture image;     ///< Image of the tileset
};

#endif
