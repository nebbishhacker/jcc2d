#pragma once
#include "PhysicsSprite.h"
class Marble : public PhysicsSprite
{
public:
	int clor;
	Marble(double x, double y, int color) : PhysicsSprite("images/spr_marbles.png")
	{
		setPosition(x, y);

		// marble colours //
		// 0 - blue
		// 1 - red
		// 2 - green
		// 3 - dragon

		// ANIMATION SETUP //
		setNumberOfAnimations(5);
		setSpriteFrameSize(16, 16);

		addSpriteAnimRow(0, 0, 0, 16, 0, 5);
		setAnimationSpeed(0, 0.25);

		addSpriteAnimRow(1, 0, 16, 16, 0, 5);
		setAnimationSpeed(1, 0.25);

		addSpriteAnimRow(2, 0, 32, 16, 0, 5);
		setAnimationSpeed(2, 0.25);

		addSpriteAnimRow(3, 0, 48, 16, 0, 5);
		setAnimationSpeed(3, 0.25);

		setCurrentAnimation(color);

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