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
		Sprite * t;
		t = new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/exit_sign.png", killWorld);
		t->scrollFactorX = 0;
		t->scrollFactorY = 0;
		t->layerID = 100;
		add(t);
		add(new Player(200, 200));
		//add(new CollTestBox(0, 0));
		//add(new CollTestBox(400, 200));

		add(new Background(0, -100, 1600, 1200, "images/PGBackground.png", -100, 0.5, 0.25));

		
		add(new Button(300, 0, 68, 68, "images/FanBase.png", playTestSound2));


		std::shared_ptr<TileSheet> tileSheet(new TileSheet(32, 32, 4, 1, "images/JCC_PlatSPR.png"));

		for (int i = 0; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 0, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 0; i < 15; ++i) {
			Tile * tempTile = new Tile(i * 32, 350, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 40; i < 70; ++i) {
			Tile * tempTile = new Tile(i * 32, 650, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 20; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 450, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 1; i <= 50; ++i) {
			Tile * tempTile = new Tile(0, i * 32, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 20; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 850, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 0; i < 30; ++i) {
			Tile * tempTile = new Tile(i * 32, 1050, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 20; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 1250, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 0; i < 30; ++i) {
			Tile * tempTile = new Tile(i * 32, 1450, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 20; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 1650, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 50; i < 100; ++i) {
			Tile * tempTile = new Tile(i * 32, 1800, rand() % 5, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
		for (int i = 0; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 32, 2000, rand() % 5, tileSheet);
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

