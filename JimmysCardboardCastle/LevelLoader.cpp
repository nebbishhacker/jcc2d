#pragma once

#include "LevelLoader.h"

static void consumeSpace(std::istream &stream)
{
	while (std::isspace(stream.peek())) stream.get();
}

static bool readLabel(std::istream &stream, std::string &label)
{
	label = "";
	consumeSpace(stream);
	if (!std::isalnum(stream.peek())) return false;
	while (std::isalnum(stream.peek())) label += stream.get();
	std::cout << label;
	return true;
}

static bool expectChar(char c, std::istream &stream)
{
	consumeSpace(stream);
	//std::cout << c;
	if (stream.peek() == c) {
		stream.get();
		std::cout << c;
		return true;
	}
	return false;
}

static bool readString(std::istream &stream, std::string &s)
{
	s = "";
	if (!expectChar('"', stream)) return false;
	while (!expectChar('"', stream)) {
		std::cout << (char)stream.peek();
		s += stream.get();
	}
	return true;
}

static bool readInt(std::istream &stream, int &n)
{
	std::string buff = "";
	consumeSpace(stream);
	if (!std::isdigit(stream.peek())) return false;
	while (std::isdigit(stream.peek())) buff += stream.get();
	n = std::atoi(buff.c_str());
	std::cout << n;
	return true;
}

bool TileInfo::read(std::istream &stream)
{
	if (expectChar('-', stream)) {
		exists = false;
		c = r = -1;
	}
	else if (readInt(stream, c)) {
		expectChar(',', stream);
		readInt(stream, r);
		exists = true;
	}
	else return false;
	return true;
}

static bool readRow(std::istream &stream, MapRow &row)
{
	if (!expectChar('[', stream)) return false;
	while (!expectChar(']', stream)) {
		TileInfo tileInfo;
		if (!tileInfo.read(stream)) stream.get();
		row.push_back(tileInfo);
		expectChar(';', stream);
	}
	return true;
}

static bool readRows(std::istream &stream, MapData &data)
{
	if (!expectChar('[', stream)) return false;
	while (!expectChar(']', stream)) {
		std::vector<TileInfo> row;
		if (readRow(stream, row)) data.push_back(row);
		else stream.get();
	}
	return true;
}

bool TileMap::read(std::istream &stream)
{
	if (!expectChar('{', stream)) return false;
	std::cout << "\n";
	std::string label;
	while (!expectChar('}', stream)) {
		if (readLabel(stream, label)) {
			if (expectChar(':', stream)) {
				if (label == "tilesheetpath") readString(stream, tileSheetPath);
				if (label == "tilewidth") readInt(stream, tileWidth);
				if (label == "tileheight") readInt(stream, tileWidth);
				if (label == "data") readRows(stream, data);
				std::cout << "\n";
			}
		}
		else stream.get();
	}
	return true;
}

bool readEntityInfo(std::istream &stream, EntityInfo &info)
{
	info.type = "";
	info.xPos = 0;
	info.yPos = 0;
	if (!expectChar('{', stream)) return false;
	std::cout << "\n";
	std::string label;
	while (!expectChar('}', stream)) {
		if (readLabel(stream, label)) {
			if (expectChar(':', stream)) {
				if (label == "type") readLabel(stream, info.type);
				if (label == "xpos") readInt(stream, info.xPos);
				if (label == "ypos") readInt(stream, info.yPos);
				std::cout << "\n";
			}
		}
		else stream.get();
	}
	return true;
}

bool readEntityList(std::istream &stream, EntityList &entities)
{
	if (!expectChar('[', stream)) return false;
	while (!expectChar(']', stream)) {
		EntityInfo entityInfo;
		if (readEntityInfo(stream, entityInfo)) entities.push_back(entityInfo);
		else stream.get();
	}
	return true;
}

void LevelData::read(std::istream &stream)
{
	std::string label;
	while (!expectChar(EOF, stream))
	{
		if (readLabel(stream, label)) {
			if (expectChar(':', stream)) {
				TileMap tileMap;
				if (label == "tilemap" && tileMap.read(stream)) tileMaps.push_back(tileMap);
				if (label == "entities") readEntityList(stream, entities);
			}
		}
		else stream.get();
	}
}

LevelData loadLevelData(std::string fileName)
{
	LevelData levelData;

	std::ifstream stream;
	stream.open(fileName);
	levelData.read(stream);

	return levelData;
}