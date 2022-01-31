#include "ExitManager.h"

const float EXIT_WINDOW_HEIGHT = 100;
const float EXIT_WINDOW_WIDTH = 300;

Exit::Exit()
{
	EXIT = false;
	PAUSED = false;
	RESTART = false;
}

Exit::~Exit()
{

	for(unsigned i = 0; i < buttons.size(); i++)
	{
		if( buttons[i] )
		{
			delete buttons[i];
			buttons[i] = NULL;
		}
	}
	
	if( exitWindow )
	{
		delete exitWindow;
		exitWindow = NULL;
	}

}

void Exit::createExitWindow(sf::RenderWindow *mainWindow)
{	

	exitWindow = new sf::RenderWindow(sf::VideoMode(EXIT_WINDOW_WIDTH, EXIT_WINDOW_HEIGHT), "Exit Window", sf::Style::None);
	//setting the position of exit window in the middle of the main window
	sf::Vector2i position = mainWindow->getPosition(); 
	position.x += 300;
	position.y += 200;
	exitWindow->setPosition(position);
}

void Exit::resumeButton( sf::Vector2f pos )
{
	button *resume = new button();
	resume->name = "RESUME";

    sf::Vector2f size(70.f, 30.f);

    resume->createButton(size, pos);

	buttons.push_back(resume);
}

void Exit::restartButton( sf::Vector2f pos )
{
	button *restart = new button();
	restart->name = "RESTART";

    sf::Vector2f size(70.f, 30.f);

    restart->createButton(size, pos);

	buttons.push_back(restart);	
}

void Exit::quitButton( sf::Vector2f pos )
{
	button *quit = new button();
	quit->name = "QUIT";

    sf::Vector2f size(60.f, 30.f);

    quit->createButton(size, pos);

	buttons.push_back(quit);
}

void Exit::Buttons()
{
	static bool buttonsMade = false;

	//for resume button
  	sf::Vector2f pos1(25.f, 45.f);
	//for quit button
   sf::Vector2f pos2(210.f, 45.f);
   //for restart button
   sf::Vector2f pos3(117.f, 45.f);


	if( buttons.size() == 0 && !buttonsMade )
	{
		//firstly resume button is pushed to the vector and then others
		resumeButton( pos1 );
		restartButton( pos3 );
		quitButton( pos2 );

		buttonsMade = true;

	}
	//resume button
	buttons[0]->drawButton(exitWindow);
	//restart button
	buttons[1]->drawButton(exitWindow);
	//quit button
	buttons[2]->drawButton(exitWindow);

	renderButtons(pos1, pos2, pos3);
}

void Exit::renderButtons( sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f pos3 )
{

    //loading the resume message
    sf::Text message;
    message.setFont(font);
    message.setString("RESUME");
    message.setCharacterSize(20);
    message.setFillColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    message.setPosition(pos1.x, pos1.y); //position of the resume text

    exitWindow->draw(message);


    //loading the quit message
    sf::Text message2;
    message2.setFont(font);
    message2.setString("QUIT");
    message2.setCharacterSize(20);
    message2.setFillColor(sf::Color::Black);
    message2.setStyle(sf::Text::Bold);
    message2.setPosition(pos2.x, pos2.y); //position of the quit text

    exitWindow->draw(message2);


    //loading the restart message
    sf::Text message3;
    message3.setFont(font);
    message3.setString("RESTART");
    message3.setCharacterSize(20);
    message3.setFillColor(sf::Color::Black);
    message3.setStyle(sf::Text::Bold);
    message3.setPosition(pos3.x, pos3.y); //position of the restart text

    exitWindow->draw(message3);
}

