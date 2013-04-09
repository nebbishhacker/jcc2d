#pragma once

#include <string>
#include "drawPrimitives.h"
#include "convert.h"
#include "World.h"
#include "entities.h"
#include "SharedButtonCallbacks.h"
#include "levelLoader.h"
#include "levelConstructor.h"
#include "QuitDialog.h"
#include "LevelEditor.h"

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
		// saveLevelData(levelFileName + ".out.txt", levelData); //testing

		// Temp variable for setting up sprites before adding them
		Sprite * t;
		
		// Initialize HUD here //
		t = new Button(325, /*game->stateInfo.screenHeight - 36*/ 550, 139, 50, "images/dev/MenuButton.png", startWorld<QuitDialog>);
		t->scrollFactorX = 0;
		t->scrollFactorY = 0;
		t->layerID = 100;
		add(t);

		score = 0;
	}
	virtual void update()
	{
		World::update();

		// Get player state for updating the hud with
		if (!groups["player"].empty()) {
			Player * p = static_cast<Player*> (groups["player"].back());
			score = p->score;
		}

		if (input->keysPressed['~']) game->replacingCurrentWorld(new LevelEditor(levelFileName));
	}
	virtual void draw()
	{
		World::draw();

		// Draw the current score to the screen
		setColor(0, 0, 0);
		drawText(stringify(score), 10, stateInfo->screenHeight - 30);
	}

	double score;

private:
	std::string levelFileName;
};