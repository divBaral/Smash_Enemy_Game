/****
 * 
 * contains the information about the aliens/enemies of the game
 * 
 ****/
#pragma once
#include "Entity.h"

static char Alienname[] = "Alien";

class Alien : public Entity
{
public:
	Alien(Vector2d position, float radius, b2World* world);


	void load(const char* path);
	void render( sf::RenderWindow* window);
	
	char* getInfo() { return Alienname;}

	~Alien();

protected:
	bool atRest;
	b2CircleShape m_Shape;
	float m_radius;
};
