#pragma once
#include "TextureSprite.h"

struct _InputInfo; // forward declaration
typedef _InputInfo InputInfo; // multi-step (why use typedef, anyways?)

//  Originally used to make sure collisions work right, then repurposed to an odd looking platform.
//	It's probably not a good idea to rely on anything with "Test" in the name.
class CollTestBox: public TextureSprite
{
public:
	CollTestBox(double x, double y);
	void initialize();
	void update();
	InputInfo *input;
};