/****
 * 
 * handles the mouse input related events 
 * 
 ****/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

const int SCALE = mPPM;

class MouseHandler 
{
public:
	MouseHandler(){}
	virtual ~MouseHandler(){}
	
	virtual void handleMouseButtonPressed() = 0;
	virtual void handleMouseButtonReleased( sf::Event& ) = 0;
protected:
	bool readyToLaunch ; 
};