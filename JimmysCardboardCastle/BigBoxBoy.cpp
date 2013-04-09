#include "BigBoxBoy.h"
#include "Game.h"
#include "Player.h"

#include <random>

BigBoxBoy::BigBoxBoy(double x, double y) : PhysicsSprite("images/spr_BBBoy.png")
{
	setPosition(x, y);
	active = false;

	// animations:
	// 0 - standing
	// 1 - charging

	// ANIMATION SETUP //
	setNumberOfAnimations(2);
	setSpriteFrameSize(256,256);

	addSpriteAnimFrame(0, 0, 256); // first animation

	addSpriteAnimRow(1, 0, 0, 256, 0, 4); // second animation
	setAnimationSpeed(1, 0.5);

	setCurrentAnimation(0);

	// PHYSICAL PROPERTIES //
	mass = 150;
	airDrag = 0.1;
	groundFriction = 0.75;
	// (airGroundFriction and gravity are left to defaults)

	hitbox = Hitbox(15, 0, 226, 122);

	setCenter(128, 71);

	// BEHAVIORAL STATE VARIABLE(S) //
	walking = false;
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

	if (active)
	{
		// check if a member of 'ground' who IS NOT the player is beside me, and if so, turn away
		Sprite * s;
		if ((s = collide(&world->groups["ground"], -5, 0)) && !s->inGroup(&world->groups["player"]) && !flipped)
		{
			flipped = true;
			walking = false;
			setCurrentAnimation(0);
		}
		if ((s = collide(&world->groups["ground"], 5, 0)) && !s->inGroup(&world->groups["player"]) && flipped)
		{
			flipped = false;
			walking = false;
			setCurrentAnimation(0);
		}

		// 1/200th of a chance each frame to:
		if (!walking)
			if (rand() % 1 == 0) { {
				walking = true; // stop walking
				setCurrentAnimation(1); // and hide animation
			}
		}
	}

	if (walking) // If we are walking:
	{
		if (!flipped)	// and facing left (the image faces right)
			contactVelocity.x += 5; // move feet right (thus pushing self left);
		else			// and facing right
			contactVelocity.x -= 5; // move feet left (thus pushing self right);
	}

	if (!active)
	{
		if (collide(&world->groups["player"],2,0))
			active = true;
		else if (collide(&world->groups["player"],-2,0))
			active = true;
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
		static_cast<Player*>(player)->damage(1);
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