//this function is particularly made for levels map
void Exit::runExit()
{
	bool closeWindow = false;
	bool buttonsMade = false;

	sf::Vector2f pos1(50.f, 45.f);
	sf::Vector2f pos2(190.f, 45.f);

	while(exitWindow->isOpen())
	{
		exitWindow->clear(sf::Color(237, 206, 149));
		exitMessage( "         Are you sure? " );
		
		if( buttons.size() == 0 && !buttonsMade )
		{
			//firstly resume button is pushed to the vector and then quit button
			resumeButton( pos1 );
			quitButton( pos2 );

			buttonsMade = true;
		}

		//resume button
		buttons[0]->drawButton(exitWindow);
		//quit button
		buttons[1]->drawButton(exitWindow);


		//render resume button text and quit button text
	   //loading the resume message
	   sf::Text message;
	   message.setFont(font);
	   message.setString("RESUME");
	   message.setCharacterSize(20);
	   message.setFillColor(sf::Color::Black);
	   message.setStyle(sf::Text::Bold);
	   message.setPosition(pos1.x, pos1.y); //position of the resume text

	   exitWindow->draw(message);


	   //loading the quit message
	   sf::Text message2;
	   message2.setFont(font);
	   message2.setString("QUIT");
	   message2.setCharacterSize(20);
	   message2.setFillColor(sf::Color::Black);
	   message2.setStyle(sf::Text::Bold);
	   message2.setPosition(pos2.x, pos2.y); //position of the quit text

	   exitWindow->draw(message2);


		//event loop 	
		sf::Event event;
		//to prevent from unresponsiveness
		while(exitWindow->pollEvent(event))
		{}

	   if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	   {
		   int MouseX = sf::Mouse::getPosition(*exitWindow).x;
         int MouseY = sf::Mouse::getPosition(*exitWindow).y;
         //resume button
			sf::Rect<float> buttonArea1 = buttons[0]->getRect();	
			if( buttonArea1.contains(MouseX, MouseY) )
			{
			   closeWindow = true;
		      EXIT = false;
            //PAUSED = false;	  		
			}
			//quit button
			sf::Rect<float> buttonArea2 = buttons[1]->getRect();
			if( buttonArea2.contains(MouseX, MouseY) ) 
			{
			   closeWindow = true;
		      EXIT = true;  		
			}		
	   }

		exitWindow->display();
		if( closeWindow )
		{
			exitWindow->close();
		}
	}
}

/* we don't want restart button to function while the program is in welcomer state 
   hence we have passed hasGreeted data member of welcomer*/
void Exit::runExitWindow( bool hasGreeted )
{	
	bool closeWindow = false;

	while(exitWindow->isOpen())
	{
		exitWindow->clear(sf::Color(237, 206, 149));
		exitMessage( "         Game is Paused!!! " );
		Buttons();
		
		//event loop	
		sf::Event event;
		while(exitWindow->pollEvent(event))
		{}

	   if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	   {
		   int MouseX = sf::Mouse::getPosition(*exitWindow).x;
         int MouseY = sf::Mouse::getPosition(*exitWindow).y;
         //resume button
			sf::Rect<float> buttonArea1 = buttons[0]->getRect();	
			if( buttonArea1.contains(MouseX, MouseY) )
			{
			   closeWindow = true;
		      EXIT = false;
            PAUSED = false;	  		
			}
			//restart button
			sf::Rect<float> buttonArea2 = buttons[1]->getRect();	
			if( hasGreeted && buttonArea2.contains(MouseX, MouseY) ) 
			{
			   closeWindow = true;
		      RESTART = true;
		      EXIT = false;
		      PAUSED = false;  		
			}
			//quit button
			sf::Rect<float> buttonArea3 = buttons[2]->getRect();
			if( buttonArea3.contains(MouseX, MouseY) ) 
			{
			   closeWindow = true;
		      EXIT = true;  		
			}		
	   }

		exitWindow->display();
		if( closeWindow )
		{
			exitWindow->close();
		}
	}
}


void Exit::exitMessage( std::string msg )
{
	//loading font for exit message
	if(!font.loadFromFile("assets/fonts/Chocolate_Covered_Raindrops.ttf"))
	{
		std::cerr << "Unable to load font\n";
	}

	//loading the exit message
	sf::Text message;
	message.setFont(font);
	message.setString( msg );
	message.setCharacterSize(30);
	message.setFillColor(sf::Color::Black);
	message.setStyle(sf::Text::Bold);
	message.setPosition(5.f, 5.f); //position of the exit text

	exitWindow->draw(message);
}
