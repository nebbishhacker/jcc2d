#pragma once

#include "World.h"
#include "entities.h"

#include "BensTestWorld.h"
#include "LucasTestWorld.h"
#include "JonathansTestWorld.h"
#include "BrandonTestWorld.h"
#include "PaolosTestWorld.h"

// NOTICE: Buttons have changed to allow for more concise usage. You should all delete your button classes, and use the templated startWorld
//		function below as a callback for the base Button class instead. Use the second Ben's button added in TestWorld for reference.


// Special-purpose buttons

// Ben's Button Callback
// You can use proper callbacks with buttons now, instead of subclassing! They need to take a pointer to the current world as an argument.
static void startBensWorld(World * currentWorld)
{
	currentWorld->game->setNewWorld(new BensTestWorld());
}

// Alternatively: Templated callback, specifically for starting a new world. Things like this should be good if you need a lot of similar callbacks.
template<class TWorld>
void startWorld(World * currentWorld)
{
	currentWorld->game->setNewWorld(new TWorld());
}

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
		// Ben's Button, using the startBensWorld callback. For illustrative purposes - most buttons with custom functions will work this way,
		//		but it's not actually necessary here, thanks to startWorld<T>()
		add(new Button(368, 500, 64, 64, "images/Ben_Button.png", startBensWorld));

		//  Ben's Button, using the templated startWorld callback (recommended, when convenient / available)
		add(new Button(304, 500, 64, 64, "images/Ben_Button.png", startWorld<BensTestWorld>));

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
