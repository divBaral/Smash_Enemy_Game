/****
 * 
 * Prompts the player with exit options
 * 
 ****/
#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Button.h"

class Exit
{
public:
	Exit();
	~Exit();

	void createExitWindow(sf::RenderWindow *);
	void runExitWindow(bool);
	void runExit();
	void exitMessage(std::string);

	void resumeButton( sf::Vector2f );
	void restartButton( sf::Vector2f );
	void quitButton( sf::Vector2f );
	void Buttons();
	void renderButtons(sf::Vector2f, sf::Vector2f, sf::Vector2f);

	bool getEXIT_FLAG(){ return EXIT; }
	bool isPaused(){ return PAUSED; }
	bool restart(){ return RESTART; }

	void started()
	{
		RESTART = false;
	}
	void setPAUSE_VALUE()
	{
		PAUSED = true;
	}
	void resetPAUSE_VALUE()
	{
		PAUSED = false;
	}

private:
	bool EXIT;
	bool PAUSED;
	bool RESTART;

	std::vector<button *> buttons;
	sf::Font font;
	sf::RenderWindow *exitWindow = NULL;
};

