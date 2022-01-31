/****
 * 
 * Manages textures and sprites 
 * 
 ****/

#pragma once

#include <SFML/Graphics.hpp>
#include <new> //for std::bad_alloc

class TextureManager
{
public:

	TextureManager();
	~TextureManager();

	static sf::Texture* loadTexture(const char* textureSheet);
};

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();

	static sf::Sprite* loadSprite(sf::Texture*);
};