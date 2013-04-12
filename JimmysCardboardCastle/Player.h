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

	void heal(double heal) { health += heal; }
	void damage(double damage) { if (invincibleTimer <= 0) { health -= damage; invincibleTimer = invincibleLength; } }
	void scoreUp(double points) { score += points; }
	void cookiesUp(double cookies) { this->cookies += cookies; }

	InputInfo *input;

	Vector2D moveSpeed;
	double jumpVelocity;
	double bootJumpVelocity;

	// Items //
	bool hasBoots;
	bool hasBat;

	bool useBat;

	double score;
	double cookies;
	double health;

	int invincibleTimer;
	int invincibleLength;

	double batDistance;
private:
	bool jumpReady;
	Sound jumpSound;
};