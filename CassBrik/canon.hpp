#pragma once

#include "gameObject.hpp"

class Canon : public GameObject
{
public:
	Canon() : GameObject(320.f, 480.f, 60, 120, "image/canon.png") { shape->setOrigin(10, 40); sprite->setOrigin(225/2, 225); };
	bool update(sf::Time deltaTime, sf::RenderWindow* window) override;

private:
	float initAngle = 0;

};