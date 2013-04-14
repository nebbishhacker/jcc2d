#pragma once
#include "TextureSprite.h"

class TriggerArea: public Sprite
{
public:
	TriggerArea(double posX, double posY, double cornerPosX, double cornerPosY, std::string targetGroup = "", std::string groupToAdd = "")
	{
		setPosition(posX, posY);
		hitbox = Hitbox(0, 0, cornerPosX - posX, cornerPosY - posY);
		this->targetGroup = targetGroup;
		this->groupToAdd = groupToAdd;
	}
	virtual void update();
	
private:
	std::string targetGroup;
	std::string groupToAdd;
};