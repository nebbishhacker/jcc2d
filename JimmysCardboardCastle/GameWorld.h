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

	double score;
	double cookies;
	double health;

private:
	std::string levelFileName;
};