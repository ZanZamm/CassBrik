#include <math.h>
#include <SFML/Graphics.hpp>

class Math
{
public:
	sf::Vector2f createVect(float x, float y);
	float getVectorLenth(sf::Vector2f vector);
	sf::Vector2f nomreVector(sf::Vector2f vector);
	float getAngleFromTwoVector(sf::Vector2f vectorOne, sf::Vector2f vectorTwo);

};

sf::Vector2f Math::createVect(float x, float y)
{
	sf::Vector2f returnVector;

	returnVector.x = x;
	returnVector.y = y;

	return returnVector;
}

float Math::getVectorLenth(sf::Vector2f vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

sf::Vector2f Math::nomreVector(sf::Vector2f vector)
{
	float norme = getVectorLenth(vector);

	vector.x = vector.x / norme;
	vector.y = vector.y / norme;

	return vector;
}

float Math::getAngleFromTwoVector(sf::Vector2f vectorOne, sf::Vector2f vectorTwo)
{
	float scalarProduct = vectorOne.x * vectorTwo.x + vectorOne.y * vectorTwo.y;
	float normeProduct = getVectorLenth(vectorOne) * getVectorLenth(vectorTwo);

	return scalarProduct / normeProduct;
}
