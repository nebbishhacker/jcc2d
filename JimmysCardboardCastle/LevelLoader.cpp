#pragma once

#include "levelLoader.h"

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
	//std::cout << label;
	return true;
}

static bool expectChar(char c, std::istream &stream)
{
	consumeSpace(stream);
	//std::cout << c;
	if (stream.peek() == c) {
		stream.get();
		//std::cout << c;
		return true;
	}
	return false;
}

static bool readString(std::istream &stream, std::string &s)
{
	s = "";
	if (!expectChar('"', stream)) return false;
	while (!expectChar('"', stream)) {
		//std::cout << (char)stream.peek();
		s += stream.get();
	}
	return true;
}

static bool readInt(std::istream &stream, int &n)
{
	std::string buff = "";
	consumeSpace(stream);
	if (std::isdigit(stream.peek()) || stream.peek() == '+' || stream.peek() == '-') buff += stream.get();
	else return false;
	while (std::isdigit(stream.peek())) buff += stream.get();
	n = std::atoi(buff.c_str());
	//std::cout << n;
	return true;
}

static bool readDouble(std::istream &stream, double &n)
{
	std::string buff = "";
	consumeSpace(stream);
	if (std::isdigit(stream.peek()) || stream.peek() == '.' || stream.peek() == '+' || stream.peek() == '-') buff += stream.get();
	else return false;
	while (std::isdigit(stream.peek()) || stream.peek() == '.') buff += stream.get();
	n = std::atof(buff.c_str());
	//std::cout << n;
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

void TileInfo::write(std::ostream &stream)
{
		if (exists) stream << c << "," << r;
		else stream << "-";
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

static void writeRow(std::ostream &stream, MapRow &row)
{
	stream << "\t\t[";
	for (MapRow::iterator it = row.begin(); it != row.end();)
	{
		it->write(stream);
		if (++it != row.end()) stream << ";";
	}
	stream << "]\n";
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

static void writeRows(std::ostream &stream, MapData &data)
{
	stream << "\t" << "data: [\n";
	for (MapData::iterator it = data.begin(); it != data.end(); ++it)
	{
		writeRow(stream, *it);
	}
	stream << "\t]\n";
}

void TileMap::autoSize()
{
	tilesHigh = data.size();
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i].size() > tilesWide) tilesWide = data[i].size();
	}
}

void TileMap::prepTile(int c, int r)
{
	while (r >= data.size()) data.push_back(MapRow());
	while (c >= data[r].size()) data[r].push_back(TileInfo());
	autoSize();
}

bool TileMap::read(std::istream &stream)
{
	if (!expectChar('{', stream)) return false;
	std::string label;
	while (!expectChar('}', stream)) {
		if (readLabel(stream, label)) {
			if (expectChar(':', stream)) {
				if (label == "tilesheetpath") readString(stream, tileSheetPath);
				if (label == "tilewidth") readInt(stream, tileWidth);
				if (label == "tileheight")readInt(stream, tileHeight);
				if (label == "sheetwidth") readInt(stream, sheetWidth);
				if (label == "sheetheight") readInt(stream, sheetHeight);
				if (label == "data") readRows(stream, data);
			}
		}
		else stream.get();
	}
	return true;
}

void TileMap::write(std::ostream &stream)
{
	stream << "tilemap: {\n";
	stream << "\t" << "tilesheetpath: " << '"' << tileSheetPath << '"' << "\n";
	stream << "\t" << "sheetwidth: " << sheetWidth << "\n";
	stream << "\t" << "sheetheight: " << sheetHeight << "\n";
	stream << "\t" << "tilewidth: " << tileWidth << "\n";
	stream << "\t" << "tileheight: " << tileHeight << "\n";
	writeRows(stream, data);
	stream << "}\n";
}

