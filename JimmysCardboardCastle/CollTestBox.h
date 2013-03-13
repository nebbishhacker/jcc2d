#pragma once
#include "TextureSprite.h"

struct _InputInfo; // forward declaration
typedef _InputInfo InputInfo; // multi-step (why use typedef, anyways?)

class CollTestBox: public TextureSprite
{
public:
	CollTestBox(double x, double y);
	void initialize();
	void update();
	InputInfo *input;
};