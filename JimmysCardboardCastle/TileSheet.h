#pragma once
#include "TextureSprite.h"
#include <memory>

//	You need to create a tileSheet before you create any tiles.
//  Also, you need to create it using a std::shared_ptr.
class TileSheet: public TextureSprite
{
public:
	TileSheet(int tileWidth, int tileHeight, int tilesWide, int tilesHigh, std::string filename) : TextureSprite(filename)
	{
		setNumberOfAnimations(1);
		setSpriteFrameSize(tileWidth,tileHeight);
		for (int j = 0; j < tilesHigh; ++j)
			for (int i = 0; i < tilesWide; ++i)
				addSpriteAnimFrame(0, i * tileWidth, j * tileHeight);
		setCurrentAnimation(0);
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
	}
	int tileWidth;
	int tileHeight;
};

class Tile: public Sprite
{
public:
	Tile(double posX, double posY, int tileNum, std::shared_ptr<TileSheet> tileSheet)
	{
		setPosition(posX, posY);
		this->tileSheet = tileSheet;
		this->tileNum = tileNum;
		hitbox = Hitbox(0, 0, tileSheet->tileWidth, tileSheet->tileHeight);
	}
	virtual void draw(Vector2D camera)
	{
		tileSheet->setFrame(tileNum);
		tileSheet->setPosition(position);
		tileSheet->draw(camera);
	}
	
	int tileNum;
	std::shared_ptr<TileSheet> tileSheet;
};