#pragma once

#include "World.h"
#include "entities.h"

#include "BensTestWorld.h"
#include "Levels.h"
#include "LucasTestWorld.h"
#include "JonathansTestWorld.h"
#include "BrandonTestWorld.h"
#include "PaolosTestWorld.h"

// SharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "SharedButtonCallbacks.h"




class TestWorld : public World
{
public:
	virtual void initialize()
	{
		//  Ben's Button, using the templated startWorld callback
		add(new Button(304, 500, 64, 64, "images/Ben_Button.png", startWorld<Level1>));

		//Brandon's Button
		add(new Button(100, 400, 64, 32, "images/BrandonsButton.png", startWorld<BrandonTestWorld>));

		//Paolo's Button
		add(new Button(368, 250, 100, 100, "images/Paolo_IronMan_Button.png", startWorld<PaolosTestWorld>));

		//Jonathan's Button
		add(new Button(368, 400, 100,100, "images/Jonathan'sHam.png", startWorld<JonathansTestWorld>)); 

		//Lucas's Button
		add(new Button(468, 500, 64, 64, "images/BUTTON_WRIGHT.png", startWorld<LucasTestWorld>));

		// Exit sign button
		add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/exit_sign.png", killWorld));
	}
};
