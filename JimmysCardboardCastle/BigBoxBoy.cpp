#include "BigBoxBoy.h"
#include "Game.h"

#include <random>

BigBoxBoy::BigBoxBoy(double x, double y) : PhysicsSprite("images/spr_BBBoy.png")
{
	setPosition(x, y);

	// animations:
	// 0 - standing
	// 1 - charging

	// ANIMATION SETUP //
	setNumberOfAnimations(2);
	setSpriteFrameSize(256,256);

	addSpriteAnimFrame(0, 0, 256); // first animation

	addSpriteAnimRow(1, 0, 0, 256, 0, 4); // second animation
	setAnimationSpeed(1, 0.5);
	setAnimationLoop(1, false);

	setCurrentAnimation(2);

	// PHYSICAL PROPERTIES //
	mass = 150;
	airDrag = 0.1;
	groundFriction = 0.75;
	// (airGroundFriction and gravity are left to defaults)

	hitbox = Hitbox(15, 0, 231, 143);

	setCenter(108, 71);

	// BEHAVIORAL STATE VARIABLE(S) //
	walking = true;
}

void BigBoxBoy::initialize() // use initialize for anything involving world (like groups)
{
	// adds this sprite to ground, so that player can't move through it
	world->groups["ground"].add(this);
}

void BigBoxBoy::update()
{
	// Is the character on the ground?
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);

	if (collide(&world->groups["player"], 0, 2)) // If the player is on top of me,
	{
		//walking = false; // stop
		//setCurrentAnimation(0); // and hide.
	}
	else // If not:
	{
		// check if a member of 'ground' who IS NOT the player is beside me, and if so, turn away
		Sprite * s;
		if ((s = collide(&world->groups["ground"], -2, 0)) && !s->inGroup(&world->groups["player"])) flipped = true;
		if ((s = collide(&world->groups["ground"], 2, 0)) && !s->inGroup(&world->groups["player"])) flipped = false;

		// 1/200th of a chance each frame to:
		if (rand() % 200 == 0) {
			if (walking) {
				walking = false; // stop walking
				setCurrentAnimation(0); // and hide animation
			}
			else {
				walking = true; // or start walking
				setCurrentAnimation(2); // and crawl animation
			}
		}
		if (!walking && rand() % 200 == 0) // If standing still, 1/200th chance of
		{
			// sneaking a peak at the world
			setCurrentAnimation(1);
			setFrame(0); // set animation to the start, as it doesn't loop
		}
	}

	if (walking) // If we are walking:
	{
		if (!flipped)	// and facing left (the image faces right)
			contactVelocity.x += 1.5; // move feet right (thus pushing self left);
		else			// and facing right
			contactVelocity.x -= 1.5; // move feet left (thus pushing self right);
	}

	// Handles ground friction and acceleration due to movement //
	if (grounded) {
		applyGroundFriction();
	}

	// Handles air drag //
	applyAirDrag();

	// Accounts for gravity //
	netForce += gravity * mass;

	// Figure out the net acceleration from forces //
	netAcceleration += netForce / mass;

	// Move the sprite, checking for collisions //
	Vector2D delta = velocity + netAcceleration * 0.5;

	// Push the player if moving into him
	Sprite * player = moveCollideX(delta.x, &world->groups["player"]);
	if (player) {
		double oldPPosX = player->position.x;
		player->moveCollideX(delta.x, &world->groups["ground"]);
		if (oldPPosX == player->position.x && rand() % 200 == 0) flipped = !flipped;
	}

	// Move, stopping upon collision with ground. Set velocity to zero when colliding.
	if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
	if (moveCollideY(delta.y, &world->groups["ground"])) velocity.y = 0;

	// update velocity to reflect acceleration //
	velocity += netAcceleration;

	// reset netForce, netAcceleration, and possibly other things for the next timestep (so they can be modified externally, if need be)
	resetPhysicsVars();
}