#include "TowerEnd.h"
#include "Game.h"
#include "Player.h"

#include <random>

TowerEnd::TowerEnd(double x, double y) : TextureSprite("images/TowerEnd.png")
{
	setPosition (x,y); 


	
	setNumberOfAnimations(1); 
	setSpriteFrameSize(256,2048); 

	addSpriteAnimRow(0,0,0, 0, 0 , 1); 
	setAnimationSpeed(0,0.25); 

	setCurrentAnimation(0); 

	setLayerID(-3);
}


void TowerEnd::update() // use initialize for anything involving world (like groups)
{
	// adds this sprite to ground, so that player can't move through it
	world->groups["ground"].add(this);
}
