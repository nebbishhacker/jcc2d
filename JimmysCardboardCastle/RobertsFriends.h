#pragma once
#include "physicssprite.h"
class RobertsFriends : public PhysicsSprite
{
public:
	RobertsFriends(double x, double y);
	void initialize();
	void update();

	// state variables
	bool standing;
	bool walking;
	bool attacking;
	bool gotHit;
};