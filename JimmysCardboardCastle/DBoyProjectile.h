#pragma once
#include "physicssprite.h"
class DBoy_proj : public PhysicsSprite
{
public:
	DBoy_proj(double x, double y, bool flip) : PhysicsSprite("images/spr_dboyproj.png")
	{
		setPosition(x, y);
		flipped = flip;
		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(64, 64);

		addSpriteAnimFrame(0, 0, 0); // first animation
		setCurrentAnimation(0);

		// PHYSICAL PROPERTIES //
		mass = 1;
		airDrag = 0.1;
		groundFriction = 0.45;
		//gravity.y = 3;
		// (airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(2, 10, 44, 35);

		setCenter(32, 32);
	};
	void initialize()
	{
		//velocity.y = 10;
		
	};
	void update()
	{
		if (!flipped)
		{
			velocity.x = 2;
		}
		else
		{
			velocity.x = -2;
		}

		//gravity.y -= 0.25;

		// Handles air drag //
		applyAirDrag();

		// Accounts for gravity //
		netForce += gravity * mass;

		// Figure out the net acceleration from forces //
		netAcceleration += netForce / mass;

		// Move the sprite, checking for collisions //
		Vector2D delta = velocity + netAcceleration * 0.5;

		// Move, stopping upon collision with ground. Set velocity to zero when colliding.
		if (moveCollideX(delta.x, &world->groups["player"]))
		{
			velocity.x *= -1;
			if (flipped)
				flipped = false;
			else
				flipped = true;
		}
		else if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
		if (moveCollideY(delta.y, &world->groups["ground"])) kill();

		// update velocity to reflect acceleration //
		velocity += netAcceleration;

		// reset netForce, netAcceleration, and possibly other things for the next timestep (so they can be modified externally, if need be)
		//resetPhysicsVars();
	}
};