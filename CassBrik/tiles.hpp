#pragma once

#include "gameObject.hpp"

class Tiles : public GameObject
{
public:
	Tiles(float posX, float posY, int pLife);
	bool update(sf::Time deltaTime, sf::RenderWindow* window) override;
	inline void onCollision(GameObject* incomingObject) override { life -= incomingObject->getDamage(); }

private:
	int maxLife;
	int life;

};