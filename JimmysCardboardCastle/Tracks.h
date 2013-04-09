#pragma once
#include "physicssprite.h"
class Tracks : public PhysicsSprite
{
public:
	Tracks(double x, double y);
	void initialize();
	void update();

	// state variables
	bool walking;
};