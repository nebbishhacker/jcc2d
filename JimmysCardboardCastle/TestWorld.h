#pragma once

#include "World.h"
#include "entities.h"

#include "BensTestWorld.h"
#include "LucasTestWorld.h"
#include "JonathansTestWorld.h"
#include "BrandonTestWorld.h"
#include "PaolosTestWorld.h"


//Special-purpose buttons

//Ben's Button Class
class BenStartButton : public Button
{
public:
	BenStartButton::BenStartButton(double x, double y, int sizeX, int sizeY, std::string filename) : Button(x, y, sizeX, sizeY, filename) {}
	virtual void callback() { if (world) world->game->setNewWorld(new BensTestWorld); }
};

//Brandon's Button Class
class BrandonStartButton : public Button
{
public:
	BrandonStartButton::BrandonStartButton(double x, double y, int sizeX, int sizeY, std::string filename) : Button(x, y, sizeX, sizeY, filename) {}
	virtual void callback() { if (world) world->game->setNewWorld(new BrandonTestWorld); }
};

//Paolo's Button Class
class PaolosStartButton : public Button
{
public:
	PaolosStartButton::PaolosStartButton(double x, double y, int sizeX, int sizeY, std::string filename) : Button(x, y, sizeX, sizeY, filename) {}
	virtual void callback() { if (world) world->game->setNewWorld(new PaolosTestWorld); }
};

//Jonathan's Button Class
class JonathanStartButton : public Button
{
public:
	JonathanStartButton::JonathanStartButton(double x, double y, int sizeX, int sizeY, std::string filename) : Button(x, y, sizeX, sizeY, filename) {}
	virtual void callback() { if (world) world->game->setNewWorld(new JonathansTestWorld); }
};

//Lucas's Button Class
class LucasStartButton : public Button
{
public:
	LucasStartButton::LucasStartButton(double x, double y, int sizeX, int sizeY, std::string filename) : Button(x, y, sizeX, sizeY, filename) {}
	virtual void callback() { if (world) world->game->setNewWorld(new LucasTestWorld); }
};


class TestWorld : public World
{
public:
	virtual void initialize()
	{
		//Ben's Button
		add(new BenStartButton(368, 500, 64, 64, "images/Ben_Button.png"));

		//Brandon's Button
		add(new BrandonStartButton(100, 400, 64, 32, "images/BrandonsButton.png"));
		//Paolo's Button
		add(new PaolosStartButton(368, 250, 100, 100, "images/Paolo_IronMan_Button.png"));

		//Jonathan's Button
		add(new JonathanStartButton(368, 400, 100,100, "images/Jonathan'sHam.png")); 

		//Lucas's Button
		add(new LucasStartButton(468, 500, 64, 64, "images/BUTTON_WRIGHT.png"));
	}
};
