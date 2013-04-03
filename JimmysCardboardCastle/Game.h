#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cctype>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "Sprite.h"
//#include "HorizontalScrollingBackground.h"
#include "Timer.h"
#include "World.h"

//#include "entities.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// input information related to mouse
// you could add keyboard info in here too if you need to know if a key is currently pressed down
typedef struct _InputInfo
{
	bool mouseDown; // is the mouse down?
	bool mousePressed; // was the mouse pressed this frame?
	bool mouseReleased; // was the mouse released this frame?
	bool rightMouseDown; // is the right mouse button down?
	bool rightMousePressed; // was the right mouse button pressed this frame?
	bool rightMouseReleased; // was the right mouse button released this frame?
	int button; // which mouse button
	float clickX,clickY; // where the mouse was last clicked
	float rightClickX, rightClickY;
	float currentX,currentY;
	bool keysDown[128]; // array of boolean keystates, for tracking whether each key is down
	bool keysPressed[128]; // array of boolean keystates, for tracking whether each key was pressed this frame
	bool keysReleased[128]; // array of boolean keystates, for tracking whether each key was released this frame
	bool specialsDown[128]; // array of boolean keystates, for tracking whether each special key is down
	_InputInfo()
	{
		mouseDown = mousePressed = mouseReleased = rightMouseDown = rightMousePressed = rightMouseReleased = false;
		clickX = clickY = rightClickX = rightClickY = currentX = currentY = -1;
		button = 0;
		for (int i = 0; i < 128; i++) keysDown[i] = false;
		for (int i = 0; i < 128; i++) specialsDown[i] = false;
	}
}InputInfo;

// convenience structure to hold rgb values
typedef struct _RGBColor
{
	float red,green,blue;
}RGBColor;

// GameStateInfo
// this stores anything related to the state of the game
// i.e. what level are we on?, what is the score? etc.
typedef struct _GameStateInfo
{
	RGBColor bgClearColor; // the default clear color of the background

	// window width/height are the actual size of the window
	int windowWidth, windowHeight;

	// screen width/height are the apparent size of the window
	// i.e. you can have a 640x480 game screen stretched to 1280x1024
	// your calculations for actual pixel locations will depend on the ratio
	//   between screen and window width/height
	int screenWidth, screenHeight;

	float ratioWidth,ratioHeight;

	// array of boolean keystates, for tracking whether each key is down
}GameStateInfo;

/* 
 * Game.h
 * This is the main Game class of the base sprite lib starter code
 * it handles input, game loop update, display
 */
class Game
{
public:
	/* initialization */
	Game();
	~Game();
	void initializeGame();

	//void loadLevel();

	/* convenience functions */
	// screen size is the apparent size in pixels
	// i.e. this is what your game calculations should use
	void setScreenSize(int w, int h)
	{
		stateInfo.screenWidth = w;
		stateInfo.screenHeight = h;
	}
	// sets the screen-to-window pixel coordinates ratio
	void updateScreenRatio()
	{
		stateInfo.ratioWidth = stateInfo.screenWidth/(float)stateInfo.windowWidth;
		stateInfo.ratioHeight = stateInfo.screenHeight/(float)stateInfo.windowHeight;
		/* these are only really used for the mouse function
		   to get actual screen pixel coordinates from the window coordinates */
	}

	// sets the window size in pixels for the window itself
	void setNewWindowSize(int width,int height)
	{
		stateInfo.windowWidth = width;
		stateInfo.windowHeight = height;
	}

	/* draw/rendering routines */
	void draw(); // called from the main

	void PreDraw(); // prior to drawing
	void DrawGame(); // actual drawing the frame
	void PostDraw(); // cleanup and prepare for next frame

	/* update routines, the game loop */
	void update(); // called from main frequently

	// update the sprites animation (calling nextFrame())
	void updateAnimation();

	/* input callback functions */
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);
	void specialDown(int key, int x, int y);
	void specialUp(int key, int x, int y);

	// Fails whenever killCurrentWorld or setNewWorld has already been called.
	// WARNING! Deletes world pointer on failure, so be careful!
	void setNewWorld(World * world);

	// Fails whenever setNewWorld has just been called.
	void killCurrentWorld();

	// Fails whenever killCurrentWorld or setNewWorld has already been called.
	// WARNING! Deletes world pointer on failure, so be careful!
	void replacingCurrentWorld(World * world);

	/*********************************/
	/* DATA */
	/*********************************/
	
	/* game state info */
	GameStateInfo stateInfo;

	InputInfo input;

	/* timer's for rendering and animation/physics update */
	Timer *renderingTimer;
	Timer *updateTimer; // for physics/collisions etc.

private:
	bool setWorldNow();
	bool killWorldNow();

	World * currentWorld;
	World * newWorld;
	bool killWorld;

	bool fpsCounterOn;
};
