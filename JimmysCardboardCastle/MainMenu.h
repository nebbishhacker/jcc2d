#pragma once

#include "World.h"
#include "entities.h"

#include "TestWorld.h"
#include "HowToPlay.h"
#include "Levels.h"
// sharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "sharedButtonCallbacks.h"




class MainMenu : public World
{
public:
	virtual void initialize()
		

	{
		add(new Background(0, 0, 800, 600, "images/dev/MainMenuBGTEST.png", -100, 0.5, 0.25));
		add(new Button(60, 300, 139, 27, "images/dev/NewGameButton.png", startWorld<Level1>));
		add(new Button(66, 275, 139, 22, "images/dev/LoadGameButton.png", startWorld<Level1>));
		add(new Button(66, 250, 161, 22, "images/dev/HowToPlayButton.png", startWorld<HowToPlay>));
		add(new Button(60, 225, 104, 22, "images/dev/Options.png", startWorld<BrandonTestWorld>));
		add(new Button(66, 200, 91, 24, "images/dev/CreditsButton.png", startWorld<TestWorld>));


		// Exit sign button 
		add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", killWorld));
	}
};
