#pragma once

#include <vector>
#include <string>

class GameWorld;

class LevelList
{
public:
	LevelList();
	GameWorld * constructLevel(unsigned int i);
	GameWorld * constructFirstLevel();
	GameWorld * constructNextLevel();

private:
	std::vector<std::string> levels;
	unsigned int currentIndex;
};
extern LevelList levelList;
