#pragma once

#include "World.h"
#include "entities.h"

static void addBG(World* world) {
	if (world->groups["background"].size() == 0)
	{
		Sprite * bg = new Background(0, -100, 825, 638, "images/ben_background(0.25scale).png", -100, 0.5, 0.25);
		world->add(bg);
		world->groups["background"].add(bg);
		//std::cout << "Background button GO!\n";
	}
}

static void playTestSound(World* world) {
	Sound sound = soundEngine.loadSound("sound/test_sfx.wav");
	soundEngine.playSound(sound);
}

class BensTestWorld : public World
{
public:
	virtual void initialize()
	{
		add(new Player(200, 200));
		//add(new CollTestBox(0, 0));
		//add(new CollTestBox(400, 200));

		//add(new Background(0, -100, 825, 638, "images/ben_background(0.25scale).png", -100, 0.5, 0.25));
		Sprite * t = new Button(500, 400, 64, 64, "images/Ben_Button.png", addBG);
		t->scrollFactorX = 0.5;
		t->scrollFactorY = 0.25;
		add(t);

		t = new Button(700, 400, 50, 75, "images/BUTTON_PaoloD.png", playTestSound);
		t->scrollFactorX = 0.5;
		t->scrollFactorY = 0.25;
		add(t);

		std::shared_ptr<TileSheet> tileSheet(new TileSheet(64, 64, 2, 2, "images/JCC_LavaRoomPlat.png"));

		for (int i = 0; i < 50; ++i) {
			Tile * tempTile = new Tile(i * 64, 0, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 1; i <= 50; ++i) {
			Tile * tempTile = new Tile(0, i * 64, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}

		for (int i = 1; i <= 50; ++i) {
			Tile * tempTile = new Tile(i / 2 * 64 + 512, 192 + i % 2 * 64, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
	}
};