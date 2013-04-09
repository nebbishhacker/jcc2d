#pragma once

#include "World.h"
#include "levelLoader.h"
#include "TileSheet.h"
#include "entities.h"

void ConstructLevel(LevelData &levelData, World * world, bool storeReferences = false)
{
	for (EntityList::iterator it = levelData.entities.begin(); it != levelData.entities.end(); ++it)
	{
		EntityInfo &info = *it;
		Sprite * t = NULL;
		if (info.type == "player") {
			Player * p = new Player(info.xPos, info.yPos);
			p->hasBoots = info.moonBoots != 0;
			t = p;
		}
		else if (info.type == "boxboy") t = new BoxBoy(info.xPos, info.yPos);
		else if (info.type == "boxbot") t = new BoxBot(info.xPos, info.yPos);
		else if (info.type == "tracks") t = new Tracks(info.xPos, info.yPos);
		else if (info.type == "dragonboy") t = new DragonBoy(info.xPos, info.yPos);
		else if (info.type == "robertsfriends") t = new RobertsFriends(info.xPos, info.yPos);
		else if (info.type == "cookie") t = new Cookie(info.xPos, info.yPos);
		else if (info.type == "bmarble") t = new Marble(info.xPos, info.yPos, 0);
		else if (info.type == "rmarble") t = new Marble(info.xPos, info.yPos, 1);
		else if (info.type == "gmarble") t = new Marble(info.xPos, info.yPos, 2);
		else if (info.type == "dmarble") t = new Marble(info.xPos, info.yPos, 3);
		else if (info.type == "background") t = new Background(info.xPos, info.yPos, info.frameSizeX, info.frameSizeY, info.imagePath);
		if (t != NULL)
		{
			if (info.layerID != INVALID_DOUBLE) t->layerID = info.layerID;
			if (info.scrollFactorX != INVALID_DOUBLE) t->scrollFactorX = info.scrollFactorX;
			if (info.scrollFactorY != INVALID_DOUBLE) t->scrollFactorY = info.scrollFactorY;
			world->add(t);
			info.entity = t;
		}
	}

	for (std::vector<TileMap>::iterator it = levelData.tileMaps.begin(); it != levelData.tileMaps.end(); ++it)
	{
		TileMap &tileMap = (*it);

		int tileWidth = tileMap.tileWidth;
		int tileHeight = tileMap.tileHeight;

		std::shared_ptr<TileSheet> tileSheet(new TileSheet(tileWidth, tileHeight, tileMap.sheetWidth, tileMap.sheetHeight, tileMap.tileSheetPath));
		if (storeReferences) tileMap.tileSheetPointer = tileSheet;

		int y = 0;
		for (std::vector<MapRow>::iterator it = tileMap.data.begin(); it != tileMap.data.end(); ++it)
		{
			int x = 0;
			MapRow &mapRow = *it;
			for (std::vector<TileInfo>::iterator it = mapRow.begin(); it != mapRow.end(); ++it)
			{
				TileInfo &info = *it;
				if (info.exists) {
					Tile * t = new Tile(x * tileWidth, y * tileHeight, info.r * tileMap.sheetWidth + info.c, tileSheet);
					world->groups["ground"].add(t);
					world->add(t);
				if (storeReferences) info.entity = t;
				}
				++x;
			}
			++y;
		}
		tileMap.autoSize();
	}
}