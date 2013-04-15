#pragma once

#include "World.h"
#include "entities.h"

// sharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "sharedButtonCallbacks.h"

class CreditsScreen : public World
{
public:
	virtual void initialize()
	{
		add(new Background(0, 0, 800, 600, "images/dev/CreditsScreen.png", -100, 0.5, 0.25));

		// Exit sign button
		add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", killWorld));
	}
};