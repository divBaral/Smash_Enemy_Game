#include "TextureManager.h"

TextureManager::TextureManager(){}
TextureManager::~TextureManager(){}

sf::Texture* TextureManager::loadTexture(const char* textureSheet)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(textureSheet);

	return texture;
}

SpriteManager::SpriteManager(){}
SpriteManager::~SpriteManager(){}

sf::Sprite* SpriteManager::loadSprite(sf::Texture* texture)
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*texture);

	return sprite;
}