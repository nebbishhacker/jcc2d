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

class TextureCache
{
public:
	unsigned int loadTexture(char* fileName);
	float getWidth(unsigned int textureID) { return textureByID[textureID]->width; }
	float getHeight(unsigned int textureID) { return textureByID[textureID]->height; }

private:
	std::map<std::string, textureInfo*> textureMap;
	std::map<unsigned int, textureInfo*> textureByID;
};

extern TextureCache textureCache;