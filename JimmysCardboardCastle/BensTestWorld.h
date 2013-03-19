#pragma once

#include "World.h"
#include "entities.h"
#include "SharedButtonCallbacks.h"

static void addBG(World* world) {
	if (world->groups["background"].size() == 0)
	{
		Sprite * bg = new Background(0, -100, 825, 638, "images/ben_background(0.25scale).png", -100, 0.5, 0.25);
		world->add(bg);
		world->groups["background"].add(bg);
		//std::cout << "Background button GO!\n";
	}
	else for(SpriteGroup::iterator it = world->groups["background"].begin(); it != world->groups["background"].end(); ++it)
	{
		(*it)->kill();
		std::cout << "ow!\n";
	}
}

static void playTestSound(World* world) {
	Sound sound = soundEngine.loadSound("sound/wave.wav");
	soundEngine.playSound(sound);
}

class BensTestWorld : public World
{
public:
	virtual void initialize()
	{
		// Temp variable for setting up sprites before adding them
		Sprite * t;

		// Creates an "exit sign" button that kills the world when pressed,
		//		sets it's scrollfactor to '0' so it doesn't scroll,
		//		sets it's layer to '100' so it's in front of everything else,
		//		and adds it to the world.
		t = new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/exit_sign.png", killWorld);
		t->scrollFactorX = 0;
		t->scrollFactorY = 0;
		t->layerID = 100;
		add(t);

		// Add da player
		add(new Player(200, 200));

		t = new Button(500, 400, 64, 64, "images/Ben_Button.png", addBG);
		t->scrollFactorX = 0.5;
		t->scrollFactorY = 0.25;
		add(t);

		add(new Button(710, 512, 50, 75, "images/BUTTON_PaoloD.png", playTestSound));

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

		for (int i = 1; i <= 25; ++i) {
			Tile * tempTile = new Tile(i * 192 + 512, 192 + i % 2 * 256, rand() % 4, tileSheet);
			groups["ground"].add(tempTile);
			add(tempTile);
		}
	}
};