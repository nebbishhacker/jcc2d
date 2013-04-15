#pragma once

#include "World.h"
#include <string>
#include "convert.h"
#include "drawPrimitives.h"

class GameWorld : public World
{
public:
	GameWorld(std::string levelFileName);

	virtual void initialize();
	virtual void update();
	virtual void draw();
	virtual void centerCamera(double x = 0, double y = 0);

	double score;
	double cookies;
	double health;

private:
	//int levelHeight;
	//int levelWidth;
	bool playerExists;
	std::string levelFileName;
};