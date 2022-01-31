#include "Tiles.h"

StaticBox::StaticBox( Vector2d position, Vector2d size, b2World* world )
:
Entity( position )
{
	m_BodyDef.type = b2_staticBody;
	m_Body = world->CreateBody( &m_BodyDef );

	float width = size.x;
	float height = size.y;

	b2Vec2 Center = b2Vec2( toBoxCoord(width/2), toBoxCoord(height/2) );

    m_shape.SetAsBox(toBoxCoord(width/2), toBoxCoord(height/2), Center, 0);
	m_FixtureDef.shape = &m_shape;
	m_FixtureDef.density = 50.f;
	m_FixtureDef.friction = 0.45f;
	m_Body->CreateFixture( &m_FixtureDef );
	m_Body->SetUserData( this );
}

StaticBox::~StaticBox()
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