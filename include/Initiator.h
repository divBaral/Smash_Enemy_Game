/****
 * 
 * Initializes the game 
 * Show the welcome screen
 * Welcomes the player
 * 
 ****/

#pragma once 

#include <iostream>

#include <SFML/Graphics.hpp>

class Initiator
{
public:
	Initiator();
	~Initiator();

	void assignScreen(sf::RenderWindow *);
	bool loadBackground(const char *);
	void renderBackground();
	
	void close();

protected:
	sf::Texture *windowTexture = NULL;
	sf::Sprite *background = NULL;
	sf::RenderWindow *m_window = NULL;
};