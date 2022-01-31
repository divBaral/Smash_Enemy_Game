#include "wMap.h"
#include <string>
#include <sstream>
#include <cmath>


const float PPM = 32.f; 

sf::Rect<float> WeaponArea(sf::Vector2f(0.f, (576-128-90-80)),sf::Vector2f(220.f, 170.f)); //(position, dimensions) rectangle for weapon area 
std::string player_name;

//**********************************************wMap Zone***********************************************************
wMap::wMap( )


{  
    totalBullets = 4;

    //score setup
    if ( !font.loadFromFile("assets/fonts/Chocolate_Covered_Raindrops.ttf") )
    {
        std::cerr << "ScoreFont not loaded\n";
    }
    scoreText.setFont( font );
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setCharacterSize(30);
    //leveltext
    levelText.setFont( font );
    levelText.setFillColor(sf::Color::Black);
    levelText.setStyle(sf::Text::Bold);
    levelText.setCharacterSize(30);

    winX = 960.f;
    winY = 576.f;
    scoreText.setPosition(winX-200,0);
    levelText.setPosition(winX/2 - 100,0);
    score = 0;

    for(int i = 0; i < 4; i++)
    {
        Borders[i] = NULL;
    }

    for(int i = 0; i < totalBullets; i++)
    {
        Bullets[i] = NULL;
    }

    weaponBody = NULL;

    if( !levelTexture.loadFromFile("assets/Texture2.png") )
        std::cerr << "Unable to load level texture.\n";
    else
    {
        //sprites for levelText and scoreText
        Sprite1.setTexture( levelTexture );
        Sprite2.setTexture( levelTexture );
    }

    if( !tTexture.loadFromFile("assets/Texture.png") )
        std::cerr << "Unable to load level texture.\n";
    else
    {
        //sprites for transition texture
        tSprite.setTexture( tTexture );
    }
}

wMap::~wMap()
{   

    if (catapultText )
    {
        delete catapultText;
        catapultText = NULL;
    }

    if( catapult )
    {
        delete catapult;
        catapult = NULL;
    }

    for(int i = 0; i < totalBullets; i++)
    {   
        if( Bullets[i] )
        {
            delete Bullets[i];
            Bullets[i] = NULL;
        }
    }

    for(int i = 0; i < 4; i++)
    {   
        if( Borders[i] )
        {
            delete Borders[i];
            Borders[i] = NULL;
        }
    }

    //deleting buttons
    if( pButton )
    {
        delete pButton;
        pButton = NULL;
    }

    //next button
    if( next )
    {
        delete next;
        next = NULL;
    }

    m_gameCollisionListener.close();

    //clean vector elements
    cleanVectorElements();
    Initiator::close();

    if( weaponBody ) weaponBody = NULL;
    if( m_world ) m_world = NULL;
}

void wMap::loadBorders()
{

    int borderThickness = 10;
    Borders[BOTTOM] = new StaticBox( Vector2d(0, winY), Vector2d(winX, borderThickness), m_world ); //bottom edge
    Borders[LEFT]   = new StaticBox( Vector2d(-borderThickness, 0), Vector2d(borderThickness, winY), m_world ); //left edge
    Borders[RIGHT]  = new StaticBox( Vector2d(winX, 0), Vector2d(borderThickness, winY), m_world ); //right edge
    Borders[UPPER]  = new StaticBox( Vector2d(0, -borderThickness ), Vector2d(winX, borderThickness), m_world ); //upper edge 

}

void wMap::loadBullets()
{
    if( levelcount >= 4 )
    {
        totalBullets = 4;
    }
    else
    {
        totalBullets = 3;
    }
    
    for(int i = 0; i < totalBullets; i++)
    {
        Bullets[i] = new Weapon(Vector2d((i * 20.f), winY-128), m_world); //(position, world)
        (Bullets[i])->load( "assets/weapons/weapon.png" );
    }

    Bulletcount = totalBullets;    

}

