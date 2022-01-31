#include "Welcomer.h"

//for controlling appearance of cursor
static sf::Time text_effect_time;
static bool show_cursor;

Welcomer::Welcomer(sf::RenderWindow* window)
{
	hasGreeted = false;
	assignScreen( window );
    int total_decor_aliens = 13;

    //welome board texture and sprite
    if(!bTexture.loadFromFile("assets/Texture2.png"))
    {
        std::cerr << "Unable to load texture.\n";
    }
    else
    {
        bSprite.setTexture(bTexture);
    }

    //loads decor aliens
    for(int i = 0; i < total_decor_aliens; i++)
    {   
        std::string path = "assets/decor/";

        std::stringstream aName;
        aName << path << "decor" << (i+1) << ".png";

        sf::Texture * t = TextureManager::loadTexture( aName.str().c_str() );
        aTextures.push_back( t );
    }

    //seed for generating pseudo random numbers
    srand( time(NULL) );
}
Welcomer::~Welcomer()
{
    Initiator::close();
    

    if( playerName )
    {
        delete playerName;
        playerName = NULL;
    }
    if( pButton )
    {
        delete pButton;
        pButton = NULL;
    }
    if( iButton )
    {
        delete iButton;
        iButton = NULL;
    }


    for(unsigned i = 0; i < aTextures.size(); i++)
    {
        if( aTextures[i] )
        {
            delete aTextures[i];
            aTextures[i] = NULL;
        } 
    }
}


void Welcomer::welcome()
{	
	static bool isText = false;

	//loading font for welcome message
	if(!isText)
	{
		if(!font.loadFromFile("assets/fonts/Chocolate_Covered_Raindrops.ttf"))
		{
			std::cerr << "Unable to load font\n";
		}
		playerName = new sf::Text("", font, 40);

		isText = true;
	}

    sf::Vector2f position(120.f , 80.f );

    bSprite.setPosition( position );
    sf::IntRect rect = bSprite.getTextureRect();
    float X = 720.f/rect.width;
    float Y = 210.f/rect.height;
    bSprite.setScale(X, Y);

    m_window->draw(bSprite);

	//loading the welcome message
	sf::Text message;
	message.setFont(font);
	message.setString("Hello, player. Dwellers of Kepler-512b really need your help\nto protect their children and riches.\nAre you willing to help them? If so,\n Please, enter a username. (At most 15 characters.)\n");
	message.setCharacterSize(40);
	message.setFillColor(sf::Color::Black);
	message.setStyle(sf::Text::Bold);
	message.setPosition(140.f, 100.f); //position of the welcome text

	m_window->draw(message);

    //for decorative purposes only
    renderAliens();
}

void Welcomer::showCursor()
{

    text_effect_time += clock.restart();

    if (text_effect_time >= sf::seconds(0.5f))
    {
        show_cursor = !show_cursor;
        text_effect_time = sf::Time::Zero;
    }
}

void Welcomer::promptBox()
{
	sf::RectangleShape prompt;
	prompt.setSize(sf::Vector2f(280.f, 50.f));
	prompt.setFillColor(sf::Color::Black);
	prompt.setPosition(200.f, 310.f);

	m_window->draw(prompt);
}

void Welcomer::drawText()
{
    showCursor();

    playerName->setString(playerInput + (show_cursor ? '|' : ' '));
    playerName->setFillColor(sf::Color::White);
    playerName->setPosition(200.f, 300.f);
   	playerName->setStyle(sf::Text::Bold);

    m_window->draw(*playerName);
}

void Welcomer::handleInput(sf::Event& event)
{
    if (playerInput.size() <= 15 && event.type == sf::Event::TextEntered)
	{
    	if (std::isprint(event.text.unicode))
    		playerInput +=(event.text.unicode);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
    	if (event.key.code == sf::Keyboard::BackSpace)
        {
            if (!playerInput.empty())
               	playerInput.erase(playerInput.size()-1);
        }
    }        
}

void Welcomer::playButton()
{
    static bool buttonMade = false;
    sf::Vector2f size(50.f, 30.f);
    sf::Vector2f pos(500.f, 320.f);

    if(!buttonMade)
    {
        pButton = new button();
        pButton->name = "PLAY";

        pButton->createButton(size, pos);

        buttonMade = true;
    }

    pButton->drawButton( m_window );

    //rendering play text
    sf::Text message;
    message.setFont(font);
    message.setString("PLAY");
    message.setCharacterSize(20);
    message.setFillColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    message.setPosition(pos.x, pos.y); 

    sf::Rect<float> buttonArea = pButton->getRect();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int MouseX = sf::Mouse::getPosition(*m_window).x;
        int MouseY = sf::Mouse::getPosition(*m_window).y;

        if(buttonArea.contains(MouseX, MouseY) && playerInput.size() > 0)
        {
            hasGreeted = true;
            player_name = playerInput;
        }
    }

    m_window->draw(message);
}

