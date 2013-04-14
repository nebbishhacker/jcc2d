#pragma once

#include <IL\ilut.h>
#include <map>
#include <string>

struct textureInfo
{
	unsigned int textureID;
	float width;
	float height;
};

// TextureCache is a singleton -- use TextureCache::getInstance to get a reference to the single instance.
// (I probably wouldn't normally use singletons, but this makes an excellent example of some of the things you can do with static variables/methods)
class TextureCache
{
public:
	static TextureCache * getInstance()	// Static method
	{
		static TextureCache INSTANCE;	// initializes a new static TextureCache instance on the first time it's called
		return &INSTANCE;				// returns the static TextureCache instance
	}
	unsigned int loadTexture(char* fileName);
	float getWidth(unsigned int textureID) { return textureByID[textureID]->width; }
	float getHeight(unsigned int textureID) { return textureByID[textureID]->height; }

private:
	TextureCache() {}	// Private constructor, so multiple instances can't be created
	//static TextureCache instance; // sole instance of textureCache

	std::map<std::string, textureInfo*> textureMap;
	std::map<unsigned int, textureInfo*> textureByID;
};

//extern TextureCache textureCache