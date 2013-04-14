#pragma once
#include "physicssprite.h"
class bubble : public PhysicsSprite
{
public:
	bubble(double x, double y, int bubbleNum) : PhysicsSprite("images/spr_nannyBubble1.png")
	{
		setPosition(x, y);

		// ANIMATION SETUP //
		setNumberOfAnimations(1);
		setSpriteFrameSize(512,512);

		addSpriteAnimFrame(0, 0, 0); // first animation
		setAnimationSpeed(0, 0);

		setCurrentAnimation(bubbleNum);
	};
	void initialize()
	{
	};
	void update()
	{
	};

private:
	bool talking;
};