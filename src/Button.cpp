#include "Button.h"

button::button(){}
button::~button(){}

void button::createButton(sf::Vector2f size, sf::Vector2f pos)
{
	/*setting coordinates for generating button area*/
	buttonArea.width = size.x;
	buttonArea.height = size.y;
	//top left corner coordinates of rectangular button
	buttonArea.left = pos.x;
	buttonArea.top = pos.y;

	shape.setSize(size);
	shape.setPosition(pos);
}

void button::drawButton(sf::RenderWindow* window)
{
	buttonInteract(window);
	window->draw(shape);
}

void button::buttonInteract(sf::RenderWindow* window)
{
        int MouseX = sf::Mouse::getPosition(*window).x;
        int MouseY = sf::Mouse::getPosition(*window).y;

        if(buttonArea.contains(MouseX, MouseY))
        {
        	shape.setFillColor(sf::Color(217, 106, 149));
        }
        else
        {
        	shape.setFillColor(sf::Color(209, 188, 186));
        }
}
