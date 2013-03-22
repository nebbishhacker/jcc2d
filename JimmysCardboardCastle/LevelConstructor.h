#pragma once

#include "World.h"
#include "LevelLoader.h"
#include "TileSheet.h"
#include "entities.h"

void ConstructLevel(LevelData levelData, World * world)
{
	for (EntityList::iterator it = levelData.entities.begin(); it != levelData.entities.end(); ++it)
	{
		EntityInfo &info = *it;
		Sprite * t = NULL;
		if (info.type == "player") t = new Player(info.xPos, info.yPos);
		else if (info.type == "background") t = new Background(info.xPos, info.yPos, info.frameSizeX, info.frameSizeY, info.imagePath);
		if (t != NULL)
		{
			if (info.layerID != INVALID_INT) t->layerID = info.layerID;
			if (info.scrollFactorX != INVALID_INT) t->scrollFactorX = info.scrollFactorX;
			if (info.scrollFactorY != INVALID_INT) t->scrollFactorY = info.scrollFactorY;
			world->add(t);
		}
	}

	for (std::vector<TileMap>::iterator it = levelData.tileMaps.begin(); it != levelData.tileMaps.end(); ++it)
	{
		TileMap &tileMap = *it;

		int tileWidth = tileMap.tileWidth;
		int tileHeight = tileMap.tileWidth;

		std::shared_ptr<TileSheet> tileSheet(new TileSheet(tileWidth, tileHeight, 2, 2, tileMap.tileSheetPath));

		int y = 0;
		for (std::vector<MapRow>::iterator it = tileMap.data.begin(); it != tileMap.data.end(); ++it)
		{
			int x = 0;
			MapRow &mapRow = *it;
			for (std::vector<TileInfo>::iterator it = mapRow.begin(); it != mapRow.end(); ++it)
			{
				TileInfo &info = *it;
				if (info.exists) {
					Tile * tempTile = new Tile(x * tileWidth, y * tileHeight, info.c + 2 * info.r, tileSheet);
					world->groups["ground"].add(tempTile);
					world->add(tempTile);
				}
				++x;
			}
			++y;
		}
	}
}