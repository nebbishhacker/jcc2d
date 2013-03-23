#pragma once

#include "World.h"
#include "entities.h"

class HowToPlay : public World
{
public:
	virtual void initialize()
	{
			add(new Background(0, 0, 800, 600, "images/dev/HowToPlay.png", -100, 0.5, 0.25));
			add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", killWorld));
	}
	
};

