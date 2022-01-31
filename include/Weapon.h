/****
 * 
 * contains information about weapons
 * 
 ****/

#pragma once

#include <cstdlib>//for abs function
#include "Entity.h"

static char Weaponname[] = "Weapon";

class Weapon : public Entity
{
public:
	Weapon(Vector2d position, b2World* world);


	void load(const char* path);
	void render( sf::RenderWindow* window );
	bool isAtRest();
	char* getInfo() { return Weaponname;}
	
	~Weapon();

protected:
	bool atRest;
	b2CircleShape m_Shape;
	float m_radius;
};
