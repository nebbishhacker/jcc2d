#pragma once

#include "World.h"

class OverlayWorld : public World
{
public:
	virtual void draw()
	{
		if (nextWorldDown) nextWorldDown->draw();
		World::draw();
	}
};