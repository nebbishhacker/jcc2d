#pragma once

#include "World.h"
#include "entities.h"

class BrandonTestWorld : public World
{
public:
	virtual void initialize()
	{

		Sprite * t; 
		t = new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/exit_sign.png", killWorld);
		t->scrollFactorX = 0;
		t->scrollFactorY = 0;
		t->layerID = 100;
		add(t);

		add(new Player(200, 200));
		//add(new CollTestBox(0, 0));
		//add(new CollTestBox(400, 200));

		add(new Background(0, -100, 2000, 1600, "images/lavaRoom_bgm.png", -100, 0.5, 0.25));

		std::shared_ptr<TileSheet> tileSheet(new TileSheet(32, 32, 4, 4, "images/JCC_LavaRoomPlat.png"));

		for (int i = 0; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 0, rand() % 4 + 11, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 1; i <= 50; ++i) {
			Tile * tempTile = new Tile(0, i * 32, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 1; i <= 50; ++i) {
			Tile * tempTile = new Tile(i / 2 * 32 + 544, 170 + i % 2 * 32, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
	}
};