#include "TextureCache.h"

unsigned int TextureCache::loadTexture(char* fileName)
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
	}
	else t = textureMap[fileName];
	return textureMap[fileName]->textureID;
};

TextureCache textureCache;