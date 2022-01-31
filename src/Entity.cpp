#include "Entity.h"

Entity::Entity( Vector2d position )
:
m_Body(NULL),
m_Texture(NULL),
m_Sprite(NULL)
{
	m_Position = position;
	m_BodyDef.position = b2Vec2( toBoxCoord(position.x), toBoxCoord(position.y ) );
}

void Entity::load( const char* path )
{
	m_Texture = TextureManager::loadTexture(path);
	if ( !m_Texture )
		std::cerr << "Entity Texture not loaded\n";

	m_Sprite = SpriteManager::loadSprite(m_Texture);
	if ( !m_Sprite )
		std::cerr << "Entity Spirite wasn\'t loaded\n";

}

void Entity::render( sf::RenderWindow* window )
{
	b2Vec2 pos = m_Body->GetPosition();

	m_Sprite->setPosition( toPixelCoord(pos.x), toPixelCoord(pos.y) );
	window->draw( *m_Sprite );

}


Entity::~Entity()
{
	if( m_Sprite )
	{
		delete m_Sprite;
		m_Sprite = NULL;
	}
	if( m_Texture )
	{
		delete m_Texture;
		m_Texture = NULL;
	}
	if( m_Body ) m_Body = NULL;
}