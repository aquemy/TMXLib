#include <SFML/Graphics.hpp>
#include <tmx/map.hpp>
#include "src/map.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    (void) argc;

    // Create the Window and the View
    sf::RenderWindow window(sf::VideoMode(800,600), "TMXExample");
    sf::View mapView(sf::FloatRect(0, 0, 800, 600));

    try
    {
        // Load the map
        tmx::Map map(argv[1]);
        
        // Define visibility vector and create the map
        std::vector<bool> visible;
        Map myMap(visible, map);
        
        // Local variables for time and events detection
        sf::Clock clock;
        sf::Event event;

        while (window.isOpen())
        {
            sf::Time elapsed = clock.restart();
            
            // To close the application
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            
            // Deplacement part        
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                mapView.move(0,200*elapsed.asSeconds());
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                mapView.move(200*elapsed.asSeconds(),0);
                
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                mapView.move(-200*elapsed.asSeconds(),0);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                mapView.move(0,-200*elapsed.asSeconds());    
            
            // Rotation part
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                mapView.rotate(10*elapsed.asSeconds());
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                mapView.rotate(-10*elapsed.asSeconds());
            
            // Zoom part    
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                mapView.zoom(1+elapsed.asSeconds());
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                mapView.zoom(1-elapsed.asSeconds());
            
            // Visbility part
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed 
                    && event.key.code  >= sf::Keyboard::Num0
                    && event.key.code <= sf::Keyboard::Num9)
                {
                        if(myMap.layers.size() > (unsigned)event.key.code - sf::Keyboard::Num0)
                            visible[event.key.code - sf::Keyboard::Num0] = !visible[event.key.code - sf::Keyboard::Num0];
                }
            }
                
            // Drawing part
            window.clear();
            window.setView(mapView);
            myMap.draw(visible, window);
            window.setView(window.getDefaultView());
            window.display();
        }
    
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

