#include "SharedButtonCallbacks.h"

// Callback for killing the current world (thus dropping to the one on the stack below it)
void killWorld(World* world) {
	world->game->killCurrentWorld();
}

// Callback for killing the current world, as well as the one below it (thus dropping to the one on the stack below that)
// Useful for "are you sure?" pop-ups
void doubleKillWorld(World* world) {
	world->killNextWorldDown();
	world->game->killCurrentWorld();
}

void switchNextLevel(World * currentWorld)
{
	World * g = levelList.constructNextLevel();
	currentWorld->game->replacingCurrentWorld(g);
}


void startCurrentLevel(World * currentWorld)
{
	World * g = levelList.constructCurrentLevel();
	currentWorld->game->setNewWorld(g);
}