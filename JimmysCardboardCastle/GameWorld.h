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
#include "healthHandler.h"

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
		//add(new Background(0, 0, 800, 600, "images/PlainHud.png", 100, 0, 0));
		t = new Button(325, /*game->stateInfo.screenHeight - 36*/ 550, 139, 50, "images/button_menu.png", startWorld<QuitDialog>);
		t->scrollFactorX = 0;
		t->scrollFactorY = 0;
		t->layerID = 100;
		add(t);

		score = 0;
		health = 0;
	}
	virtual void update()
	{
		World::update();

		// Get player state for updating the hud with
		if (!groups["player"].empty()) {
			Player * p = static_cast<Player*> (groups["player"].back());
			score = p->score;
			cookies = p->cookies;
			health = p->health;
		}
		if (input->keysPressed['~']) game->replacingCurrentWorld(new LevelEditor(levelFileName));
		if (input->keysPressed['+']) game->replacingCurrentWorld(levelList.constructNextLevel());
	}
	virtual void draw()
	{
		World::draw();

		// Draw the current score to the screen
		setColor(0, 0, 0);
		drawText(stringify(score), 10, stateInfo->screenHeight - 30);
		drawText("Cookies:" + stringify(cookies), 70, stateInfo->screenHeight - 30);
		//drawText("Health:" + stringify(health), 200, stateInfo->screenHeight - 30);
	}

	double score;
	double cookies;
	double health;

private:
	std::string levelFileName;
};