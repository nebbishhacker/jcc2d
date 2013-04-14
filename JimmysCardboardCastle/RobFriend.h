#pragma once
#include "physicssprite.h"
class RobFriend : public PhysicsSprite
{
public:
	RobFriend(double x, double y);
	void initialize();
	void update();

	// state variables
	bool walking;
	bool attacking;
	bool gotHit;
	bool thrown;

	bool willAttack;
};