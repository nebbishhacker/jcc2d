#pragma once
#include "physicssprite.h"
class AsianPaperBoy : public PhysicsSprite
{
public:
	AsianPaperBoy(double x, double y);
	void initialize();
	void update();

private:
	// state variables
	bool walking;
	bool attacking;
	bool gotHit;
};