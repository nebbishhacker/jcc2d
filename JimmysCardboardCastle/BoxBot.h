#pragma once
#include "physicssprite.h"
class BoxBot : public PhysicsSprite
{
public:
	BoxBot(double x, double y);
	void initialize();
	void update();

private:
	// state variables
	bool standing;
	bool walking;
	bool attacking;
	bool gotHit;
};