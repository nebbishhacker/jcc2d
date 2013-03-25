#include "Button.h"
#include "Game.h"

Button::Button(double x, double y, int sizeX, int sizeY, std::string filename, void (*callbackFunction)(World *), bool hover) : TextureSprite(filename)
	{
		this->hover = hover;
		setPosition(x, y);
		int frames = 1;
		if (hover) {
			frames = 2;
		}
		setNumberOfAnimations(frames);
		setSpriteFrameSize(sizeX, sizeY);
		for (int i = 0; i < frames; ++i) addSpriteAnimFrame(i, 0, i * sizeY);
		hitbox = Hitbox(0, 0, sizeX, sizeY);
		this->callbackFunction = callbackFunction;
	}

void Button::update()
{
	if (world) {
		if (collidePoint(world->input->currentX + world->cameraX * scrollFactorX, world->input->currentY + world->cameraY * scrollFactorY)) {
			if (world->input->mousePressed) callback();
			if (hover) setCurrentAnimation(1);
		}
		else if (hover) setCurrentAnimation(0);
	}
}