#pragma once

#include "GameWorld.h"

struct Level1 : GameWorld
{
	Level1() : GameWorld("levels/testLevel.txt") {}
};