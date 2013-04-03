#include "levelConstructor.h"
#include "QuitDialog.h"
#include "TilePlacer.h"
#include <cstdio>

class LevelEditor : public World
{
public:
	LevelEditor(std::string levelFileName)
	{
		this->levelFileName = levelFileName;
	}
	~LevelEditor()
	{
		rename(levelFileName.c_str(), (levelFileName + "~").c_str());
		saveLevelData(levelFileName, *levelData);
		delete levelData;
	}

	virtual void initialize()
	{
		levelData = new LevelData(loadLevelData(levelFileName));
		ConstructLevel(*levelData, this, true);
		// saveLevelData(levelFileName + ".out.txt", levelData); //testing
		
		// Initialize HUD here //

		updateList.clear();

		// Temp variable for setting up sprites before adding them
		// Sprite * t;

		// Creates an "exit sign" button that kills the world when pressed,
		//		sets it's scrollfactor to '0' so it doesn't scroll,
		//		sets it's layer to '100' so it's in front of everything else,
		//		and adds it to the world.
		//t = new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", startWorld<QuitDialog>);
		//t->scrollFactorX = 0;
		//t->scrollFactorY = 0;
		//t->layerID = 100;
		//add(t);

		add(new TilePlacer(&levelData->tileMaps.front()));
	}

	virtual void update()
	{
		World::update();
		if (input->specialsDown[GLUT_KEY_RIGHT]) cameraX += 10;
		if (input->specialsDown[GLUT_KEY_LEFT]) cameraX -= 10;
		if (input->specialsDown[GLUT_KEY_UP]) cameraY += 10;
		if (input->specialsDown[GLUT_KEY_DOWN]) cameraY -= 10;

		if (input->currentX < 50) cameraX -= 10;
		if (input->currentX > stateInfo->screenWidth - 50) cameraX += 10;
		if (input->currentY < 50) cameraY -= 10;
		if (input->currentY > stateInfo->screenHeight - 50) cameraY += 10;

		if (input->keysPressed[27]) //escape key
			game->killCurrentWorld();
	}

private:
	std::string levelFileName;

	LevelData * levelData;
};