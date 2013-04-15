#pragma once
#include "physicssprite.h"
class healthMilk : public TextureSprite
{
public:
	healthMilk() : TextureSprite("images/spr_milk.png")
	{
		setNumberOfAnimations(1);
		setSpriteFrameSize(64,64);

		addSpriteAnimRow(0, 0, 0, 64, 0, 3); // second animation
		setAnimationSpeed(0, 0);

		setCurrentAnimation(0);

		setScrollFactor(0, 0);
	};
	void initialize()
	{
		layerID = 100;
	};
	void update()
	{
	};
};