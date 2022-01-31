#include "LevelsMap.h"


lMap::lMap( sf::RenderWindow *window )
:
wMap()
{
	assignScreen(window); //this method is in initiator.h
    levelcount = 0;
    pButtonMade = false;

    if(!tSelectLevel.loadFromFile("assets/levelsMap/selectLevel.png"))
    {
        std::cerr << "Unable to load \'assets/levelsMap/selectLevel.png\' texture.\n";
    }
    else
    {
        selectLevelSprite.setTexture( tSelectLevel );
    }

    sf::Texture * t = TextureManager::loadTexture("assets/levelsMap/lock.png");
   	lTextures.push_back( t );
    
    t = TextureManager::loadTexture( "assets/levelsMap/1.png" );
    lTextures.push_back( t );

    m_levelTracker = 1;

    areaPushed = false;
    texturesPushed = false;
}

lMap::~lMap()
{
    for( unsigned i = 0; i < lTextures.size(); i++ )
    {
        if( lTextures[i] )
        {
            delete lTextures[i];
            lTextures[i] = NULL;
        }
    }

}

void lMap::chooseLevels( int& m_levelCount, int levelTracker )
{
    m_levelTracker = levelTracker;

    if( !texturesPushed )loadTextures();

    renderlTags();

    m_levelCount = select();
}

void lMap::loadTextures()
{
    if ( m_levelTracker > 1 && m_levelTracker < 8) //we have only eight level tags
    {

        //creates path for the textures and pushes them in the lTextures data member
        for(int i = 2; i <= m_levelTracker; i++)
        {   
            std::string path = "assets/levelsMap/";

            std::stringstream tName;
            tName << path << i << ".png";

            sf::Texture * t = TextureManager::loadTexture( tName.str().c_str() );
            lTextures.push_back( t );
        }

        texturesPushed = true;   
    }
}

int lMap::select()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int MouseX = sf::Mouse::getPosition(*m_window).x;
        int MouseY = sf::Mouse::getPosition(*m_window).y;

        for(unsigned i = 0; i < lAreas.size(); i++)
        {
            if(lAreas[i].contains(MouseX, MouseY))
            {
                //counting in array starts from zero
                //std::cerr << "value= " << i+1 << std::endl;
                return ( i+1 );
            }
        }
    }
    return 0;
}

void lMap::renderlTags()
{   
    selectLevelSprite.setPosition(340.f, 50.f);
    m_window->draw(selectLevelSprite);

    lSprite.setTexture(*(lTextures[1]));
    lSprite.setPosition( 200.f, 150.f );
    sf::IntRect rect1 = lSprite.getTextureRect();
    rect1.left = 200.f;
    rect1.top = 150.f;
    m_window->draw(lSprite);


    if( m_levelTracker > 1 )
        lSprite.setTexture( *(lTextures[2]) );
    else
        lSprite.setTexture( *(lTextures[0]) );
    lSprite.setPosition( 400.f, 150.f );
    sf::IntRect rect2 = lSprite.getTextureRect();
    rect2.left = 400.f;
    rect2.top = 150.f;
    m_window->draw(lSprite);


    if( m_levelTracker > 2)
        lSprite.setTexture(*(lTextures[3]));
    else
        lSprite.setTexture(*(lTextures[0]));
    lSprite.setPosition( 600.f, 150.f );
    sf::IntRect rect3 = lSprite.getTextureRect();
    rect3.left = 600.f;
    rect3.top = 150.f;
    m_window->draw(lSprite);



    if( m_levelTracker > 3)
        lSprite.setTexture(*(lTextures[4]));
    else
        lSprite.setTexture(*(lTextures[0]));
    lSprite.setPosition( 800.f, 150.f );
    sf::IntRect rect4 = lSprite.getTextureRect();
    rect4.left = 800.f;
    rect4.top = 150.f;
    m_window->draw(lSprite);



    if( m_levelTracker > 4)
        lSprite.setTexture(*(lTextures[5]));
    else
        lSprite.setTexture(*(lTextures[0]));
    lSprite.setPosition( 200.f, 250.f );
    sf::IntRect rect5 = lSprite.getTextureRect();
    rect5.left = 200.f;
    rect5.top = 250.f;
    m_window->draw(lSprite);



    if( m_levelTracker > 5)
        lSprite.setTexture(*(lTextures[6]));
    else
        lSprite.setTexture(*(lTextures[0]));
    lSprite.setPosition( 400.f, 250.f );
    sf::IntRect rect6 = lSprite.getTextureRect();
    rect6.left = 400.f;
    rect6.top = 250.f;
    m_window->draw(lSprite);



    if( !areaPushed )
    {
        lAreas.push_back( rect1 );

        if( m_levelTracker > 1)
            lAreas.push_back( rect2 );
        if( m_levelTracker > 2)
            lAreas.push_back( rect3 );
        if( m_levelTracker > 3)
            lAreas.push_back( rect4 );
        if( m_levelTracker > 4)
            lAreas.push_back( rect5 );
        if( m_levelTracker > 5)
            lAreas.push_back( rect6 );

        areaPushed = true;
    }

}
