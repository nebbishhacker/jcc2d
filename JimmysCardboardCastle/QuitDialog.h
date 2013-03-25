#pragma once

#include "OverlayWorld.h"
#include "sharedButtonCallbacks.h"
#include "entities.h"

class QuitDialog : public OverlayWorld
{
public:
	virtual void initialize()
	{
		// Temp variable for setting up sprites before adding them
		Sprite * t;

		// Creates a semi-transparent black fill behind everything else.
		// Since this world inherits from OverlayWorld, you can see the next world down through it.
		t = new ScreenFillSprite(1, 1, 1, 0.75);
		t->layerID = -200;
		add(t);

		// Creates an "exit sign" button that kills the world when pressed,
		//		sets it's scrollfactor to '0' so it doesn't scroll,
		//		sets it's layer to '100' so it's in front of everything else,
		//		and adds it to the world.
		t = new Button(game->stateInfo.screenWidth / 2 - 99, game->stateInfo.screenHeight / 2 + 10, 198, 58, "images/text_quit.png", NULL);
		add(t);

		t = new Button(game->stateInfo.screenWidth / 2 - 122, game->stateInfo.screenHeight / 2 - 66, 112, 56, "images/button_yes.png", doubleKillWorld, true);
		add(t);

		t = new Button(game->stateInfo.screenWidth / 2 + 15, game->stateInfo.screenHeight / 2 - 66, 93, 56, "images/button_no.png", killWorld, true);
		add(t);
	}
};