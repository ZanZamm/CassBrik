#include "TextureManager.hpp"


std::map<std::string, sf::Texture*> TextureManager::textures;

sf::Texture* TextureManager::getTexture(std::string path)
{
    if (!checkTexture(path))
        loadNewTexture(path);

    return findTexture(path);
}

bool TextureManager::checkTexture(std::string path)
{
    return TextureManager::textures[path];
}

int TextureManager::loadNewTexture(std::string path)
{
    sf::Texture* texture = new sf::Texture;
    if (!texture->loadFromFile(path))
    {
        return 1;
    }

    TextureManager::textures[path] = texture;

    return 0;
}

sf::Texture* TextureManager::findTexture(std::string path)
{
    if (TextureManager::textures[path] != nullptr)
        return TextureManager::textures[path];

    return nullptr;
}