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

	void damage(double damage) { health -= damage; }
	void scoreUp(double points) { score += points; }

	InputInfo *input;

	Vector2D moveSpeed;
	double jumpVelocity;
	double bootJumpVelocity;

	bool hasBoots;
	double score;
	double health;

private:
	bool jumpReady;
	Sound jumpSound;
};