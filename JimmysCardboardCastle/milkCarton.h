#pragma once
#include "PhysicsSprite.h"
class milkCarton : public PhysicsSprite
{
public:
	milkCarton(double x, double y) : PhysicsSprite("images/spr_milkCarton.png")
	{
		setPosition(x, y);

		// marble colours //
		// 0 - blue
		// 1 - red
		// 2 - green
		// 3 - dragon

		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(64, 64);

		addSpriteAnimRow(0, 0, 0, 64, 0, 7);
		setAnimationSpeed(0, 0.25);

		// PHYSICAL PROPERTIES //
		mass = 1;
		// (airDrag, groundFriction, airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(0, 0, 64, 64);

		setCenter(32, 32);
	};
	void update()
	{
		Sprite * s = collide(&world->groups["player"]);
		if (s != NULL)
		{
			static_cast<Player*>(s)->heal(2.5);
			this->kill();
		}
	};
	
};