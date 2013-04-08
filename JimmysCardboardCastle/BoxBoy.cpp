#include "BoxBoy.h"
#include "Game.h"

#include <random>

BoxBoy::BoxBoy(double x, double y) : PhysicsSprite("images/spr_enemy2.png")
{
	setPosition(x, y);

	// animations:
	// 0 - hiding
	// 1 - lift box
	// 2 - crawl left

	// ANIMATION SETUP //
	setNumberOfAnimations(3);
	setSpriteFrameSize(128,128);

	addSpriteAnimFrame(0, 0, 0); // first animation

	addSpriteAnimRow(1, 0, 0, 128, 0, 5); // second animation
	setAnimationSpeed(1, 0.25);
	setAnimationLoop(1, false);

	addSpriteAnimRow(2, 0, 128, 128, 0, 4); // third animation
	setAnimationSpeed(2, 0.1);

	setCurrentAnimation(2);

	// PHYSICAL PROPERTIES //
	mass = 50;
	airDrag = 0.1;
	groundFriction = 0.75;
	// (airGroundFriction and gravity are left to defaults)

	hitbox = Hitbox(7, 1, 94, 59);

	setCenter(54, 30);

	// BEHAVIORAL STATE VARIABLE(S) //
	walking = true;
}

void BoxBoy::initialize() // use initialize for anything involving world (like groups)
{
	// adds this sprite to ground, so that player can't move through it
	world->groups["ground"].add(this);
}

void BoxBoy::update()
{
	// Is the character on the ground?
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);

	if (collide(&world->groups["player"], 0, 2)) // If the player is on top of me,
	{
		walking = false; // stop
		setCurrentAnimation(0); // and hide.
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