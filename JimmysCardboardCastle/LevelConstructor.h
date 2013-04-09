#pragma once

#include "World.h"
#include "levelLoader.h"
#include "TileSheet.h"
#include "entities.h"

void ConstructLevel(LevelData &levelData, World * world, bool storeReferences = false);