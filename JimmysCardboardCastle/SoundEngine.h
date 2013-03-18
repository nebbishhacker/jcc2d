#pragma once

#include <string>
#include "fmod.hpp"
#pragma comment( lib, "fmodex_vc.lib" )

typedef FMOD::Sound * Sound;

class SoundEngine {
public:
	SoundEngine();
	~SoundEngine();

	Sound loadSound(std::string fileName);
	FMOD::Channel * playSound(Sound sound);

	void update();

private:
	FMOD::System * system;
};

extern SoundEngine soundEngine;