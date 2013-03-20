#pragma once

#include <string>
#include "World.h"
#include "entities.h"
#include "SharedButtonCallbacks.h"
#include "LevelLoader.h"
#include "LevelConstructor.h"

class GameWorld : public World
{
public:
	GameWorld(std::string levelFileName)
	{
		this->levelFileName = levelFileName;
	}

	virtual void initialize()
	{
		LevelData levelData = loadLevelData(levelFileName);
		ConstructLevel(levelData, this);

		add(new Background(0, -100, 825, 638, "images/ben_background(0.25scale).png", -100, 0.5, 0.25));
		
		// Initialize HUD here


		// Everything below shouldn't really be here.

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
	}

private:
	std::string levelFileName;
};