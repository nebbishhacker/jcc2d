#pragma once
#include "PhysicsSprite.h"
class Cookie : public PhysicsSprite
{
public:
	Cookie(double x, double y);
	//void initialize();
	void update();
	// I did actually re-write this, it beats copying because maybe, just maybe, I'll get it better if I do...
	// You just wasted time writing that one line
};