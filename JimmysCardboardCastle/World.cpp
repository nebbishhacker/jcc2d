#include "Game.h"
#include "World.h"

bool spriteSortingFunction(Sprite *s1, Sprite *s2)
{
	// return true if s1's layerID is less than s2's layerID
	return (s1->layerID < s2->layerID);
}

World::World()
{
	cameraX = 0;
	cameraY = 0;
	nextWorldDown = NULL;
}

World::~World()
{
	for (SpriteGroup::iterator it = spriteList.begin(); it != spriteList.end(); ++it)
		(*it)->kill();
	executeHitList();
}

void World::add(Sprite *s)
{
	spriteList.add(s);

	addToDrawList(s);
	addToAnimationList(s);
	addToUpdateList(s);
	s->setWorld(this);
	s->initialize();
}

void World::addToDrawList(Sprite *s)
{
	if(s)
	{
		/* push the sprite to the back of the list */
		this->drawList.add(s);
	}
}

void World::addToUpdateList(Sprite *s)
{
	if(s)
	{
		/* push the sprite to the back of the list */
		this->updateList.add(s);
	}
}

void World::addToAnimationList(Sprite *s)
{
	if(s)
	{
		/* push the sprite to the back of the list */
		this->animationList.add(s);
	}
}

void World::draw()
{
	drawList.sort(spriteSortingFunction);

	SpriteGroup::iterator it; 
	for(it = drawList.begin(); it != drawList.end();)
	{
		Sprite *s = (*it++);
		s->draw(cameraX, cameraY);
	}
}

void World::update()
{
	SpriteGroup::iterator it; 
	for(it=updateList.begin(); it != updateList.end();)
	{
		Sprite * s = *it++;
		s->update();
	}
	executeHitList();
}

void World::updateAnimation()
{
	SpriteGroup::iterator it; 
	for(it=updateList.begin(); it != updateList.end();)
	{
		Sprite * s = *it++;
		s->updateAnimation();
	}
}

void World::remove(Sprite * sprite)
{
	hitList.push_back(sprite);
}

void World::executeHitList()
{
	while (!hitList.empty()) {
		delete hitList.back();
		hitList.pop_back();
	}
}

void World::centerCamera(double x, double y)
{
	if (stateInfo) {
		cameraX = x - stateInfo->screenWidth / 2;
		cameraY = y - stateInfo->screenHeight / 2;
	}
}

void World::killNextWorldDown()
{
	World * temp = nextWorldDown;
	nextWorldDown = nextWorldDown->nextWorldDown;
	delete temp;
}

void World::replaceNextWorldDown(World * world)
{
	world->nextWorldDown = nextWorldDown->nextWorldDown;
	delete nextWorldDown;
	nextWorldDown = world;
}