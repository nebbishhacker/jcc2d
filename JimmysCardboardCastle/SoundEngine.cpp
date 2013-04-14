#include "SoundEngine.h"
#include <iostream>

SoundEngine::SoundEngine()
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
	system->getChannel(0, &musicChannel);
	musicChannel->setPriority(0);
}

SoundEngine::~SoundEngine()
{
	system->release();
}

Sound SoundEngine::loadSound(std::string fileName)
{
	FMOD::Sound * fmodSound;
	Sound sound;
	std::map<std::string, Sound>::iterator it = soundMap.find(fileName);
	if (it == soundMap.end())
	{
		FMOD_RESULT result = system->createSound(fileName.c_str(), FMOD_2D, 0, &fmodSound);
		if (result != FMOD_OK) std::cout << "Loading file \"" << fileName << "\" failed with code " << result << "\n";
		sound = Sound(fmodSound);
	}
	else sound = soundMap[fileName];
	return sound;
}
Sound SoundEngine::loadStream(std::string fileName)
{
	FMOD::Sound * fmodSound;
	Sound sound;
	std::map<std::string, Sound>::iterator it = soundMap.find(fileName);
	if (it == soundMap.end())
	{
		FMOD_RESULT result = system->createStream(fileName.c_str(), FMOD_2D, 0, &fmodSound);
		if (result != FMOD_OK) std::cout << "Loading file \"" << fileName << "\" failed with code " << result << "\n";
		sound = Sound(fmodSound);
	}
	else sound = soundMap[fileName];
	return sound;
}
FMOD::Channel * SoundEngine::playSound(Sound &sound)
{
	FMOD::Channel * channel;
	system->playSound(FMOD_CHANNEL_FREE, sound.fmodSound, false, &channel);
	return channel;
}
FMOD::Channel * SoundEngine::playMusic(Sound &sound)
{
	FMOD::Channel * channel;
	unsigned int n = 0;
	system->playSound(FMOD_CHANNEL_REUSE, sound.fmodSound, false, &musicChannel);
	return channel;
}

void SoundEngine::update()
{
	system->update();
}

Sound::Sound(FMOD::Sound * fmodSound)
{
	this->fmodSound = fmodSound;
}

SoundEngine soundEngine;