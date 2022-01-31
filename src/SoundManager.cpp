#include "SoundManager.h"

SoundBufferManager::SoundBufferManager(){}
SoundBufferManager::~SoundBufferManager(){}

sf::SoundBuffer* SoundBufferManager::loadBuffer(const char* SoundBufferSheet)
{
	sf::SoundBuffer* SoundBuffer = new sf::SoundBuffer();
	//SoundBuffer->setSmooth(true);
	SoundBuffer->loadFromFile(SoundBufferSheet);

	return SoundBuffer;
}

SoundManager::SoundManager(){}
SoundManager::~SoundManager(){}

sf::Sound* SoundManager::loadSound(sf::SoundBuffer* SoundBuffer)
{
	sf::Sound* Sound = new sf::Sound();
	Sound->setBuffer(*SoundBuffer);

	return Sound;
}