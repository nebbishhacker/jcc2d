#pragma once
#include "TextureSprite.h"
#include "SoundEngine.h"

struct _InputInfo; // forward declaration
typedef _InputInfo InputInfo; // multi-step (why use typedef, anyways?)

class Player: public TextureSprite
{
public:
	Player(double x, double y);
	void initialize();
	void update();
	InputInfo *input;
private:
	int vy;
	bool jumping;
	//Sound * jumpSound;
};