#include "CollTestBox.h"
#include "Game.h"

CollTestBox::CollTestBox(double x, double y) : TextureSprite("images/dev/colltestbox.png")
{
	setNumberOfAnimations(2);
	setSpriteFrameSize(600,50);
	addSpriteAnimFrame(0,0,0);
	addSpriteAnimFrame(1,200,0);
	setCurrentAnimation(0);
	setPosition(x, y);
	setLayerID(1);

	hitbox = Hitbox(0, 0, 600, 50);
}

void CollTestBox::initialize()
{
	world->groups["ground"].add(this);
}

void CollTestBox::update()
{
	setCurrentAnimation(0);
	Sprite * player = collide(&world->groups["player"]);
	if (player != NULL) {
		//std::cout << player->positionX << ", " << player->positionY << "\n";
		//player->kill();
		//this->kill();
		setCurrentAnimation(1);
	}
	//positionX -= 1;
}