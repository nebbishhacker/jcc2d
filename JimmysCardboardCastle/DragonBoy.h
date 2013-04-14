#pragma once
#include "physicssprite.h"
class DragonBoy : public PhysicsSprite
{
public:
	DragonBoy(double x, double y);
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