#pragma once

#include <IL\ilut.h>
#include <map>
//#include <string>
#include <iostream>

struct textureInfo
{
	unsigned int textureID;
	float width;
	float height;
};

class TextureCache
{
public:
	unsigned int loadTexture(char* fileName)
	{
		textureInfo * t = new textureInfo;
		std::map<std::string, textureInfo*>::iterator it = textureMap.find(fileName);
		if (it == textureMap.end())
		{
			t->textureID = ilutGLLoadImage(fileName);
			t->width = ilGetInteger(IL_IMAGE_WIDTH);
			t->height = ilGetInteger(IL_IMAGE_HEIGHT);
			textureMap[fileName] = t;
			textureByID[t->textureID] = t;
			//std::cout << fileName << "\n";
		}
		else t = textureMap[fileName];
		lastWidth = t->width;
		lastHeight = t->height;
		return textureMap[fileName]->textureID;
	}
	float getWidth(unsigned int textureID) { return textureByID[textureID]->width; }
	float getHeight(unsigned int textureID) { return textureByID[textureID]->height; }

private:
	std::map<std::string, textureInfo*> textureMap;
	std::map<unsigned int, textureInfo*> textureByID;
	int lastWidth, lastHeight;
} textureCache;