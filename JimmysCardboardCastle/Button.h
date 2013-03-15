#pragma once
#include "TextureSprite.h"
#include "Game.h"

class Button: public TextureSprite
{
public:
	Button(double x, double y, int sizeX, int sizeY, std::string filename, void (*callbackFunction)(World *) = NULL) : TextureSprite(filename)
	{
		setPosition(x, y);
		setNumberOfAnimations(1);
		setSpriteFrameSize(sizeX, sizeY);
		addSpriteAnimFrame(0, 0, 0);
		hitbox = Hitbox(0, 0, sizeX, sizeY);
	}
	virtual void update();

	virtual void callback()
	{
		if (callbackFunction) callbackFunction(world);
	};

private:
	void (*callbackFunction)(World *);
};