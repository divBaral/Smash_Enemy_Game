/****
 * 
 * handles the music and sound attributes of the game 
 * 
 ****/

#pragma once

#include <SFML/Audio.hpp>
#include <new> //for std::bad_alloc

class SoundBufferManager
{
public:

	SoundBufferManager();
	~SoundBufferManager();

	static sf::SoundBuffer* loadBuffer(const char* buffersheet);
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static sf::Sound* loadSound(sf::SoundBuffer*);
};