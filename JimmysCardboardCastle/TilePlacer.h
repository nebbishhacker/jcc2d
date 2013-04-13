#pragma once
#include "Sprite.h"
#include "TileSheet.h"
#include "levelLoader.h"

struct TileCoord
{
	int c;
	int r;
};

class TilePlacer: public Sprite
{
public:
	TilePlacer(TileMap * tileMapData)
	{
		setPosition(0, 0);
		this->tileMapData = tileMapData;
		tileSheet = tileMapData->tileSheetPointer;
		hitbox = Hitbox(0, 0, tileSheet->tileWidth, tileSheet->tileHeight);
		layerID = 500;

		tileType.c = 0;
		tileType.r = 0;
	}
	void draw(Vector2D camera);
	void update();
	
private:
	int levelData;
	TileMap * tileMapData;
	std::shared_ptr<TileSheet> tileSheet;
	TileCoord tileType;
};