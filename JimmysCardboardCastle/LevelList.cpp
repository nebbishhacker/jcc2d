#include "levelList.h"
#include "GameWorld.h"
#include <fstream>

LevelList::LevelList()
{
	std::ifstream stream;
	stream.open("levels/levellist.txt");
	while (!stream.eof()) {
		std::string str;
		std::getline(stream, str);
		levels.push_back(str);
	}
}
GameWorld * LevelList::constructLevel(unsigned int i)
{
	currentIndex = i;
	return new GameWorld(std::string(levels[i]));
}
GameWorld * LevelList::constructFirstLevel()
{
	currentIndex = 0;
	return new GameWorld(std::string(levels[0]));
}
GameWorld * LevelList::constructNextLevel()
{
	if (currentIndex < levels.size() - 1) ++currentIndex;
	return new GameWorld(std::string(levels[currentIndex]));
}
LevelList levelList;