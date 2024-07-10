#include "tiles.hpp"
#include <iostream>

Tiles::Tiles(float posX, float posY, int pLife) : GameObject(64*posX + 32, 25*posY + 12, 60, 20)
{
	life = pLife;
    sf::Time deltaTime;
    update(deltaTime, nullptr);
}

bool Tiles::update(sf::Time deltaTime, sf::RenderWindow* window)
{
    switch (life)
    {
    case 6:
        shape->setFillColor(sf::Color::Blue);
        break;
        
    case 5:
        shape->setFillColor(sf::Color::Cyan);
        break;
        
    case 4:
        shape->setFillColor(sf::Color::Green);
        break;
        
    case 3:
        shape->setFillColor(sf::Color::Green);
        break;
        
    case 2:
        shape->setFillColor(sf::Color(255, 127, 0, 255));
        break;
        
    case 1:
        shape->setFillColor(sf::Color::Red);
        break;
        
    case 0:
        return true;

    default:
        break;
    }

	return false;
}
