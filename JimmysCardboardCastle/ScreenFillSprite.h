#pragma once
#include "Sprite.h"

//  This sprite fills the screen with whatever color you set it to have upon creation. Can have alpha transparency.
class ScreenFillSprite: public Sprite
{
public:
	ScreenFillSprite(float red, float green, float blue, float alpha = 1.0);
	virtual void draw(Vector2D);

	float red;
	float green;
	float blue;
	float alpha;
};