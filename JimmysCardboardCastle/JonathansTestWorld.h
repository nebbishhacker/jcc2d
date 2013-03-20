#pragma once

#include "World.h"
#include "entities.h"

static void playTestSound2(World* world) {
		Sound sound = soundEngine.loadSound("sound/Wind.mp3");
		soundEngine.playSound(sound);
		}


class JonathansTestWorld : public World
{
public:
	virtual void initialize()
	{
		add(new Player(200, 200));
		//add(new CollTestBox(0, 0));
		//add(new CollTestBox(400, 200));

		add(new Background(0, -100, 1600, 1200, "images/PGBackground.png", -100, 0.5, 0.25));

		
		add(new Button(300, -320, 68, 68, "images/FanBase.png", playTestSound2));


		std::shared_ptr<TileSheet> tileSheet(new TileSheet(32, 32, 4, 1, "images/JCC_PlatSPR.png"));

		for (int i = 0; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, -350, rand() % 4, tileSheet);
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

