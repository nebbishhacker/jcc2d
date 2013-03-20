#pragma once

#include "World.h"
#include "entities.h"

#include "TestWorld.h"
#include "HowToPlay.h"
#include "BrandonTestWorld.h"
// SharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "SharedButtonCallbacks.h"




class MainMenu : public World
{
public:
	virtual void initialize()
		

	{
		add(new Background(0, 0, 800, 600, "images/MainMenuBGTEST.png", -100, 0.5, 0.25));
		//  Ben's Button, using the templated startWorld callback
		add(new Button(60, 300, 139, 27, "images/NewGameButton.png", startWorld<BrandonTestWorld>));
		add(new Button(66, 275, 139, 22, "images/LoadGameButton.png", startWorld<BrandonTestWorld>));
		add(new Button(66, 250, 161, 22, "images/HowToPlayButton.png", startWorld<HowToPlay>));
		add(new Button(60, 225, 104, 22, "images/Options.png", startWorld<BrandonTestWorld>));
		add(new Button(66, 200, 91, 24, "images/CreditsButton.png", startWorld<TestWorld>));


		// Exit sign button
		add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/exit_sign.png", killWorld));
	}
};