void wMap::loadCatapult()
{
    catapultText = TextureManager::loadTexture( "assets/catapult.png" );
    if ( !catapultText )
        std::cerr << "[ERROR] >> Couldn't find \"assets/catapult.png\".\n";

    catapult = SpriteManager::loadSprite( catapultText );
    if ( !catapult )
        std::cerr << "[ERROR] >> Catapult sprite wasn\'t loaded.\n";
}

b2Vec2 wMap::getTrajectoryPoint( b2World* wrld, b2Vec2& startingPosition, b2Vec2& startingVelocity, float n )
{

    //velocity and gravity are given per second but we want time step values here
    float t = 1 / 60.0f; // seconds per time step (at 60fps)
    b2Vec2 stepVelocity = t * startingVelocity; // m/s
    b2Vec2 stepGravity = t * t * PPM * m_world->GetGravity(); // m/s/s
  
    return (startingPosition + n * stepVelocity + 0.5f * (n*n+n) * stepGravity);
    //derivation
    /*Let r0, v0 be intial position and velocity, r be position of the weapon after n steps in simulations,
    Since, accelation(step gravity) g is added (for each step) to velocity,
    velocity at any time, v = v0 + ng, 
    Thus, r = r0 + SUM(Vi)[from i = i to i = n] = r0 + nv0 + (n*n+n)/2 * g 
    */

}
void wMap::loadEntities()
{
    loadBorders();
    loadTiles();
    loadCatapult();
    loadElements();
    loadBullets();
    loadAliens();

}
void wMap::listenCollision()
{
    m_world->SetContactListener( &m_gameCollisionListener );
}

void wMap::transitionTexture( int& m_levelCount, int& levelTracker )
{   
    sf::Vector2i position(winX/2 - 175 , winY/2 - 60);

    tSprite.setPosition(static_cast<sf::Vector2f>(position));
    sf::IntRect rect = tSprite.getTextureRect();
    float X = 350.f/rect.width;
    float Y = 120.f/rect.height;
    tSprite.setScale(X, Y);

    m_window->draw( tSprite );

    //level completion message
    sf::Vector2f pos1(position.x + 15.f, position.y + 15.f);

    sf::Text message;
    message.setFont(font);
    message.setString("*****LEVEL COMPLETED*****");
    message.setCharacterSize(30);
    message.setFillColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    message.setPosition(pos1.x, pos1.y); //position of the resume text

    m_window->draw(message);

    sf::Vector2f size(70.f, 30.f);
    sf::Vector2f pos2(pos1.x + 100.f, pos1.y + 50.f);

    if(!nextButtonMade)
    {
        next = new button();
        next->name = "NEXT";

        next->createButton(size, pos2);

        nextButtonMade = true;
    }
    
    next->drawButton( m_window );

    //rendering next text 
    sf::Text message2;
    message2.setFont(font);
    message2.setString("NEXT");
    message2.setCharacterSize(20);
    message2.setFillColor(sf::Color::Black);
    message2.setStyle(sf::Text::Bold);
    message2.setPosition(pos2.x + 10, pos2.y);

    sf::Rect<float> buttonArea1 = next->getRect();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int MouseX = sf::Mouse::getPosition(*m_window).x;
        int MouseY = sf::Mouse::getPosition(*m_window).y;

        if(buttonArea1.contains(MouseX, MouseY))
        {
          //increase level Tracker of wMap class for LevelsMap header file
        if( levelTracker < 6 && m_levelCount == levelTracker )//there are 6 levels in our game at present
            levelTracker++;
        if( m_levelCount < 6 )m_levelCount++;
        else m_levelCount = 0;
        }
    }

    m_window->draw(message2);
}

void wMap::renderTiles()
{
    for( unsigned i = 0; i < tiles.size(); ++i )
        tiles[i]->render( m_window );
}

void wMap::renderElements()
{
    for ( unsigned i =0; i<woodElements.size(); ++i)
        woodElements[i]->render( m_window );

}


