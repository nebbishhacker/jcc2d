#pragma once
#include "physicssprite.h"
class BlackPaperBoy : public PhysicsSprite
{
public:
	BlackPaperBoy(double x, double y);
	void initialize();
	void update();

	// state variables
	bool walking;
	bool attacking;
	bool gotHit;
};