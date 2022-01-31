/****
 * 
 * contains the blueprint of the entities of the game
 * 
 ****/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstring>

#include "TextureManager.h"

const float mPPM = 32.f; // Pixel to Meter ratio
static char name[] = "Entity";

class Vector2d {
public:
	Vector2d( float p_x=0.f,  float p_y=0.f):
	x(p_x),
	y(p_y)
	{}

	void set(float p_x, float p_y )
	{
		x = p_x;
		y = p_y;
	}
	Vector2d get()
	{
		return *this;
	}

	float x;
	float y;
	
};

inline float toBoxCoord( const float x)
{
	return x/mPPM;
}

inline float toPixelCoord( const float x )
{
	return x*mPPM;
}

class Entity 
{
public:
	Entity( Vector2d position );
	
	virtual void load(const char *path);
	virtual void render( sf::RenderWindow* window );

	b2Body* getBody() { return m_Body;}
	sf::Sprite* getSprite() { return m_Sprite;}

	virtual ~Entity();

	virtual char* getInfo() { return name;}

protected:
	b2BodyDef m_BodyDef;
	b2Body* m_Body = NULL;
	b2FixtureDef m_FixtureDef;
	sf::Texture* m_Texture = NULL; 
	sf::Sprite* m_Sprite = NULL;
	Vector2d m_Position;

};