void wMap::renderCatapult()
{   
    //dimensions of actual pic
    float catapultPicX = 30.f;
    float catapultPicY = 90.f;

    //rendering catapult sprite
    catapult->setPosition((200-30), (winY-128-90));
    sf::IntRect rect2 = catapult->getTextureRect();
    catapult->setScale( catapultPicX/rect2.width, catapultPicY/rect2.height);
    m_window->draw(*catapult);

}


void wMap::renderBullets()
{

    for(int i = 0; i < totalBullets; i++)
    {
        (Bullets[i])->render( m_window );
    }

}
void wMap::renderAliens( )
{
    m_gameCollisionListener.cleanAliens(aliens, m_world);

    if ( aliens.size() == 0)
    	hasEnded = true;


    for ( unsigned i =0; i < aliens.size(); ++i) {
        aliens[i]->render( m_window );
       
    }

}

void wMap::renderScore()
{   
    Sprite1.setPosition(winX-220, 0);
    Sprite2.setPosition(winX/2 - 150, 0);

    sf::IntRect rect = Sprite1.getTextureRect();
    float X = 200.f/rect.width;
    float Y = 45.f/rect.height;
    Sprite1.setScale(X, Y);
    Sprite2.setScale(X, Y);

    m_window->draw( Sprite1 );
    m_window->draw( Sprite2 );

    score = (aliencount-aliens.size()) * 1000;
    std::stringstream ss;
    ss << "Score: " << score;
    
    scoreText.setString( ss.str() );
    ss.str("");
    ss << " LEVEL " << levelcount;
    levelText.setString( ss.str() );

    m_window->draw( scoreText );
    m_window->draw( levelText );
}


void wMap::renderEntities()
{

    renderTiles();
    renderCatapult();
    renderScore();
    renderElements();
    renderAliens();

}

void wMap::handleMouseButtonPressed()
{   

    b2Vec2 startingPosition;
    b2Vec2 startingVelocity;

    int X = sf::Mouse::getPosition( *m_window ).x;
    int Y = sf::Mouse::getPosition( *m_window ).y;

    if( WeaponArea.contains(X, Y) && Bulletcount > 0 )
    {
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
        {
            //setting condition to launch succeeding weapons
            if( readyToLaunch )
            {
                Bullets[Bulletcount - 1]->getBody()->SetTransform( b2Vec2(X/PPM, Y/PPM), 0 );

                startingPosition    = Bullets[Bulletcount - 1]->getBody()->GetPosition();
                startingPosition.x *= PPM;
                startingPosition.y *= PPM;
                startingVelocity    = b2Vec2((200-15-X) * 10, (winY-128-80-Y) * 10); // catapult is the origin

                //keeps track of the last weapon used
                weaponBody = Bullets[Bulletcount - 1];


                for (int i = 0; i < 120; i++) // goes 120 frames ahead to predict trajectory
                { 
                    if (i % 2 == 0)
                    {
                        b2Vec2 trajectoryPosition = getTrajectoryPoint(m_world, startingPosition, startingVelocity, i );
                        sf::CircleShape dot(3);
                        dot.setFillColor(sf::Color::White);
                        dot.setPosition( trajectoryPosition.x, trajectoryPosition.y);
                        dot.setOutlineThickness(1.f);
                        dot.setOrigin(4, 4);
                        dot.setOutlineColor(sf::Color::Black);
                        m_window->draw(dot);
                    }
                }


                //rendering rubber connecting catapult and the weapon
                sf::RectangleShape r1Shape;
                float rX = 200 - 3;
                float rY = winY - 128 - 80;
                float rLen = sqrt(pow((rX - startingPosition.x), 2) + pow((rY - startingPosition.y), 2));
                sf::Vector2f r1Size(rLen, 4.f);

                r1Shape.setSize(r1Size);
                r1Shape.setPosition(startingPosition.x, startingPosition.y);
                r1Shape.setFillColor(sf::Color(120, 1, 3));
                float slope = (startingPosition.y - rY) / (startingPosition.x - rX);
                float angle = atan(slope) * (180.f/b2_pi);
                if(startingPosition.x >= rX )
                    angle += 180.f;
                r1Shape.rotate(angle);
                m_window->draw(r1Shape);


                sf::RectangleShape r2Shape;
                rX = 200 - 28;
                rY = winY - 128 - 80;
                rLen = sqrt(pow((rX - startingPosition.x), 2) + pow((rY - startingPosition.y), 2));
                sf::Vector2f r2Size(rLen, 4.f);

                r2Shape.setSize(r2Size);
                r2Shape.setPosition(startingPosition.x, startingPosition.y);
                r2Shape.setFillColor(sf::Color(120, 1, 3));
                slope = (startingPosition.y - rY) / (startingPosition.x - rX);
                angle = atan(slope) * (180.f/b2_pi);
                if(startingPosition.x >= rX )
                    angle += 180.f;
                r2Shape.rotate(angle);
                m_window->draw(r2Shape);
            }
            else if( Bullets[Bulletcount - 1]->isAtRest() )
            {
                readyToLaunch = true;
                Bulletcount--;
            }
        }
    }
    else if( !WeaponArea.contains(X, Y) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && Bulletcount > 0 && readyToLaunch )
    {
        if( weaponBody )weaponBody->getBody()->SetTransform( b2Vec2(61/PPM, (winY-128-8)/PPM), 0 );
    }

}

