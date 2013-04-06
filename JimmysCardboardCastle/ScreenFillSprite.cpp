#include "ScreenFillSprite.h"
#include "Game.h"
#include "drawPrimitives.h"

ScreenFillSprite::ScreenFillSprite(float red, float green, float blue, float alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}
void ScreenFillSprite::draw(Vector2D)
{
	setColor(red, green, blue, alpha);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawRectangle(true, 0, 0, world->stateInfo->screenWidth, world->stateInfo->screenHeight, 0);
	glDisable(GL_BLEND);
}