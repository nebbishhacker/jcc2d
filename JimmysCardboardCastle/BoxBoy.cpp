#include "BoxBoy.h"
#include "Game.h"

#include <random>

BoxBoy::BoxBoy(double x, double y) : PhysicsSprite("images/spr_enemy2.png")
{
	// animations:
	// 0 - hiding
	// 1 - lift box
	// 2 - crawl left
	setNumberOfAnimations(3);
	setSpriteFrameSize(128,128);

	addSpriteAnimFrame(0, 0, 0);

	addSpriteAnimRow(1, 0, 0, 128, 0, 5);
	setAnimationSpeed(1, 0.25);
	setAnimationLoop(1, false);

	addSpriteAnimRow(2, 0, 128, 128, 0, 4);
	setAnimationSpeed(2, 0.1);

	setCurrentAnimation(2);

	setPosition(x, y);

	mass = 50;
	airDrag = 0.1;
	groundFriction = 0.75;

	hitbox = Hitbox(17, 1, 94, 59);

	walking = true;
}

void BoxBoy::initialize()
{
	world->groups["ground"].add(this);
}

void BoxBoy::update()
{
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL); // Is the character on the ground?

	if (collide(&world->groups["player"], 0, 2))
	{
		walking = false;
		setCurrentAnimation(0);
	}
	else
	{
		Sprite * s;
		if ((s = collide(&world->groups["ground"], -2, 0)) && !s->inGroup(&world->groups["player"])) flipped = true;
		if ((s = collide(&world->groups["ground"], 2, 0)) && !s->inGroup(&world->groups["player"])) flipped = false;
	
		if (rand() % 200 == 0) {
			if (walking) {
				walking = false;
				setCurrentAnimation(0);
			}
			else {
				walking = true;
				setCurrentAnimation(2);
			}
		}
		if (!walking && rand() % 200 == 0) {
			setCurrentAnimation(1);
			setFrame(0);
		}
	}

	if (walking)
	{
		if (!flipped) contactVelocity.x += 1.5;
		else contactVelocity.x -= 1.5;
	}

	// Handles ground friction and acceleration due to foot movement //
	if (grounded) {
		applyGroundFriction();
	}
	//if (!grounded) {
	//	// There is still ground friction while airborn, but to a different extent. This is a game. It is not real.
	//	applyAirGroundFriction();
	//	if (velocity.y >= 0) setCurrentAnimation(2);
	//	else setCurrentAnimation(3);
	//}
	// Handles air drag //
	applyAirDrag();

	netForce += gravity * mass;

	// Figure out the net acceleration from forces //
	netAcceleration += netForce / mass;

	// Move the sprite, checking for collisions //
	Vector2D delta = velocity + netAcceleration * 0.5;

	Sprite * player;
	if (player = moveCollideX(delta.x, &world->groups["player"])) player->moveCollideX(delta.x, &world->groups["ground"]);

	if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
	if (moveCollideY(delta.y, &world->groups["ground"])) velocity.y = 0;

	// update velocity to reflect acceleration //
	velocity += netAcceleration;

	// reset netForce and netAcceleration for the next timestep (so they can be modified externally, if need be)
	resetPhysicsVars();
}