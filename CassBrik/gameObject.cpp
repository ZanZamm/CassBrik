#include "gameObject.hpp"
#include <iostream>

GameObject::GameObject(float pPos1, float pPos2, int pSize1, int pSize2, const char* path)
{
	position.x = pPos1;
	position.y = pPos2;
	size.x = pSize1;
	size.y = pSize2;

	shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	shape->setOrigin(pSize1/2, pSize2/2);
	shape->setPosition(position.x, position.y);
	shape->setFillColor(sf::Color::White);

	sf::Vector2f sizeSprite;
	sprite = new sf::Sprite(*TextureManager::getTexture(path));
	sizeSprite.x = (size.x / 356);
	sizeSprite.y = (size.y / 529);
	sprite->setScale(sizeSprite);
	sprite->setOrigin(pSize1 / 2, pSize2 / 2);
	sprite->setPosition(position.x, position.y);
}

GameObject::GameObject(float pPos1, float pPos2, int pSize1, int pSize2)
{
	position.x = pPos1;
	position.y = pPos2;
	size.x = pSize1;
	size.y = pSize2;

	shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	shape->setOrigin(pSize1/2, pSize2/2);
	shape->setPosition(position.x, position.y);
	shape->setFillColor(sf::Color::White);
}

GameObject::GameObject(float pPos1, float pPos2, int pSize1, const char* path)
{
	position.x = pPos1;
	position.y = pPos2;
	size.x = pSize1;
	size.y = pSize1;

	velocity = 500;

	shape = new sf::CircleShape(size.x / 2);
	shape->setOrigin(pSize1 / 2, pSize1 / 2);
	shape->setPosition(position.x, position.y);
	shape->setFillColor(sf::Color::Cyan);

	hitbox = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	hitbox->setOrigin(pSize1 / 2, pSize1 / 2);
	hitbox->setPosition(position.x, position.y);
	hitbox->setFillColor(sf::Color::Green);

	sf::Vector2f sizeSprite;
	sprite = new sf::Sprite(*TextureManager::getTexture(path));
	sizeSprite.x = 2 * (size.x / 612);
	sizeSprite.y = 2 * (size.y / 612);
	sprite->setScale(sizeSprite);
	sprite->setPosition(position.x, position.y);
}


// Position //

void GameObject::move(sf::Time deltaTime)
{
	float fDt = deltaTime.asSeconds();

	position.x += vect.x * velocity * fDt;
	position.y += vect.y * velocity * fDt;

	shape->setPosition(position.x, position.y);
	hitbox->setPosition(position.x, position.y);
	sprite->setPosition(position.x - size.x, position.y - size.y);
}

sf::Vector2f GameObject::getMinMaxX() {
	sf::Vector2f returnVect;
	returnVect.x = position.x - size.x / 2;
	returnVect.y = position.x + size.x / 2;
	return returnVect;
}

sf::Vector2f GameObject::getMinMaxY() {
	sf::Vector2f returnVect;
	returnVect.x = position.y - size.y / 2;
	returnVect.y = position.y + size.y / 2;
	return returnVect;
}


// Vector //

float GameObject::getVectorLenth(sf::Vector2f vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}