//handles instruction button
void Welcomer::InsButton( Exit *exitMenu )
{	
    static bool buttonMade = false;
    static bool goBack = false;

    sf::Vector2f size(150.f, 30.f);
    sf::Vector2f pos(575.f, 320.f);

    if(!buttonMade)
    {
        iButton = new button();
        iButton->name = "INSTRUCTIONS";

        iButton->createButton(size, pos);

        buttonMade = true;
    }

    iButton->drawButton( m_window );

    //rendering instructions text
    sf::Text message;
    message.setFont(font);
    message.setString("HOW TO PLAY?");
    message.setCharacterSize(20);
    message.setFillColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    message.setPosition(pos.x, pos.y); 

    sf::Rect<float> buttonArea = iButton->getRect();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int MouseX = sf::Mouse::getPosition(*m_window).x;
        int MouseY = sf::Mouse::getPosition(*m_window).y;

        if(buttonArea.contains(MouseX, MouseY))
        {	
        	sf::Event event;
            bool isClosed = false;
            while( !goBack )
            {	
        		m_window->clear(sf::Color::Black);
				m_window->draw(*background);

				while(m_window->pollEvent( event ))
                {
                    if( event.type == sf::Event::Closed )
                    {
                        exitMenu->setPAUSE_VALUE();
                        isClosed = true;
                        goBack = true;
                        break;
                    }
                }

                if(isClosed)
                {
                    break;
                }

				Instructions();
				goBack = exitIns();

				m_window->display();
            }
        }
        goBack = false;
    }

    m_window->draw(message);
}

void Welcomer::Instructions()
{
    sf::Vector2f position(110.f , 80.f );

    bSprite.setPosition( position );
    sf::IntRect rect = bSprite.getTextureRect();
    float X = 740.f/rect.width;
    float Y = 496.f/rect.height;
    bSprite.setScale(X, Y);

    m_window->draw(bSprite);

	//loading instructions
	sf::Text message;
	message.setFont(font);
	message.setString("Hello, player.\nThe rules of this game are quite simple.\nYou should fight the enemies with magical\nweapons and a magical catapult.\n\n*Take your mouse pointer near the catapult and left-click.\n*You will see the trajectory that will be followed by the \nweapon. Set the best trajectory and release the mouse button.\n*If the weapon hits the enemies, you will earn points.\n*Once all the enemies are killed, you will advance to next\nlevel.\n\t\t\t\tTHANK YOU!!!\n");
	message.setCharacterSize(40);
	message.setFillColor(sf::Color::Black);
	message.setStyle(sf::Text::Bold);
	message.setPosition(130.f, 100.f);

	m_window->draw(message);

    //for decorative purposes only
    renderAliens();
}

bool Welcomer::exitIns()
{	
    sf::Vector2f size(80.f, 40.f);
    sf::Vector2f pos(800.f, 20.f);

    button exit;
    exit.name = "goBack";

    exit.createButton(size, pos);
    exit.drawButton( m_window );

    //rendering goBack text
    sf::Text message;
    message.setFont(font);
    message.setString("BACK");
    message.setCharacterSize(30);
    message.setFillColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    message.setPosition(pos.x, pos.y); 

    sf::Rect<float> buttonArea = exit.getRect();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int MouseX = sf::Mouse::getPosition(*m_window).x;
        int MouseY = sf::Mouse::getPosition(*m_window).y;

        if(buttonArea.contains(MouseX, MouseY))
        {
            return true;
        }
    }

    m_window->draw(message);
    return false;
}

//rendering the cursor and text entered by the player
void Welcomer::greetPlayer(Exit* exitMenu)
{
    promptBox(); //draw prompt box
    drawText();
    playButton();
    InsButton( exitMenu );

}

void Welcomer::renderAliens()
{
    static unsigned int counter = 0;
    static int count = 5;
    counter++;

    if( counter > 40 )
    {
        counter = 0;
        //generate a random number between 0 and 9
        count = rand() % 9;
    }

    aSprite.setTexture( *(aTextures[ count ]) );
    sf::Vector2f position1(20.f , 80.f );
    aSprite.setPosition( position1 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 1 ]) );
    sf::Vector2f position2(20.f , 180.f );
    aSprite.setPosition( position2 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 2 ]) );
    sf::Vector2f position3(20.f , 280.f );
    aSprite.setPosition( position3 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 3 ]) );
    sf::Vector2f position4(20.f , 380.f );
    aSprite.setPosition( position4 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 4 ]) );
    sf::Vector2f position5(20.f, 480.f );
    aSprite.setPosition( position5 );
    m_window->draw( aSprite );

    //for right side
    aSprite.setTexture( *(aTextures[ count + 3 ]) );
    sf::Vector2f position6(870.f , 80.f );
    aSprite.setPosition( position6 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 4 ]) );
    sf::Vector2f position7(870.f , 180.f );
    aSprite.setPosition( position7 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 1 ]) );
    sf::Vector2f position8(870.f, 280.f );
    aSprite.setPosition( position8 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count ]) );
    sf::Vector2f position9(870.f, 380.f );
    aSprite.setPosition( position9 );
    m_window->draw( aSprite );

    aSprite.setTexture( *(aTextures[ count + 2 ]) );
    sf::Vector2f position10(870.f, 480.f );
    aSprite.setPosition( position10 );
    m_window->draw( aSprite );

}


