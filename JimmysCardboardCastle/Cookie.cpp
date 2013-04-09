#include "Cookie.h"
#include "Game.h"

#include <random>

Cookie::Cookie(double x, double y) : PhysicsSprite("images/spr_cookiescore.png")
{
	setPosition(x, y);

	// animations, even though there's only one.
	// 0 - sparkling cookie

	// ANIMATION SETUP //
	setNumberOfAnimations(1);
	setSpriteFrameSize(32, 32);

	addSpriteAnimRow(0, 0, 0, 32, 0, 7); // first, and only animation
	setAnimationSpeed(0, 0.25);

	setCurrentAnimation(0);

	// PHYSICAL PROPERTIES //
	mass = 0.0330693; // yes, I actually found out the weight of an average chocolate chip cookie in pounds
	// (airDrag, groundFriction, airGroundFriction and gravity are left to defaults)
	// Another waste of time

	hitbox = Hitbox(0, 0, 32, 32);
}

/*void Cookie::initialize();
{
Left out because the cookie doesn't currently need to use the "ground" group.
}*/

void Cookie::update()
{
	// Accounts for gravity //
	netForce += gravity * mass;

	// Figure out the net acceleration from forces //
	netAcceleration += netForce / mass;

	// Move the sprite, checking for collisions //
	Vector2D delta = velocity + netAcceleration * 0.5;

	// Move, stopping upon collision with ground. Set velocity to zero when colliding.
	if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
	if (moveCollideY(delta.y, &world->groups["ground"])) velocity.y = 0;

	// update velocity to reflect acceleration //
	velocity += netAcceleration;

	// reset netForce, netAcceleration, and possibly other things for the next timestep (so they can be modified externally, if need be)
	resetPhysicsVars();

	if (collide(&world->groups["player"]))
		this->kill();
}