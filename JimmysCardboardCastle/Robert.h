#pragma once
#include "physicssprite.h"
class Robert : public PhysicsSprite
{
public:
	Robert(double x, double y);
	void initialize();
	void update();

private:
	// state variables
	bool walking;
	bool attacking;
	bool gotHit;
	bool thrown;

	bool willAttack;

	double health;
};