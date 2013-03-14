#pragma once

#include "World.h"
#include "entities.h"

#include "BensTestWorld.h"


//Special-purpose buttons

//Ben's Button Class
class BenStartButton : public Button
{
public:
	BenStartButton::BenStartButton(double x, double y, int sizeX, int sizeY, std::string filename) : Button(x, y, sizeX, sizeY, filename) {}
	virtual void callback() { if (world) world->game->setNewWorld(new BensTestWorld); }
};

//Brandon's Button Class

//Paolo's Button Class

//Jonathan's Button Class

//Lucas's Button Class



class TestWorld : public World
{
public:
	virtual void initialize()
	{
		//Ben's Button
		add(new BenStartButton(368, 500, 64, 64, "images/Ben_Button.png"));

		//Brandon's Button

		//Paolo's Button

		//Jonathan's Button

		//Lucas's Button
	}
};