#pragma once

#include "World.h"
#include "entities.h"

#include "BensTestWorld.h"
#include "LucasTestWorld.h"
#include "JonathansTestWorld.h"
#include "BrandonTestWorld.h"
#include "PaolosTestWorld.h"
#include "GameWorld.h"

// sharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "sharedButtonCallbacks.h"


static void startLevel1(World * w)  { w->game->setNewWorld(new GameWorld("levels/level1.txt")); }
static void startLevel2(World * w)  { w->game->setNewWorld(new GameWorld("levels/level2.txt")); }
static void startLevel3(World * w)  { w->game->setNewWorld(new GameWorld("levels/level3.txt")); }
static void startLevel4(World * w)  { w->game->setNewWorld(new GameWorld("levels/level4.txt")); }
static void startLevel5(World * w)  { w->game->setNewWorld(new GameWorld("levels/level5.txt")); }


class TestWorld : public World
{
public:
	virtual void initialize()
	{
		//add(new Background(0, 0, 800, 600, "images/dev/CreditsScreen.png", -100, 0.5, 0.25));
		//  Ben's Button, using the templated startWorld callback
		add(new Button(304, 500, 64, 64, "images/dev/Ben_Button.png", startWorld<BensTestWorld>));

		//Brandon's Button
		add(new Button(100, 400, 64, 32, "images/dev/BrandonsButton.png", startWorld<BrandonTestWorld>));

		//Paolo's Button
		add(new Button(368, 250, 100, 100, "images/dev/Paolo_IronMan_Button.png", startWorld<PaolosTestWorld>));

		//Jonathan's Button
		add(new Button(368, 400, 100,100, "images/dev/Jonathan'sHam.png", startWorld<JonathansTestWorld>)); 

		//Lucas's Button
		add(new Button(468, 500, 50, 75, "images/dev/BUTTON_WRIGHT.png", startWorld<LucasTestWorld>));

		// Exit sign button
		add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", killWorld));

		add(new Button(100, 0, 110, 100, "images/dev/Button_Level1.png", startLevel1));
		add(new Button(225, 0, 110, 100, "images/dev/Button_Level2.png", startLevel2));
		add(new Button(350, 0, 110, 100, "images/dev/Button_Level3.png", startLevel3));
		add(new Button(475, 0, 110, 100, "images/dev/Button_Level4.png", startLevel4));
		add(new Button(600, 0, 110, 100, "images/dev/Button_Level5.png", startLevel5));
	}
};