/****
 * 
 * overrides the BeginContact function of b2ContactListener class of Box2D
 * 
 ****/

#pragma once

#include <cstring>
#include <iostream>
#include "Alien.h"
#include "Weapon.h"
#include <typeinfo>
#include <vector>
#include <algorithm>

#include "SoundManager.h"


inline float square(float n ) { return n*n;}

class Listener : public b2ContactListener
{
public:   
    Listener() 
    {
      isDestroy = false;
      m_collisionSoundBuffer = SoundBufferManager::loadBuffer("assets/sound/cry_of_hurt.wav");
      m_collisionSound = SoundManager::loadSound(m_collisionSoundBuffer);
      m_collisionSound->setVolume(50.f);

    }

    void BeginContact(b2Contact* contact)
    {
      //body A
      body1 = contact->GetFixtureA()->GetBody();
      //body B
      body2 = contact->GetFixtureB()->GetBody();


      void* data1 = body1->GetUserData();
      if ( data1 )
         entity1 = static_cast<Entity*> ( data1 );
      void* data2 = body2->GetUserData();
      if ( data2 )
        entity2 = static_cast<Entity*> ( data2 );
       
      //names of bodies
      char* name1 = entity1->getInfo();
      char* name2 = entity2->getInfo();


      //find alien
      if ( !strcmp( name1 , "Alien") )
      {

        alienBody = body1;
        alien = dynamic_cast<Alien*>(entity1);

      }
      else if ( !strcmp(name2, "Alien") )
      {

        alienBody = body2;
        alien = dynamic_cast<Alien*>( entity2 );

      }

      

      //check if either of fixtures was a ball
      
      if ( ( strcmp(name2, "Alien") == 0 ) 
        || ( strcmp ( name1, "Alien")==0 ) )
        {

           b2Vec2 v1 =  body1->GetLinearVelocity();
           b2Vec2 v2 = body2->GetLinearVelocity();

           float impulse = square(v2.x - v1.x) + square( v2.y - v1.y );
           if ( static_cast<int> (impulse) > 150)
               isDestroy = true;

        }


    
    }
    void cleanAliens(std::vector<Alien*>& aliens, b2World* world)
    {

      if ( isDestroy )
      {
        m_collisionSound->play();
      }

      //GetContactList is the list of contacts attached to the body
      if ( isDestroy && alienBody->GetContactList() )
      {
         //delete alienBody from the world;
        world->DestroyBody( alienBody );
 
        if ( alien ) {
        //iterates through aliens and deletes the matching alien

        /*std::vector<Alien *>::iterator it;
          for( it = aliens.begin(); it < aliens.end(); it++)
          {
            if(*it == alien)
            {
              aliens.erase(it);
              break;
            }

          }*/

          aliens.erase( std::remove(aliens.begin(), aliens.end(), alien) );

          delete alien;
          alien = NULL;
        }
        isDestroy = false;

      }
    }

    void close()
    {
      if( m_collisionSound )
      {
        delete m_collisionSound;
        m_collisionSound = NULL;
      }
      if( m_collisionSoundBuffer )
      {
        delete m_collisionSoundBuffer;
        m_collisionSoundBuffer = NULL;
      }
      //deleting reference to mem
      if( entity1 )
      {
        entity1 = NULL;
      }
      if( entity2 )
      {
        entity2 = NULL;
      }
      if( alien )
      {
        alien = NULL;
      }
      if( alienBody )
      {
        alienBody = NULL;
      }
      if( alien )
      {
        alien = NULL;
      }
      if( body1 )
      {
        body1 = NULL;
      }
      if( body2 )
      {
        body2 = NULL;
      }
    }

private:
  sf::SoundBuffer* m_collisionSoundBuffer = NULL;
  sf::Sound* m_collisionSound = NULL;
  bool isDestroy;
  Entity* entity1=NULL, * entity2=NULL;
  b2Body* body1 = NULL,  *alienBody=NULL;
  Alien* alien=NULL;;

  b2Body* body2 = NULL;


};
