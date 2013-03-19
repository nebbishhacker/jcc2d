#include "SoundEngine.h"
#include <iostream>

SoundEngine::SoundEngine()
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
}

SoundEngine::~SoundEngine()
{
	system->release();
}

Sound SoundEngine::loadSound(std::string fileName)
{
	Sound sound;
	std::map<std::string, Sound>::iterator it = soundMap.find(fileName);
	if (it == soundMap.end())
	{
		FMOD_RESULT result = system->createSound(fileName.c_str(), FMOD_2D, 0, &sound);
		if (result != FMOD_OK) std::cout << "Loading file \"" << fileName << "\" failed with code " << result << "\n";
	}
	else sound = soundMap[fileName];
	return sound;
}
FMOD::Channel * SoundEngine::playSound(Sound sound)
{
	FMOD::Channel * channel;
	system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	return channel;
}

void SoundEngine::update()
{
	system->update();
}

SoundEngine soundEngine;