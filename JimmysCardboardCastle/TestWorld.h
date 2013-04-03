#pragma once

#include "World.h"
#include "entities.h"

#include "BensTestWorld.h"
#include "Level1.h"
#include "LucasTestWorld.h"
#include "JonathansTestWorld.h"
#include "BrandonTestWorld.h"
#include "PaolosTestWorld.h"

// sharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "sharedButtonCallbacks.h"




class TestWorld : public World
{
public:
	virtual void initialize()
	{
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

		add(new Button(100, 0, 110, 100, "images/dev/Button_Level1.png", startWorld<Level1>));
		add(new Button(225, 0, 110, 100, "images/dev/Button_Level2.png", NULL));
		add(new Button(350, 0, 110, 100, "images/dev/Button_Level3.png", NULL));
		add(new Button(475, 0, 110, 100, "images/dev/Button_Level4.png", NULL));
		add(new Button(600, 0, 110, 100, "images/dev/Button_Level5.png", NULL));
	}
};