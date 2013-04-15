#pragma once

#include "World.h"
#include "Game.h"
#include "GameWorld.h"
#include "levelList.h"

// Callback for killing the current world (thus dropping to the one on the stack below it)
void killWorld(World* world);

// Callback for killing the current world, as well as the one below it (thus dropping to the one on the stack below that)
// Useful for "are you sure?" pop-ups
void doubleKillWorld(World* world);

// Templated callback, specifically for starting a new world. Things like this should be good if you need a lot of similar callbacks.
template<class TWorld>
void startWorld(World * currentWorld)
{
	currentWorld->game->setNewWorld(new TWorld());
}

template<int num>
void startLevel(World * currentWorld)
{
	currentWorld->game->setNewWorld(levelList.constructLevel(num));
}

// Templated callback, specifically for switching to a different world. Things like this should be good if you need a lot of similar callbacks.
template<class TWorld>
void switchWorld(World * currentWorld)
{
	currentWorld->game->replacingCurrentWorld(new TWorld());
}

template<int num>
void switchLevel(World * currentWorld)
{
	currentWorld->game->replacingCurrentWorld(levelList.constructLevel(num));
}

void switchNextLevel(World * currentWorld);

void startCurrentLevel(World * currentWorld);
