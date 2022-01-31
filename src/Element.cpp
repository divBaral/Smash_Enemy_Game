#include "Element.h"

Element::Element( Vector2d position, Vector2d size, b2World* world)
:
Entity( position )
{
	m_BodyDef.type = b2_dynamicBody;
	m_Body = world->CreateBody( &m_BodyDef );

	float width = size.x;
	float height = size.y;

	b2Vec2 Center = b2Vec2( toBoxCoord(width/2), toBoxCoord(height/2) );

    m_shape.SetAsBox(toBoxCoord(width/2), toBoxCoord(height/2), Center, 0);
	m_FixtureDef.shape = &m_shape;
	m_FixtureDef.density = 1.f;
	m_FixtureDef.friction = 0.55f;
	m_Body->CreateFixture( &m_FixtureDef );
	m_Body->SetUserData( this );

}

void Element::load( const char* path, const Vector2d& size )
{
	Entity::load( path );
	sf::IntRect rect = m_Sprite->getTextureRect();
    float X = size.x/rect.width;
    float Y = size.y/rect.height;
    m_Sprite->setScale(X, Y);
}

void Element::render( sf::RenderWindow* window )
{
	b2Vec2 pos = m_Body->GetPosition();

	m_Sprite->setPosition( toPixelCoord(pos.x), toPixelCoord(pos.y) );
	if ( m_Body->GetAngle() )
		m_Sprite->setRotation( m_Body->GetAngle() * 180/b2_pi);
	window->draw( *m_Sprite );

}

Element::~Element()
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