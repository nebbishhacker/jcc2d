#pragma once
#include "physicssprite.h"
#include "SoundEngine.h"
class BigBoxBoy : public PhysicsSprite
{
public:
	BigBoxBoy(double x, double y);
	void initialize();
	void update();

	double health;
	double movespeed;

private:
	// state variables
	bool walking;
	bool active;
	Sound wallHitSound;
};