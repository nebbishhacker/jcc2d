#pragma once;

#include <string>
#include <istream>
#include <ostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cfloat>

#include "TileSheet.h"
#include "Sprite.h"

//#include <iostream>


const double INVALID_DOUBLE = DBL_MAX;
const int INVALID_INT = INT_MAX;


struct TileInfo {
	int c, r;
	bool exists;
	Sprite * entity;

	TileInfo()
	{
		c = r = -1;
		exists = false;
		entity = NULL;
	}
	bool read(std::istream &stream);
	void write(std::ostream &stream);
};

typedef std::vector<TileInfo> MapRow;

typedef std::vector<MapRow> MapData;

struct TileMap
{
	std::string tileSheetPath;
	int sheetWidth;
	int sheetHeight;
	int tileWidth;
	int tileHeight;
	int tilesWide;
	int tilesHigh;
	MapData data;
	std::shared_ptr<TileSheet> tileSheetPointer;
	
	void autoSize();
	void prepTile(int r, int c);

	bool read(std::istream &stream);
	void write(std::ostream &stream);
};

struct EntityInfo
{
	std::string type;
	int xPos;
	int yPos;
	std::string imagePath;
	int frameSizeX;
	int frameSizeY;
	double layerID;
	double scrollFactorX;
	double scrollFactorY;
	int moonBoots; // pretend it's a bool
	int bat; // pretend it's a bool
	int waterGun; // pretend it's a bool
	int sheild; // pretend it's a bool
	int cornerX;
	int cornerY;
	std::string target;
	std::string trigger;
	Sprite * entity;
	int bubble;

	EntityInfo()
	{
		xPos = 0;
		yPos = 0;
		frameSizeX = INVALID_INT;
		frameSizeY = INVALID_INT;
		layerID = INVALID_DOUBLE;
		scrollFactorX = INVALID_DOUBLE;
		scrollFactorY = INVALID_DOUBLE;
		moonBoots = 0;
		bat = 0;
		waterGun = 0;
		sheild = 0;
		entity = NULL;
<<<<<<< HEAD
		int cornerX = INVALID_INT;
		int cornerY = INVALID_INT;
		bubble = INVALID_INT;
=======
		cornerX = INVALID_INT;
		cornerY = INVALID_INT;
>>>>>>> 10e1d16475f6c7475926965acb6f60f4462933c8
	}

	bool read(std::istream &stream);
	void write(std::ostream &stream);
};

typedef std::vector<EntityInfo> EntityList;

struct LevelData
{
	std::string music;
	std::vector<TileMap> tileMaps;
	EntityList entities;

	void read(std::istream &stream);
	void write(std::ostream &stream);
};

LevelData loadLevelData(std::string fileName);

void saveLevelData(std::string fileName, LevelData &levelData);