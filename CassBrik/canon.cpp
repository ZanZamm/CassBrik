#include "canon.hpp"
#include <iostream>

bool Canon::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f baseCanon = shape->getPosition();

	if (window->getSize().x < mouse.x or mouse.x < 0 or 0 > mouse.y or mouse.y > window->getSize().y)
		return false;

	float opp = mouse.x - baseCanon.x;
	float adj = mouse.y - baseCanon.y;

	float angle = -atan(opp / adj) * 180 / 3.14;

	shape->setRotation(angle);
	sprite->setRotation(angle);

	return false;
}
