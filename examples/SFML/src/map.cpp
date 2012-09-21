 #ifndef MAP
#define MAP

#include <vector>
#include <SFML/Graphics.hpp>
#include <tmx/map.hpp>

#include "tileset.cpp"
#include "tile.cpp"

class Map
{
public:
    Map(std::vector<bool> &visible, const tmx::Map& source)
    {
        // Let's build tilesets
        for(auto tileset : source.getTilesets())
            tilesets.push_back(Tileset(tileset));
           
        // The following part assumes we have only one tileset 
        unsigned tilesetwidth = tilesets[0].image.getSize().x / tilesets[0].tilewidth;

        int i = 0;
        for(auto layer : source.getLayers())
        {
            int j = 0;
            layers.push_back(std::vector<Tile>());
            visible.push_back(layer->getVisible());
            for(auto tile : layer->getData())
            {
                // Position of the tile on the tileset
                sf::Vector2i post(((tile.getId() - tilesets[0].firstgid) % tilesetwidth) * tilesets[0].tilewidth,
                                  ((tile.getId()-tilesets[0].firstgid) / tilesetwidth) * tilesets[0].tileheight
                                 );
                // Dimensions of the tile according to the tileset
                sf::Vector2i dim(tilesets[0].tilewidth, tilesets[0].tileheight);
                
                sf::IntRect rec(post, dim);
                
                // Position of the tile on the view
                sf::Vector2f pos((j % source.getWidth()) * tilesets[0].tilewidth, (j / source.getWidth()) * tilesets[0].tileheight);
                
                layers[i].push_back(Tile(tilesets[0].image, rec, pos));
                j++;
            }
            i++;
        }
        
        for(auto objectgroup : source.getObjectgroups())      
        {
            layers.push_back(std::vector<Tile>());
            for(auto object : *objectgroup)
            {
                // Position of the object on the tileset
                sf::Vector2i post(((object.getId() - tilesets[0].firstgid) % tilesetwidth) * tilesets[0].tilewidth,
                                  ((object.getId()-tilesets[0].firstgid) / tilesetwidth) * tilesets[0].tileheight
                                 );
                                 
                // Dimensions of the object according to the tileset                 
                sf::Vector2i dim(tilesets[0].tilewidth, tilesets[0].tileheight);
                
                sf::IntRect rec(post, dim);
                
                // Position of the tile on the view. Do NOT forget the offset due to Tile Map Editor positioning conventions.
                sf::Vector2f pos(object.getX(),object.getY()-tilesets[0].tileheight);
                
                layers[i].push_back(Tile(tilesets[0].image, rec, pos));
            }
        }
    }
    
    void draw(const std::vector<bool> &visible, sf::RenderWindow &rw) const
    {
        int i = 0;
        for(auto layer : layers)
        {
            if(visible[i])
               for(auto tile : layer)
                   tile.draw(rw);
            i++;
        }
    }   
    
    std::vector<std::vector<Tile>> layers;
    std::vector<Tileset> tilesets;
};

#endif
