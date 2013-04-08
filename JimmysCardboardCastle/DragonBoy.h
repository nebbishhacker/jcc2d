#pragma once
#include "physicssprite.h"
class DragonBoy : public PhysicsSprite
{
public:
	DragonBoy(double x, double y);
	void initialize();
	void update();

	// state variables
	bool standing;
	bool walking;
	bool attacking;
	bool gotHit;
};