#pragma once
#include "TextureSprite.h"
#include "SoundEngine.h"

struct _InputInfo; // forward declaration
typedef _InputInfo InputInfo; // multi-step (why use typedef, anyways?)

//  The player class! Rather incomplete, but it works for now.
class Player: public TextureSprite
{
public:
	Player(double x, double y);
	void initialize();
	void update();
	InputInfo *input;
	double mass;
	Vector2D netForce;
	Vector2D netAcceleration;
	Vector2D velocity;
	static const double groundFriction;
	static const double airDrag;
	static const Vector2D moveSpeed;
	static const double airManeuverability;
	static const double jumpVelocity;
	static const Vector2D gravity;
private:
	bool jumpReady;
	Sound jumpSound;
};