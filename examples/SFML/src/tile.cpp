#ifndef TILE
#define TILE

#include <SFML/Graphics.hpp>

class Tile : public sf::Sprite
{
public:
    Tile(sf::Texture &tex, sf::IntRect rec, sf::Vector2f pos) :
        sf::Sprite(tex)
    {
        setTextureRect(rec);
        setPosition(pos.x, pos.y);
    }
    
    void draw(sf::RenderWindow &rw) const
    {
        rw.draw(*this);
    }
};

#endif