bool EntityInfo::read(std::istream &stream)
{
	type = "";
	xPos = 0;
	yPos = 0;
	if (!expectChar('{', stream)) return false;
	std::string label;
	while (!expectChar('}', stream)) {
		if (readLabel(stream, label)) {
			if (expectChar(':', stream)) {
				if (label == "type") readLabel(stream, type);
				if (label == "xpos") readInt(stream, xPos);
				if (label == "ypos") readInt(stream, yPos);
				if (label == "imagepath") readString(stream, imagePath);
				if (label == "framesizex") readInt(stream, frameSizeX);
				if (label == "framesizey") readInt(stream, frameSizeY);
				if (label == "layerid") readDouble(stream, layerID);
				if (label == "scrollfactorx") readDouble(stream, scrollFactorX);
				if (label == "scrollfactory") readDouble(stream, scrollFactorY);
				if (label == "moonboots") readInt(stream, moonBoots);
				if (label == "bat") readInt(stream, bat);
				if (label == "waterGun") readInt(stream, waterGun);
				if (label == "sheild") readInt(stream, sheild);
				if (label == "cornerx") readInt(stream, cornerX);
				if (label == "cornery") readInt(stream, cornerY);
				if (label == "target") readString(stream, target);
				if (label == "trigger") readString(stream, trigger);
				//std::cout << " ";
			}
		}
		else stream.get();
	}
	return true;
}

void EntityInfo::write(std::ostream &stream)
{
	stream << "\t{\n";
	stream << "\t\t" << "type: " << type << "\n";
	stream << "\t\t" << "xpos: " << xPos << "\n";
	stream << "\t\t" << "ypos: " << yPos << "\n";
	if (imagePath != "") stream << "\t\t" << "imagepath: " << '"' << imagePath << '"' << "\n";
	if (frameSizeX != INVALID_INT) stream << "\t\t" << "framesizex: " << frameSizeX << "\n";
	if (frameSizeY != INVALID_INT) stream << "\t\t" << "framesizey: " << frameSizeY << "\n";
	if (layerID != INVALID_DOUBLE) stream << "\t\t" << "layerid: " << layerID << "\n";
	if (scrollFactorX != INVALID_DOUBLE) stream << "\t\t" << "scrollfactorx: " << scrollFactorX << "\n";
	if (scrollFactorY != INVALID_DOUBLE) stream << "\t\t" << "scrollfactory: " << scrollFactorY << "\n";
	if (moonBoots != 0) stream << "\t\t" << "moonboots: " << moonBoots << "\n";
	if (bat != 0) stream << "\t\t" << "bat: " << bat << "\n";
	if (waterGun != 0) stream << "\t\t" << "watergun: " << waterGun << "\n";
	if (sheild != 0) stream << "\t\t" << "shield: " << sheild << "\n";
	if (type == "triggerarea") { // This is just to clean up a rash of cornerx's and cornery's from an earlier bug.
		if (cornerX != INVALID_INT) stream << "\t\t" << "cornerx: " << cornerX << "\n";
		if (cornerY != INVALID_INT) stream << "\t\t" << "cornery: " << cornerY << "\n";
	}
	if (trigger != "") stream << "\t\t" << "trigger: " << trigger << "\n";
	if (target != "") stream << "\t\t" << "target: " << target << "\n";
	stream << "\t}\n";
}

bool readEntityList(std::istream &stream, EntityList &entities)
{
	if (!expectChar('[', stream)) return false;
	while (!expectChar(']', stream)) {
		EntityInfo entityInfo;
		if (entityInfo.read(stream)) entities.push_back(entityInfo);
		else stream.get();
	}
	return true;
}

void writeEntityList(std::ostream &stream, EntityList &entities)
{
	stream << "[\n";
	for (EntityList::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		it->write(stream);
	}
	stream << "]\n";
}

void LevelData::read(std::istream &stream)
{
	std::string label;
	while (!expectChar(EOF, stream))
	{
		if (readLabel(stream, label)) {
			if (expectChar(':', stream)) {
				TileMap tileMap;
				if (label == "music") readString(stream, music);
				if (label == "tilemap" && tileMap.read(stream)) tileMaps.push_back(tileMap);
				if (label == "entities") readEntityList(stream, entities);
			}
		}
		else stream.get();
	}
}

void LevelData::write(std::ostream &stream)
{
	stream << "music: \"" << music << "\"\n";
	stream << "entities: ";
	writeEntityList(stream, entities);

	for (std::vector<TileMap>::iterator it = tileMaps.begin(); it != tileMaps.end(); ++it)
	{
		(*it).write(stream);
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

void saveLevelData(std::string fileName, LevelData &levelData)
{
	std::ofstream stream;
	stream.open(fileName);
	levelData.write(stream);
}