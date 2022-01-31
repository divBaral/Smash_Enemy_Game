/****
 * 
 * base class for construction of levels objects in the game 
 * Loads and deletes box2d world bodies
 * 
 ****/

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Initiator.h"
#include "Weapon.h"
#include "Tiles.h"
#include "Alien.h"
#include "myListener.h"
#include "Element.h"
#include "MouseHandler.h"
#include "ExitManager.h"
#include "RecordManager.h"



enum { BOTTOM, LEFT, RIGHT, UPPER};
enum { FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH};



//world map
class wMap : public MouseHandler, public Initiator
{
public:
	wMap();
	virtual ~wMap();

	void assignWorld(b2World* world)
	{
		m_world = world;
	}

	void loadBorders();
	void loadBullets();
	void loadCatapult();

	//dynamics for levels
	virtual void loadTiles(){}
	virtual void loadElements(){}
	virtual void loadAliens(){}
	bool Ended()
	{	
		if( weaponBody && weaponBody->isAtRest() && hasEnded )
	    {
	    	return true;
	    }
	    return false;
	}
	//load all the entities of level zero
	void loadEntities();

	
	void renderTiles();
	void renderCatapult();
	void renderBullets();
	void renderElements();
	void renderAliens();
	void renderScore();
	//render all the entities of level zero
	void renderEntities();
	
	int getLevelCount() { return levelcount;}

	void listenCollision();
	void transitionTexture( int&, int& );
	void handleMouseButtonPressed();
	void handleMouseButtonReleased( sf::Event& );
	void makeButton(Exit *, bool);

	b2Vec2 getTrajectoryPoint( b2World*, b2Vec2&, b2Vec2& , float);
	Weapon* getWeapon()
	{ 
		if( weaponBody ) return weaponBody;
		else return NULL;
	}
	//deletes all the vectors(data members)
	void cleanVectorElements();

	//for levels' map
	virtual void chooseLevels( int&, int ){}

	float winX;
	float winY;

protected:
	button *pButton = NULL;
	bool pButtonMade;
	bool nextButtonMade;

	sf::Font font;
	sf::Text scoreText;
	sf::Text levelText;
	int score;

	//Transition texture and sprite
	sf::Texture tTexture;
	sf::Sprite tSprite;
	//Next button
	button *next = NULL;

	//Texture and sprite for levelText and scoreText
    sf::Texture levelTexture;
    sf::Sprite Sprite1;
    sf::Sprite Sprite2;

	b2World *m_world = NULL;
	Weapon *weaponBody = NULL;

	//Borders
	StaticBox* Borders[4];
	//weapons
	Weapon* Bullets[4];
	int Bulletcount;
	int totalBullets;
	bool hasEnded;
	int levelcount;
	unsigned aliencount; 

	//catapult
	sf::Texture* catapultText = NULL;
	sf::Sprite* catapult = NULL;

	//listener for collision
	Listener m_gameCollisionListener;

	std::vector<StaticBox*> tiles;

	//elements
	std::vector<Element*> woodElements;
	std::vector<Alien*> aliens;

	//player's progress report
	User playerData;
};