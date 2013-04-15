#include "GameWorld.h"
#include "entities.h"
#include "levelLoader.h"
#include "levelConstructor.h"
#include "QuitDialog.h"
#include "LevelEditor.h"
#include "healthHandler.h"
#include "sharedButtonCallbacks.h"

GameWorld::GameWorld(std::string levelFileName)
{
	this->levelFileName = levelFileName;
}

void GameWorld::initialize()
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
void GameWorld::update()
{
	World::update();

	// Get player state for updating the hud with
	if (!groups["player"].empty()) {
		Player * p = static_cast<Player*> (groups["player"].back());
		score = p->score;
		cookies = p->cookies;
		health = p->health;
		playerExists = true;
	}
	else playerExists = false;
	if (input->keysPressed['~']) game->replacingCurrentWorld(new LevelEditor(levelFileName));
	if (input->keysPressed['+']) game->replacingCurrentWorld(levelList.constructNextLevel());
}
void GameWorld::draw()
{
	World::draw();

	if (playerExists) {
		// Draw the current score to the screen
		setColor(0, 0, 0);
		drawText(stringify(score), 10, stateInfo->screenHeight - 30);
		drawText("Cookies:" + stringify(cookies), 70, stateInfo->screenHeight - 30);
		//drawText("Health:" + stringify(health), 200, stateInfo->screenHeight - 30);
	}
}

void GameWorld::centerCamera(double x, double y)
{
	World::centerCamera(x, y);
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
}