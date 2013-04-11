#include "Fan.h"
#include "Game.h"
#include "Player.h"

#include <random>

Fan::Fan(double x, double y) : TextureSprite("images/spr_fan.png")
{
	setPosition (x,y); 


	
	setNumberOfAnimations(1); 
	setSpriteFrameSize(64,64); 

	addSpriteAnimRow(0,0,0, 64, 0 , 4); 
	setAnimationSpeed(0,0.25); 

	setCurrentAnimation(0); 

}


	void Fan::update() // use initialize for anything involving world (like groups)
{
	// adds this sprite to ground, so that player can't move through it
	world->groups["ground"].add(this);
}
