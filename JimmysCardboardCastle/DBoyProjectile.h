#pragma once
#include "physicssprite.h"
class DBoy_proj : public PhysicsSprite
{
public:
	bool getDBoy;

	DBoy_proj(double x, double y, bool flip) : PhysicsSprite("images/spr_dboyproj.png")
	{
		setPosition(x, y);
		// Allows setting of where the box should go //
		flipped = flip;
		getDBoy = false;

		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(64, 64);

		addSpriteAnimFrame(0, 0, 0); // first animation
		setCurrentAnimation(0);

		// PHYSICAL PROPERTIES //
		mass = 1;
		airDrag = 0.1;
		groundFriction = 0.45;
		gravity.y = 3;
		// (airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(2, 10, 44, 35);

		setCenter(32, 32);
	};
	void initialize()
	{		
	};
	void update()
	{
		// Set the velocity //
		if (!flipped)
		{
			velocity.x = 10;
		}
		else
		{
			velocity.x = -10;
		}

		theta += 0.09;

		// Increase how much the gravity effects the projectile //
		gravity.y -= 0.25;

		// Handles air drag //
		applyAirDrag();

		// Accounts for gravity //
		netForce += gravity * mass;

		// Figure out the net acceleration from forces //
		netAcceleration += netForce / mass;

		// Move the sprite, checking for collisions //
		Vector2D delta = velocity + netAcceleration * 0.5;

		// Check if the box should collide with DBoy //
		if (getDBoy)
		{
			// If it should be then it will moveCollide with DBoy //
			if (moveCollideX(delta.x, &world->groups["dboy"]))
			{
				velocity.y = 10;
				gravity.y = 1.5;
				if (flipped)
					flipped = false;
				else
					flipped = true;
				Sprite * player = moveCollideX(delta.x, &world->groups["dboy"]);
				if (player) 
				{
					player->moveCollideX(delta.x*5, &world->groups["ground"]);
				}
				setCurrentAnimation(3);
				kill();
			}
			else
			{
				if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
				if (moveCollideY(delta.y, &world->groups["ground"])) kill();
			}
		}
		// TEMP //
		else if (moveCollideX(delta.x, &world->groups["player"]))
		{
			velocity.y = 10;
			gravity.y = 1.5;
			if (flipped)
				flipped = false;
			else
				flipped = true;
			getDBoy = true;
		}
		else
		{
			if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
			if (moveCollideY(delta.y, &world->groups["ground"])) kill();
		}

		// update velocity to reflect acceleration //
		velocity += netAcceleration;

		// reset netForce, netAcceleration, and possibly other things for the next timestep (so they can be modified externally, if need be)
		resetPhysicsVars();
	}
};