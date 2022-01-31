#include "Initiator.h"
#include "TextureManager.h"

Initiator::Initiator(){}
Initiator::~Initiator(){}

bool Initiator::loadBackground(const char* backgroundImg)
{
	bool success = true;

	//load background picture 
	windowTexture = TextureManager::loadTexture(backgroundImg);
	background = SpriteManager::loadSprite(windowTexture);
    //stretch backgroundImg
    sf::IntRect rect = background->getTextureRect();
    float X = static_cast<float>(m_window->getSize().x)/rect.width;
    float Y = static_cast<float>(m_window->getSize().y)/rect.height;
    background->setScale(X, Y);

    if(!windowTexture || !background) success = false;

    return success;
}

void Initiator::assignScreen(sf::RenderWindow * window)
{	
	m_window = window;
}

void Initiator::renderBackground()
{	
	m_window->clear(sf::Color::Black);
	m_window->draw(*background);
}


void Initiator::close()
{	
	if ( windowTexture )
	{
		delete windowTexture;
		windowTexture = NULL;
	}
	if ( background )
	{
		delete background;
		background = NULL;
	}
	if(m_window) m_window = NULL; //window is deleted in main file
}