#include "Robert.h"
#include "Game.h"
#include "GameWorld.h"
#include "levelList.h"
#include "World.h"
#include "RobertProjectile.h"

#include <random>

Robert::Robert(double x, double y) : PhysicsSprite("images/spr_robert.png")
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

	addSpriteAnimRow(0, 0, 256, 128, 0, 1); // standing animation - 0
	setAnimationSpeed(0, 0.1);

	addSpriteAnimRow(1, 0, 384, 128, 0, 4); // walking animation - 1
	setAnimationSpeed(1, 0.25);

	addSpriteAnimRow(2, 0, 128, 128, 0, 5); // attacking animation - 2
	setAnimationSpeed(2, 0.25);
	setAnimationLoop(2, false);

	addSpriteAnimRow(3, 0, 0, 128, 0, 2); // hit animation - 3
	setAnimationSpeed(3, 0.1);
	setAnimationLoop(3, false);

	setCurrentAnimation(0);

	// PHYSICAL PROPERTIES //
	mass = 50;
	airDrag = 0.1;
	groundFriction = 0.75;
	// (airGroundFriction and gravity are left to defaults)

	hitbox = Hitbox(40, 0, 48, 117);
	setCenter(64, 58);

	health = 3;

	// BEHAVIORAL STATE VARIABLE(S) //
	walking = false;
	attacking = false;
	gotHit = false;
	thrown = false;
	willAttack = false;
}

void Robert::initialize() // use initialize for anything involving world (like groups)
{
	// adds this sprite to DBoy, so that the box can collide with it
	world->groups["dboy"].add(this);
}

void Robert::update()
{
	// Is the character on the ground?
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);

	// check if a member of 'ground' who IS NOT the player is beside me, and if so, turn away
	Sprite * s;
	if ((s = collide(&world->groups["ground"], 2, 0)) && !s->inGroup(&world->groups["player"])) flipped = true;
	if ((s = collide(&world->groups["ground"], -2, 0)) && !s->inGroup(&world->groups["player"])) flipped = false;

	// 1/200th of a chance each frame to:
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
	
	Sprite * projectile = collide(&world->groups["dboyscryptonite"],0,0);
	if (projectile)
	{
		health--;
		if (!flipped)
			velocity.x -= 10;
		else
			velocity.x += 10;

		if (!attacking)
			setCurrentAnimation(3);

		projectile->kill();
	}

	if (attacking)
	{
		if (animations[currentAnimation]->currentFrame == 5 && !thrown)
		{
			animations[currentAnimation]->nextFrame();
			thrown = true;

			// Create the box projectile
			Sprite * t;
			if (!flipped)
				t = new DBoy_proj(position.x+100, position.y+58, flipped);
			else
				t = new DBoy_proj(position.x-41, position.y+58, flipped);
			world->add(t);
		}
		else if (animations[currentAnimation]->currentFrame == 6)
		{
			setCurrentAnimation(0);
			attacking = false;
			thrown = false;
		}
	}

	if (walking) // If we are walking
	{
		if (flipped)
			contactVelocity.x += 2.5;
		else
			contactVelocity.x -= 2.5;
	}

	// Handles ground friction and acceleration due to movement //
	if (grounded) {
		applyGroundFriction();
	}
	
	if (health <= 0)
	{
		world->game->replacingCurrentWorld(levelList.constructNextLevel());
	}


	if (!willAttack)
	{
		Sprite * s = collide(&world->groups["player"]);
		if (s != NULL && static_cast<Player*>(s)->marbles == 3)
		{
			willAttack = true;
		}
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