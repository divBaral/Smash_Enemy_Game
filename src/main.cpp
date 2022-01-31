#include <iostream>
#include <string>
#include <new>

//SFML specific headers
#include <SFML/Graphics.hpp>
//Box2D specific headers
#include <Box2D/Box2D.h>

//local header files
#include "Welcomer.h"
#include "TextureManager.h"
#include "ExitManager.h"
#include "Levels.h"
#include "LevelsMap.h"
#include "RecordManager.h"

//global constants 
const float PPM = 32.f; //pixel per meter ratio

//screen dimensions
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 576;


int main()
{
	//Box2D world setup
    b2World* myWorld = NULL;

    //music setup
    sf::Music music;
	if (!music.openFromFile("assets/sound/game_music.wav") ) {
    	std::cerr << "Music can't be loaded\n"; 
	}

	std::string backgroundImg = "assets/backgrounds/welcomeScreen.jpg"; //for welcome screen
	std::string backgroundImglevel = "assets/backgrounds/background1.jpg"; //for level zero screen

	sf::RenderWindow* window;
	try
	{
		window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Smash Enemy"); 
	}
	catch(std::bad_alloc& ba)
	{
		window = NULL;
	}
	if(!window)
	{
		std::cerr << "Window not created\n";
	}
	else
	{	

		//decides if the level is initialized
		//initialization of level means rendering background, loading entities & world creation
		bool isLevelInit = false;

		//after welcomer player goes to levels' map
		bool atLevelsMap = true;

		//decides if level should be changed 
		bool levelTransition = false;

		int levelCount = 0;
		int levelTracker = 1;


		//sets frame rate of the window equal to the refresh rate of screen
        window->setFramerateLimit(60);	

        //welcomes the player
        Welcomer* gameInit = new Welcomer( window );
		//rendering backgroundImg for welcome screen
    	if( gameInit->loadBackground(backgroundImg.c_str()) == false )
    	{
    		std::cerr << "Unable to load background.\n";
    		delete gameInit;
    		gameInit = NULL;

    		delete window;
    		window = NULL;

    		exit(-1);
    	}


    	//exit manager
		Exit *exitMenu = new Exit();

		//creating levels 
		//wMap means world map
		wMap* level;
		//lMap means level map which is a gateway for levels and the player
		level = new lMap( window );

		User playerData;//contains player's progress
		bool retrievedUserData = false;


        sf::Event event;
    	//game loop
     	while(window->isOpen())
    	{

    		if(!(gameInit->Greeted()))
    		{
    			//renders welcome sprites and marks the beginning of the game
    			gameInit->renderBackground();
    			gameInit->welcome();
			}



			if( gameInit->Greeted() && !retrievedUserData )
			{
				//retrieve the saved progress of the user( if exists )
				levelTracker = playerData.savedLevels( player_name ); //player_name is declared in Welcomer.h file

				retrievedUserData = true;
			}



    		if( gameInit->Greeted() )
    		{	

    			if( !isLevelInit )
    			{	
    				//rendering backgroundImg for level screen
    				if(level->loadBackground(backgroundImglevel.c_str()) == false)
    				{
    					std::cerr << "Unable to load background.\n";
    				}

   					music.play();
   					music.setLoop(true);

   					if( !atLevelsMap )
   					{
	    			    b2Vec2 gravity(0.f, 9.8f);
	   					myWorld = new b2World(gravity);
	   					level->assignWorld( myWorld );

	    				level->loadEntities();
	    				
	    				//starts listening collisions
	    				level->listenCollision();
    				}

    				isLevelInit = true;
    			}


    			//simulate world
    			if( myWorld )
    				myWorld->Step(1/60.f, 8, 3);

    			level->renderBackground();
    			bool levelQuit = false;//is used to decide whether to design pause button or quit button

    			if( atLevelsMap )
    			{


    				levelQuit = true;
    				level->chooseLevels( levelCount, levelTracker );
    				//make quit button
    				level->makeButton( exitMenu, levelQuit );


    			}
    			else
    			{

    				//render all entities except bullets aka weapons
    				level->renderEntities();
    				//make pause button
	    			level->makeButton( exitMenu, levelQuit );
	    			level->handleMouseButtonPressed();
	    			level->renderBullets();



	    			if( level->Ended() )
	    			{
	    				levelTransition = true;
	    			}


    			}

    			if( levelTransition )
    			{
	    			//passing levelCount by reference
	    			level->transitionTexture( levelCount, levelTracker );
    			}
    		}


    		//create levels
    		if ( (gameInit->Greeted() && (levelCount != level->getLevelCount())) || exitMenu->restart() ) 
    		{

    			if( level )
    			{
    				delete level;
    				level = NULL;
    			}

    			if(exitMenu->restart())
    			{
    				exitMenu->started();
    			}

    			if( myWorld )
    			{
	    			delete myWorld;
	    			myWorld = NULL;
    			}

    			isLevelInit = false;
    			levelTransition = false;

    			switch( levelCount )
    			{
    				case 0:
    				level = new lMap( window );
    				atLevelsMap = true;
    				break;
    				case 1:
    				level = new levelZone::level1( window);
    				atLevelsMap = false;
    				break;
    				case 2:
    				level = new levelZone::level2( window );
    				atLevelsMap = false;
    				break;
    				case 3:
    				level = new levelZone::level3( window );
    				atLevelsMap = false;
    				break;
    				case 4:
    				level = new levelZone::level4( window );
    				atLevelsMap = false;
    				break;
    				case 5:
    				level = new levelZone::level5( window );
    				atLevelsMap = false;
    				break;
    				case 6:
    				level = new levelZone::level6( window );
    				atLevelsMap = false;
    				break;
    				default:
    				level = new levelZone::level6( window );
    				atLevelsMap = false;
    				break;
    			}
    		}

    		//event loop
    		while (window->pollEvent(event))
    		{

    			//player can quit the game only when he/she is in levels' map
    			if( event.type == sf::Event::Closed || exitMenu->isPaused() )
   				{
   					if( !atLevelsMap )
   					{
	   					exitMenu->createExitWindow( window );
	   					exitMenu->runExitWindow( gameInit->Greeted() );

	    				if( exitMenu->getEXIT_FLAG() )
	    				{	
	    					levelCount = 0;
	    				}

	    				//if the player chooses to resume the game
	    				exitMenu->resetPAUSE_VALUE();
    				}
    				else
    				{
    					Exit exit;
    					exit.createExitWindow( window );
    					exit.runExit();
    					if( exit.getEXIT_FLAG() )
    					{

	    					music.setLoop(false);
	    					music.stop();
	    					window->close();

    					}

    					//if the player chooses to resume the game
    					exitMenu->resetPAUSE_VALUE();
    				}
    			}
    			else if( gameInit->Greeted() && !atLevelsMap && event.type == sf::Event::MouseButtonReleased )
   				{	
   					if(!(level->Ended()))
   					{
   						//release the weapon 
   						level->handleMouseButtonReleased( event );
   					}
            	}
            	//handling username of the player
            	if( !(gameInit->Greeted()) )//control condition to let it happen only once
            	{
            		gameInit->handleInput( event );
    			}

    		}

    		
    		if(!(gameInit->Greeted()))//control codition to let it happen only once
    		{	
    			//rendering the cursor and text entered by the player
    			gameInit->greetPlayer( exitMenu );	
    		}
    		
    		window->display();

    	}

    	//perform cleanup

    	if( gameInit )
    	{
			delete gameInit;
	    	gameInit = NULL;
    	}

    	if( exitMenu )
    	{
    		delete exitMenu;
    		exitMenu = NULL;
    	}

    	if( level )
    	{
	    	delete level;
	    	level = NULL;
    	}

    	if( myWorld )
    	{
	    	delete myWorld;
	    	myWorld = NULL;
    	}

    	if( window )
    	{
	    	delete window;
	    	window = NULL;
   		}
	}

    std::cout << "Game Closed Successfully. \n";
	return 0;
}