void wMap::handleMouseButtonReleased( sf::Event& event )
{

    int X = sf::Mouse::getPosition(*m_window).x;
    int Y = sf::Mouse::getPosition(*m_window).y;

    if( WeaponArea.contains(X, Y) )
    {
        if( event.mouseButton.button == sf::Mouse::Left )
        {
            if( Bulletcount > 0 && readyToLaunch )
            {
                Bullets[Bulletcount - 1]->getBody()->SetLinearVelocity(b2Vec2((200-15-X)/PPM * 10,(576-128-80-Y)/PPM * 10)); 
                Bullets[Bulletcount - 1]->getBody()->SetAngularVelocity(0);

                readyToLaunch = false;
            }
        }
    }
}

void wMap::makeButton( Exit * exitMenu, bool isQuitButton )
{

    sf::Vector2f pos(10.f, 10.f);
    sf::Vector2f size(50.f, 30.f);



    std::string buttonName = "PAUSE";
    if ( isQuitButton )
        buttonName = "QUIT";



    if( !pButtonMade )
    {
        pButton = new button();
        pButton->name = buttonName;

        pButton->createButton(size, pos);
        pButtonMade = true;
    }


    
    pButton->drawButton( m_window );

    //rendering pause text
    sf::Text message;
    message.setFont(font);
    message.setString(buttonName);
    message.setCharacterSize(20);
    message.setFillColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    message.setPosition(pos.x, pos.y);

    sf::Rect<float> buttonArea = pButton->getRect();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int MouseX = sf::Mouse::getPosition(*m_window).x;
        int MouseY = sf::Mouse::getPosition(*m_window).y;

        if(buttonArea.contains(MouseX, MouseY))
        {
            exitMenu->setPAUSE_VALUE();
        }
    }

    m_window->draw(message);
}

//deletes all the vectors(data members)
void wMap::cleanVectorElements()
{   
    
    for ( unsigned i = 0; i < aliens.size(); ++i)
    {   
        if( aliens[i] )
        {
            delete aliens[i];
            aliens[i] = NULL;
        } 
    }   

    for ( unsigned i =0; i < woodElements.size(); ++i)
    {   
        if( woodElements[i] )
        {
            delete woodElements[i];
            woodElements[i] = NULL;
        }
    } 

    for( unsigned i = 0; i < tiles.size(); ++i )
    {   
        if( tiles[i] )
        {
             delete tiles[i];
            tiles[i] = NULL;
        }
    }
    
}