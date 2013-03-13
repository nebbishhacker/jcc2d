#pragma once
#include "TextureSprite.h"

class Background: public TextureSprite
{
public:
	Background(double x, double y, int sizeX, int sizeY, std::string filename, float layerID = -100, float scrollFactorX = 1, float scrollFactorY = 1) : TextureSprite(filename)
	{
		setPosition(x, y);
		setNumberOfAnimations(1);
		setSpriteFrameSize(sizeX, sizeY);
		addSpriteAnimFrame(0, 0, 0);
		setLayerID(layerID);
		setScrollFactor(scrollFactorX, scrollFactorY);
	}
};