#pragma once
#include "TextureSprite.h"
#include "Game.h"

//  Create a button, and it'll call it's callbackFunction when you click it!
class Button: public TextureSprite
{
public:
	Button(double x, double y, int sizeX, int sizeY, std::string filename, void (*callbackFunction)(World *) = NULL);

	virtual void update();

	virtual void callback() { if (callbackFunction) callbackFunction(world); }

private:
	void (*callbackFunction)(World *);
};