/****
 * 
 * contains information about the boxes/elements protecting (sometimes may destroy) aliens
 * 
 ****/
#pragma once 
#include "Entity.h"

class Element : public Entity
{
public:
	Element( Vector2d position, Vector2d size, b2World* world );

	void load(const char * path, const Vector2d& size);
	void render( sf::RenderWindow* window );
	
	~Element();

private:
	b2PolygonShape m_shape;

};