#pragma once
#include "physicssprite.h"
class Nanny : public PhysicsSprite
{
public:
	Nanny(double x, double y) : PhysicsSprite("images/spr_nanny.png")
	{
		setPosition(x, y);

		// animations:
		// 0 - standing
		// 1 - walking
		// 2 - attacking
		// 3 - get hit

		// ANIMATION SETUP //
		setNumberOfAnimations(3);
		setSpriteFrameSize(128,256);

		addSpriteAnimFrame(0, 4*128, 0); // first animation
		setAnimationSpeed(0, 0);

		addSpriteAnimRow(1, 0, 0, 128, 0, 2); // walking animation - 1
		setAnimationSpeed(1, 0.1);

		addSpriteAnimRow(2, 256, 0, 128, 0, 2); // attacking animation - 2
		setAnimationSpeed(2, 0.1);

		setCurrentAnimation(0);

		// PHYSICAL PROPERTIES //
		mass = 50;
		airDrag = 0.1;
		groundFriction = 0.75;
		// (airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(40, 0, 48, 117);
		setCenter(64, 58);

		talking = false;
	};
	void initialize()
	{
		
	};
	void update()
	{
		// Is the character on the ground?
		bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);

		if (collide(&world->groups["player"],0,0))
		{
			if (!talking)
			{
				if (rand() % 2 == 0)
					setCurrentAnimation(1);
				else
					setCurrentAnimation(2);
			}

			talking = true;
		}
		else
		{
			talking = false;
			setCurrentAnimation(0);
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
	};

private:
	bool talking;
};