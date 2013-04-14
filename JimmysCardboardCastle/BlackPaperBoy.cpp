#include "BlackPaperBoy.h"
#include "Game.h"
#include "PaperAirplane.h"

#include <random>

BlackPaperBoy::BlackPaperBoy(double x, double y) : PhysicsSprite("images/spr_blackpaperboy.png")
{
	setPosition(x, y);

	// animations:
	// 0 - standing
	// 1 - walking
	// 2 - attacking
	// 3 - get hit

	// ANIMATION SETUP //
	setNumberOfAnimations(3);
	setSpriteFrameSize(128,128);

	addSpriteAnimRow(0, 0, 0, 128, 0, 6); // standing animation - 0
	setAnimationSpeed(0, 0.1);

	addSpriteAnimRow(2, 0, 256, 128, 0, 7); // walking animation - 1
	setAnimationSpeed(2, 0.25);

	addSpriteAnimRow(1, 0, 128, 128, 0, 4); // attacking animation - 2
	setAnimationSpeed(1, 0.25);
	setAnimationLoop(1, false);

	//addSpriteAnimRow(3, 0, 0, 128, 0, 1); // hit animation - 3
	//setAnimationSpeed(3, 0.1);
	//setAnimationLoop(3, false);

	setCurrentAnimation(0);

	// PHYSICAL PROPERTIES //
	mass = 50;
	airDrag = 0.1;
	groundFriction = 0.75;
	// (airGroundFriction and gravity are left to defaults)

	hitbox = Hitbox(40, 0, 50, 117);
	setCenter(65, 58);

	health = 2; 
	
	// BEHAVIORAL STATE VARIABLE(S) //
	walking = false;
	attacking = false;
	gotHit = false;
}

void BlackPaperBoy::initialize() // use initialize for anything involving world (like groups)
{
	// adds this sprite to PBoy, so that the box can collide with it
	world->groups["blackPBoy"].add(this);
}

void BlackPaperBoy::update()
{
	// Is the character on the ground?
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);

	// check if a member of 'ground' who IS NOT the player is beside me, and if so, turn away
	Sprite * s;
	if ((s = collide(&world->groups["ground"], 2, 0)) && !s->inGroup(&world->groups["player"])) flipped = true;
	if ((s = collide(&world->groups["ground"], -2, 0)) && !s->inGroup(&world->groups["player"])) flipped = false;

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
	if (rand() % 200 == 0) // 1/100th chance of attacking
	{
		// Stops it from walking if it already is
		if (walking)
			walking = false;
		setCurrentAnimation(1);
		setFrame(0); // set animation to the start, as it doesn't loop

		// Create the box projectile
		Sprite * t;
		if (!flipped)
			t = new PaperAirplane_proj(position.x+65, position.y+58, flipped);
		else
			t = new PaperAirplane_proj(position.x-65, position.y+58, flipped);
		world->add(t);
	}

	if (walking) // If we are walking
	{
		if (flipped)
			contactVelocity.x += 3.5;
		else
			contactVelocity.x -= 3.5;
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

	// Move, stopping upon collision with ground. Set velocity to zero when colliding.
	if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
	if (moveCollideY(delta.y, &world->groups["ground"])) velocity.y = 0;

	// update velocity to reflect acceleration //
	velocity += netAcceleration;

	// reset netForce, netAcceleration, and possibly other things for the next timestep (so they can be modified externally, if need be)
	resetPhysicsVars();
}