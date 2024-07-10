#include "ball.hpp"
#include <iostream>

Ball::Ball(sf::RenderWindow* window) : GameObject(320.f, 480.f, 20, "image/ball.png")
{
	sf::Vector2f direction;
	direction.x = sf::Mouse::getPosition(*window).x - shape->getPosition().x;
	direction.y = sf::Mouse::getPosition(*window).y - shape->getPosition().y;
	float norme = getVectorLenth(direction);
	vect.x = direction.x / norme;
	vect.y = direction.y / norme;
	std::cout << vect.x << " / " << vect.y << std::endl;
}

bool Ball::update(sf::Time deltaTime, sf::RenderWindow* window)
{
	//move(deltaTime);
	oSetPosition(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	borderProtection(window);

	return isUnderScreen(window);
}

bool Ball::isUnderScreen(sf::RenderWindow* window)
{
	return getMinMaxY().x > window->getSize().y;
}

void Ball::oSetPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	shape->setPosition(position.x, position.y);

	hitbox->setPosition(position.x, position.y);
}

void Ball::onCollision(GameObject* incomingObject)
{
	bounce(getBounceDirection(incomingObject));
}

void Ball::bounce(sf::Vector2f direction)
{
	std::cout << "X : " << direction.x << std::endl << "Y : " << direction.y << std::endl;

	if (direction.x != 0)
		vect.x = abs(vect.x) * direction.x;
	else if (direction.y != 0)
		vect.y = abs(vect.y) * direction.y;
	return;
}

sf::Vector2f Ball::getBounceDirection(GameObject* incomingObject)
{
	sf::Vector2f returnVect;
	returnVect.x = -1;
	returnVect.y = -1;

	float left = abs(getMinMaxX().y - incomingObject->getMinMaxX().x);
	float right = abs(getMinMaxX().x - incomingObject->getMinMaxX().y);
	float up = abs(getMinMaxY().y - incomingObject->getMinMaxY().x);
	float down = abs(getMinMaxY().x - incomingObject->getMinMaxY().y);
	float xMin = left;
	float yMin = up;

	if (left > right) {
		xMin = right;
		returnVect.x = 1;
	}
	if (up > down) {
		yMin = down;
		returnVect.y = 1;
	}
	if (xMin > yMin) {
		returnVect.x = 0;
	}
	else {
		returnVect.y = 0;
	}

	return returnVect;
}

sf::Vector2f Ball::getWindowBorderBounceDirection(sf::RenderWindow* window)
{
	sf::Vector2f bounceDirection;

	if (getMinMaxX().x < 0)
		bounceDirection.x = 1;

	else if (getMinMaxX().y > window->getSize().x)
		bounceDirection.x = -1;

	if (getMinMaxY().x < 0)
		bounceDirection.y = 1;

	return bounceDirection;
}

// Collides //

bool Ball::isOutScreen(sf::RenderWindow* window)
{
	if (getMinMaxX().x < 0 or getMinMaxX().y > window->getSize().x or getMinMaxY().x < 0)
		return true;

	return false;
}

bool Ball::isColliding(GameObject* incomingObject)
{
	bool collideX = isCollidingOneD(incomingObject->getMinMaxX(), getMinMaxX());

	bool collideY = isCollidingOneD(incomingObject->getMinMaxY(), getMinMaxY());

	if (!collideX or !collideY)
		return false;

	sf::Vector2f minmaxX = incomingObject->getMinMaxX();
	sf::Vector2f minmaxY = incomingObject->getMinMaxY();

	collideX = isCollidingOnePos(shape->getPosition().x, minmaxX);

	collideY = isCollidingOnePos(shape->getPosition().y, minmaxY);

	if (collideX and collideY)
		return true;

	sf::Vector2f dist;

	dist.x = abs(incomingObject->shape->getPosition().x - shape->getPosition().x);
	dist.y = abs(incomingObject->shape->getPosition().y -shape->getPosition().y);

	sf::Vector2f objectSize;

	objectSize.x = incomingObject->size.x / 2;
	objectSize.y = incomingObject->size.y / 2;

	if (getVectorLenth(dist) <= size.x / 2 + getVectorLenth(objectSize))
		return true;

	return false;
}

bool Ball::isCollidingOneD(sf::Vector2f objectOne, sf::Vector2f objectTwo)
{
	if (objectOne.y - objectOne.x > objectTwo.y - objectTwo.x)
		return isCollidingOneD(objectTwo, objectOne);



	return ((objectOne.x >= objectTwo.x and objectOne.x <= objectTwo.y) or (objectOne.y >= objectTwo.x and objectOne.y <= objectTwo.y));
}

bool Ball::isCollidingOnePos(float objectOne, sf::Vector2f objectTwo)
{
	return (objectOne >= objectTwo.x and objectOne <= objectTwo.y);
}


// Bounce //

void Ball::checkBounce(GameObject* incomingObject)
{
	if (isColliding(incomingObject))
	{
		std::cout << "maitre du monde" << std::endl;
		if (!(std::find(colliding.begin(), colliding.end(), incomingObject) != colliding.end()))
		{
			onCollision(incomingObject);
			incomingObject->onCollision(this);
			colliding.push_back(incomingObject);
		}
	}
	else
	{
		for (auto it = colliding.begin(); it != colliding.end();)
		{
			if (*it == incomingObject)
			{
				it = colliding.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void Ball::borderProtection(sf::RenderWindow* window)
{
	if (isOutScreen(window))
		bounce(getWindowBorderBounceDirection(window));
}
