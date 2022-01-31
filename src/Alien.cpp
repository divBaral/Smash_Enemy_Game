#include "Alien.h"


Alien::Alien( Vector2d position, float radius, b2World* world)
:
Entity( position )
{

	m_radius = radius;
	m_BodyDef.type = b2_dynamicBody;
	m_Shape.m_p.Set(0, 0);
	m_Shape.m_radius = m_radius / mPPM;

	m_Body = world->CreateBody( &m_BodyDef );

	m_FixtureDef.shape = &m_Shape;
	m_FixtureDef.density = 5.f;
	m_FixtureDef.restitution = 0.33f;
	m_FixtureDef.friction = 0.55f;
	m_Body->CreateFixture( &m_FixtureDef );

	m_Body->SetUserData( this );

}

void Alien::load(const char* path)
{
	
	m_Texture = TextureManager::loadTexture(path);
	if ( !m_Texture )
		std::cerr << "Entity Texture not loaded\n";

	m_Sprite = SpriteManager::loadSprite(m_Texture);
	if ( !m_Sprite )
		std::cerr << "Entity Spirite wasn\'t loaded\n";

}

void Alien::render( sf::RenderWindow* window )
{

	b2Vec2 pos = m_Body->GetPosition();

	m_Sprite->setPosition( toPixelCoord(pos.x), toPixelCoord(pos.y) );
	m_Sprite->setOrigin( m_radius, m_radius );
	m_Sprite->setRotation( m_Body->GetAngle() * 180/b2_pi );
	window->draw( *m_Sprite );


}

Alien::~Alien()
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