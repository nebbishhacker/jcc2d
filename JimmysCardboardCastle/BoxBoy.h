#pragma once
#include "physicssprite.h"
class BoxBoy : public PhysicsSprite
{
public:
	BoxBoy(double x, double y);
	void initialize();
	void update();

private:
	// state variables
	bool walking;
};