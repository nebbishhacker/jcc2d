#include "levelList.h"
#include "GameWorld.h"
#include <fstream>

LevelList::LevelList()
{
	currentIndex = 0;
	std::ifstream stream;
	stream.open("levels/levellist.txt");
	while (!stream.eof()) {
		std::string str;
		std::getline(stream, str);
		levels.push_back(str);
	}

	std::ifstream saveFile("save.txt");
	if (!saveFile.eof()) saveFile >> currentIndex;
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
	std::ofstream saveFile("save.txt");
	//if (saveFile) {
		saveFile << currentIndex;
		saveFile.close();
	//}
	return new GameWorld(std::string(levels[currentIndex]));
}
GameWorld * LevelList::constructCurrentLevel()
{
	return new GameWorld(std::string(levels[currentIndex]));
}
LevelList levelList;