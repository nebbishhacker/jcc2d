#pragma once
#include "PhysicsSprite.h"
#include "SoundEngine.h"

struct _InputInfo; // forward declaration
typedef _InputInfo InputInfo; // multi-step (why use typedef, anyways?)

//  The player class! Rather incomplete, but it works for now.
class Player: public PhysicsSprite
{
public:
	Player(double x, double y);
	void initialize();
	void update();
	InputInfo *input;
	Vector2D moveSpeed;
	double jumpVelocity;
	double bootJumpVelocity;
	bool hasBoots;
	double score;
private:
	bool jumpReady;
	Sound jumpSound;
};