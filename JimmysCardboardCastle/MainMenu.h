#pragma once

#include "World.h"
#include "entities.h"

#include "TestWorld.h"
#include "HowToPlay.h"
// sharedButtonCallbacks.h is where I'm putting button callback functions that are useful in more than one world.
#include "sharedButtonCallbacks.h"




class MainMenu : public World
{
public:
	virtual void initialize()
	{
		add(new Background(0, 0, 800, 600, "images/spr_mainMenu.png", -100, 0.5, 0.25));
		add(new Button(60+20, 300+10, 145, 28, "images/dev/NewGameButton.png", startLevel<0>));
		add(new Button(66+20, 275+10, 139, 22, "images/dev/LoadGameButton.png", startLevel<0>));
		add(new Button(66+20, 250+10, 161, 22, "images/dev/HowToPlayButton.png", startWorld<HowToPlay>));
		add(new Button(60+20, 225+10, 104, 22, "images/dev/Options.png", startWorld<BrandonTestWorld>));
		add(new Button(66+20, 200+10, 91, 24, "images/dev/CreditsButton.png", startWorld<TestWorld>));


		// Exit sign button 
		add(new Button(0, game->stateInfo.screenHeight - 36, 76, 36, "images/dev/exit_sign.png", killWorld));

		// This is how you set the music for a menu
		setMusic(soundEngine.loadStream("sound/electrodoodle.mp3"));
	}
};
