/****
 * 
 * contains information about the tiles used in the games
 * 
 ****/

#pragma once
#include "Entity.h"


class StaticBox : public Entity

{
public:
	StaticBox(Vector2d position, Vector2d size, b2World* world);
	~StaticBox();

private:
	b2PolygonShape m_shape;
};