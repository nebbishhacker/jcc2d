#pragma once
#include "PhysicsSprite.h"
#include "Player.h"
class Key : public PhysicsSprite
{
public:
	Key(double x, double y) : PhysicsSprite("images/spr_key.png")
	{
		setPosition(x, y);

		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(32, 32);

		addSpriteAnimRow(0, 0, 0, 32, 0, 5);
		setAnimationSpeed(0, 0.25);
		
		
		// PHYSICAL PROPERTIES //
		mass = 1;
		// (airDrag, groundFriction, airGroundFriction and gravity are left to defaults)

		hitbox = Hitbox(0, 0, 16, 16);
	};
	//void initialize();
	void update()
	{
		Sprite * s = collide(&world->groups["player"]);
		if (s != NULL)
		{
			static_cast<Player*>(s)->key++;
			this->kill();
		}
	};
	
};