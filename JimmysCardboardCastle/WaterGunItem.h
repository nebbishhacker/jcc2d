#pragma once
#include "PhysicsSprite.h"
#include "Player.h"
class WaterGunItem : public PhysicsSprite
{
public:
	WaterGunItem(double x, double y) : PhysicsSprite("images/spr_WaterGun.png")
	{
		setPosition(x, y);

		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(64, 32);

		addSpriteAnimRow(0, 0, 0, 64, 0, 5);
		setAnimationSpeed(0, 0.25);

		// PHYSICAL PROPERTIES //
		mass = 1;
		// (airDrag, groundFriction, airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(0, 0, 64, 64);
	};
	void update()
	{
		Sprite * s = collide(&world->groups["player"]);
		if (s != NULL)
		{
			static_cast<Player*>(s)->hasWaterGun = true;
			this->kill();
		}
	};
	
};