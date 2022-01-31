/****
 * 
 * manages all the tasks related to welcome screen 
 * 
 ****/
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Initiator.h"
#include "Button.h"
#include "ExitManager.h"
#include "TextureManager.h"

extern std::string player_name;

class Welcomer: public Initiator
{
public:
	Welcomer( sf::RenderWindow* );
	~Welcomer();

	void welcome();
	void showCursor();
	void promptBox();
	void playButton();
	//handles instruction button
	void InsButton(Exit *);
	void Instructions();
	bool exitIns();
	void renderAliens();//for decoration purpose only

	void drawText();
	void handleInput(sf::Event&);
	bool Greeted(){ return hasGreeted;}
	void greetPlayer(Exit*);

	std::string playerInput;

private:
	bool hasGreeted;
	sf::Font font;
	sf::Text* playerName = NULL;
	sf::Clock clock;

	//welcomer board texture and sprite
	sf::Texture bTexture;
	sf::Sprite bSprite;

	//decorative aliens
	std::vector<sf::Texture *> aTextures;
	sf::Sprite aSprite;

	//play button
	button *pButton = NULL;
	//instruction button
	button *iButton = NULL;
};