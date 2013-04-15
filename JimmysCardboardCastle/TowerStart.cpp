#include "TowerStart.h"
#include "Game.h"
#include "Player.h"

#include <random>

TowerStart::TowerStart(double x, double y) : TextureSprite("images/TowerStart.png")
{
	setPosition (x,y); 


	
	setNumberOfAnimations(1); 
	setSpriteFrameSize(256,1024); 

	addSpriteAnimRow(0,0,0, 0, 0 , 1); 
	setAnimationSpeed(0,0.25); 

	setCurrentAnimation(0); 

	setLayerID(-3);

}


void TowerStart::update() // use initialize for anything involving world (like groups)
{
	// adds this sprite to ground, so that player can't move through it
	world->groups["ground"].add(this);
}
