#include "Chest.h"
#include "Game.h"
#include "GameWorld.h"
#include "levelList.h"
#include "World.h"
#include "Key.h"

#include <random>

Chest::Chest(double x, double y) : PhysicsSprite("images/spr_chest.png")
{
	setPosition(x,y); 

	//animations:
	// 0 - open 
	// 1 - locked
	// 2 - opening

	// ANIMATION SETUP //
	
		setNumberOfAnimations(3);
		setSpriteFrameSize(64, 64);

		//Chest Opening
		addSpriteAnimRow(2, 0, 0, 64, 0, 7);
		setAnimationSpeed(0, 0.25);
		
		//Chest Locked
		addSpriteAnimRow(0, 0, 0, 64, 0, 2); 
		setAnimationSpeed(0, 0.25); 

		//Chest Opened
		addSpriteAnimRow(1, 0, 0, 64, 0, 1); 
		setAnimationSpeed(0, 0.25);

		setCurrentAnimation(0); 

		// PHYSICAL PROPERTIES //
		mass = 1; 

		//Behavioural State
		itemObtained=false; 
		locked=false; 
		opening= false; 
}
void Chest::initialize()
{

}
void Chest::update() // use initialize for anything involving world (like groups)
{
	// Is the character on the ground?
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);

	if(opening)
	{

		setCurrentAnimation(2); 
		opening = true; 
	}
	if (!opening)
	{
		Sprite * s = collide(&world->groups["player"]); 
		if (s != NULL && static_cast<Player*>(s)->key == 1)
		{
			opening = true; 
		}
	if(itemObtained)
	{
		setCurrentAnimation(1); 
		itemObtained = true; 
	}
	}

}
	
