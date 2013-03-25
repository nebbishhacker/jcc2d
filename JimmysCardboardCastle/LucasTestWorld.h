#pragma once

#include "World.h"
#include "entities.h"

#include "SharedButtonCallbacks.h"
#include "QuitDialog.h"

class LucasTestWorld : public World
{
public:
	virtual void initialize()
	{
		add(new Player(200, 200));
		//add(new CollTestBox(0, 0));
		//add(new CollTestBox(400, 200));

		add(new Background(0, -100, 825, 638, "images/dev/ben_background(0.25scale).png", -100, 0.5, 0.25));

		std::shared_ptr<TileSheet> tileSheet(new TileSheet(32, 32, 4, 1, "images/dev/JCC_PlatSPR.png"));

		for (int i = 0; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 0, rand() % 4, tileSheet);
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

		// Temp variable for setting up sprites before adding them
		Sprite * t;

		// Creates an "exit sign" button that kills the world when pressed,
		//		sets it's scrollfactor to '0' so it doesn't scroll,
		//		sets it's layer to '100' so it's in front of everything else,
		//		and adds it to the world.
		t = new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", startWorld<QuitDialog>);
		t->scrollFactorX = 0;
		t->scrollFactorY = 0;
		t->layerID = 100;
		add(t);
	}
};