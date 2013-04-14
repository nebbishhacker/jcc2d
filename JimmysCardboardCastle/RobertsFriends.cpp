#include "RobFriend.h"
#include "Game.h"
#include "RobbyFriendsProjectile.h"
#include "GameWorld.h"
#include "levelList.h"
#include "World.h"


#include <random>
RobertsFriends::RobertsFriends(double x, double y) : PhysicsSprite("images/spr_robertsfriend.png")
{
	setPosition(x, y);

	// animations:
	// 0 - standing
	// 1 - walking
	// 2 - attacking
	// 3 - get hit

	// ANIMATION SETUP //
	setNumberOfAnimations(4);
	setSpriteFrameSize(128,128);

	addSpriteAnimRow(0, 0, 128, 128, 0, 1); // standing animation - 0
	setAnimationSpeed(0, 0.1);

	addSpriteAnimRow(1, 0, 128, 128, 0, 4); // walking animation - 1
	setAnimationSpeed(1, 0.25);

	addSpriteAnimRow(2, 0, 256, 128, 0, 6); // attacking animation - 2
	setAnimationSpeed(2, 0.25);
	setAnimationLoop(2, false);

	addSpriteAnimRow(3, 0, 0, 128, 0, 3); // hit animation - 3
	setAnimationSpeed(3, 0.1);
	setAnimationLoop(3, false);

	setCurrentAnimation(0);


	// PHYSICAL PROPERTIES //
	mass = 50;
	airDrag = 0.1;
	groundFriction = 0.75;
	// (airGroundFriction and gravity are left to defaults)

	hitbox = Hitbox(40, 0, 50, 117);
	setCenter(5 , 58);

	// BEHAVIORAL STATE VARIABLE(S) //
	walking = true;
}

void RobertsFriends::initialize() // use initialize for anything involving world (like groups)
{
	// adds this sprite to ground, so that player can't move through it
	world->groups["ground"].add(this);
}

void RobertsFriends::update()
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
		// check if a member of 'ground' who IS NOT thje player is beside me, and if so, turn away
		Sprite * s;
		if ((s = collide(&world->groups["ground"], 2, 0)) && !s->inGroup(&world->groups["player"])) flipped = true;
		if ((s = collide(&world->groups["ground"], -2, 0)) && !s->inGroup(&world->groups["player"])) flipped = false;
		if (!attacking)
	{
		walking = true;
		setCurrentAnimation(1);
		if (rand() % 200 == 0) {
			if (walking) {
				if (!flipped)
					flipped = true;
				else
					flipped = false;
			}
		}
		if (willAttack)
		{
			if (rand() % 100 == 0) // 1/100th chance of attacking
			{
				// Stops it from walking if it already is
				if (walking)
					walking = false;
				setCurrentAnimation(2);
				setFrame(0); // set animation to the start, as it doesn't loop
				attacking = true;
			}
		}
	}
		// 1/200th of a chance each frame to:
		if (rand() % 200 == 0) {
			if (walking) {
				walking = false; // stop walking
				setCurrentAnimation(1); // and hide animation
			}
			else {
				walking = true; // or start walking
				setCurrentAnimation(0); // and crawl animation
			}
		}
		if (!walking && rand() % 200 == 0) // If standing still, 1/200th chance of
		{
			// sneaking a peak at the world
			setCurrentAnimation(2);
			setFrame(0); // set animation to the start, as it doesn't loop
		}
	}

	if (walking) // If we are walking:
	{
		if (flipped)	// and facing left (the image faces right)
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