#pragma once

#include <string>
#include <map>
#include "FMOD/fmod.hpp"
#pragma comment( lib, "fmodex_vc.lib" )

//typedef FMOD::Sound * Sound;

class Sound
{
public:
	Sound(FMOD::Sound *);
	Sound() { null = true; }

	bool operator==(Sound s) { return fmodSound == s.fmodSound; }
	bool operator!=(Sound s) { return !(*this == s); }

	FMOD::Sound * fmodSound;
	bool null;
};

class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();

	Sound loadSound(std::string fileName);
	Sound loadStream(std::string fileName);
	FMOD::Channel * playSound(Sound &sound);
	FMOD::Channel * playMusic(Sound &sound);
	Sound getCurrentMusic();

	void update();

private:
	FMOD::System * system;
	std::map<std::string, Sound> soundMap;
	FMOD::Channel * musicChannel;
	Sound currentMusic;
};

extern SoundEngine soundEngine;