/****
 * 
 * Gateway between the user and game levels
 * 
 ****/

#pragma once 
#include <string>
#include <sstream>

#include "wMap.h"
#include "TextureManager.h"

class lMap: public wMap
{
public:
	lMap(  sf::RenderWindow* );
	~lMap();

	void chooseLevels( int&, int);
	void loadTextures();
	int select();
	void renderlTags();

private:
	//areas of sprites of level tags/buttons
	bool areaPushed;

	//textures of level tags/buttons
	bool texturesPushed;

	sf::Texture tSelectLevel;
	sf::Sprite selectLevelSprite;

	std::vector<sf::Texture *> lTextures;
	std::vector<sf::IntRect> lAreas;
	sf::Sprite lSprite;

	int m_levelTracker;
};