#pragma once

#include "World.h"
#include "Game.h"

// Callback for killing the current world (thus dropping to the one on the stack below it)
static void killWorld(World* world) {
	world->game->killCurrentWorld();
}

// Templated callback, specifically for starting a new world. Things like this should be good if you need a lot of similar callbacks.
template<class TWorld>
void startWorld(World * currentWorld)
{
	currentWorld->game->setNewWorld(new TWorld());
}