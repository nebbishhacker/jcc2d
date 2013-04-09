#pragma once
#include "PhysicsSprite.h"
class Marble : public PhysicsSprite
{
public:
	Marble(double x, double y, int color) : PhysicsSprite("images/spr_BMarble.png")
	{
		setPosition(x, y);

		// animations, even though there's only one.
		// 0 - sparkling cookie

		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(16, 16);

		addSpriteAnimRow(0, 0, 0, 16, 0, 5); // first, and only animation
		setAnimationSpeed(0, 0.25);

		setCurrentAnimation(0);

		// PHYSICAL PROPERTIES //
		mass = 1;
		// (airDrag, groundFriction, airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(0, 0, 16, 16);
	};
	//void initialize();
	void update()
	{
		if (collide(&world->groups["player"]))
			this->kill();
	};
	
};