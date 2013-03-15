#include "Button.h"
#include "Game.h"

Button::Button(double x, double y, int sizeX, int sizeY, std::string filename, void (*callbackFunction)(World *)) : TextureSprite(filename)
	{
		setPosition(x, y);
		setNumberOfAnimations(1);
		setSpriteFrameSize(sizeX, sizeY);
		addSpriteAnimFrame(0, 0, 0);
		hitbox = Hitbox(0, 0, sizeX, sizeY);
		this->callbackFunction = callbackFunction;
	}

void Button::update()
{
	if (world)
		if (world->input->mousePressed && collidePoint(world->input->clickX, world->input->clickY))
			callback();
}