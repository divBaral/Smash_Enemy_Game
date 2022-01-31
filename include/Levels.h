/****
 * 
 * Contains all the necessary information for setting up different levels
 * 
 ****/

#pragma once 

#include "wMap.h"

extern std::string player_name;

namespace levelZone
{

	class level1: public wMap
	{
	public:
		level1(  sf::RenderWindow* );
		~level1();
		 void loadTiles();
		 void loadElements();
		 void loadAliens();

	};


	class level2: public wMap
	{
	public:
		level2(  sf::RenderWindow* );
		~level2();
		 void loadTiles();
		 void loadElements();
		 void loadAliens();

	};

	class level3: public wMap
	{
	public:
		level3(  sf::RenderWindow* );
		~level3();
		 void loadTiles();
		 void loadElements();
		 void loadAliens();
	};

	class level4: public wMap
	{
	public:
		level4(  sf::RenderWindow* );
		~level4();
		 void loadTiles();
		 void loadElements();
		 void loadAliens();

	};

	class level5: public wMap
	{
	public:
		level5(  sf::RenderWindow* );
		~level5();
		 void loadTiles();
		 void loadElements();
		 void loadAliens();

	};

	class level6: public wMap
	{
	public:
		level6(  sf::RenderWindow* );
		~level6();
		 void loadTiles();
		 void loadElements();
		 void loadAliens();

	};

}



