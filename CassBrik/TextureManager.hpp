#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager
{
public:
	static sf::Texture* getTexture(std::string path);
	static std::map<std::string, sf::Texture*> textures;

private:

	TextureManager();

	static bool checkTexture(std::string path);
	static int loadNewTexture(std::string path);
	static sf::Texture* findTexture(std::string path);

};