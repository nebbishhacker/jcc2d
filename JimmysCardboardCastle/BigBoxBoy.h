#pragma once
#include "physicssprite.h"
class BigBoxBoy : public PhysicsSprite
{
public:
	BigBoxBoy(double x, double y);
	void initialize();
	void update();

	// state variables
	bool walking;
	bool active;
};