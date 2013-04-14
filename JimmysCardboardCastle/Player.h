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

	void heal(double heal) { if (health+heal <= 5) health += heal; else health = 5; }
	void damage(double damage) { if (invincibleTimer <= 0) { health -= damage; invincibleTimer = invincibleLength; } }
	void scoreUp(double points) { score += points; }
	void cookiesUp(double cookies) { this->cookies += cookies; }

	InputInfo *input;

	// Items //
	bool hasBoots;
	bool hasBat;
	bool hasWaterGun; 
	bool hasShield; 
	
	bool useBat;
	bool useWaterGun; 
	bool useShield; 

	double score;
	double cookies;
	double health;

	double marbles;
	double key; 
private:
	Vector2D moveSpeed;
	double jumpVelocity;
	double bootJumpVelocity;

	double batDistance;

	int invincibleTimer;
	int invincibleLength;

	bool jumpReady;
	Sound jumpSound;
	Sound batSound;
	Sound moonJumpSound;
	Sound lavaHitSound;
};