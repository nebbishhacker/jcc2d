#pragma once;

#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <climits>

#include <iostream>


const int INVALID_INT = INT_MAX;


struct TileInfo {
	int c, r;
	bool exists;

	bool read(std::istream &stream);
};

typedef std::vector<TileInfo> MapRow;

typedef std::vector<MapRow> MapData;

struct TileMap
{
	std::string tileSheetPath;
	int tileWidth;
	int tileHeight;
	MapData data;
	
	bool read(std::istream &stream);
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

	EntityInfo()
	{
		xPos = 0;
		yPos = 0;
		layerID = INVALID_INT;
		scrollFactorX = INVALID_INT;
		scrollFactorY = INVALID_INT;
	}
};

typedef std::vector<EntityInfo> EntityList;

struct LevelData
{
	std::vector<TileMap> tileMaps;
	EntityList entities;

	void read(std::istream &stream);
};

LevelData loadLevelData(std::string fileName);