/****
 * 
 * This headerfile contains code for designing buttons, only rectangular buttons
 * 
 ****/
#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class button
{
public:
	button();
	~button();

	void createButton(sf::Vector2f, sf::Vector2f); //(size, position)
	void drawButton(sf::RenderWindow*);
	void buttonInteract(sf::RenderWindow*);
	sf::Rect<float> getRect(){return buttonArea;}

	std::string name;
protected:
	sf::Rect<float> buttonArea;
	sf::RectangleShape shape;
	
};