#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include <vector>
#include <cmath>
//#include <map>
//#include <string>
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

#include "entities.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* these are enumerated types (just names) of game states
   that the game can be in at any moment.  These help you
   manage the flow of the game.  Especially if you want 
   to do different updates (call different update functions)
   or have different behaviour for input (i.e. mouse and keyboard
   functions might have different behaviour in-game (STATE_GAMEPLAY)
   versus when in the Menu (STATE_MAINMENU)
*/
enum {
	STATE_GAMEPLAY=0, 
	STATE_MAINMENU, 
	STATE_CREDITS
};

// input information related to mouse
// you could add keyboard info in here too if you need to know if a key is currently pressed down
typedef struct _InputInfo
{
	bool mouseDown; // is the mouse down?
	int button; // which mouse button
	float clickX,clickY; // where the mouse was clicked
	float currentX,currentY;
	bool keysDown[128]; // array of boolean keystates, for tracking whether each key is down
	bool specialsDown[128]; // array of boolean keystates, for tracking whether each special key is down
	_InputInfo()
	{
		mouseDown = false;
		button = 0;
		for (int i = 0; i <  128; i++) keysDown[i] = false;
		for (int i = 0; i <  128; i++) specialsDown[i] = false;
	}
	//bool shiftDown();
	//bool ctrlDown();
	//bool altDown();
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
	int gameState; // the game state, see enum's above
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

	/* functions for adding sprites */

	// add a sprite to the game
	// automatically adds it to the draw list, update list, etc.
	//void add(Sprite *s);

	// add a sprite to the draw list
	// only sprites in the draw list will be drawn
	//void addSpriteToDrawList(Sprite *s);

	// add a sprite to the update list
	// all sprites in the update list will be updated (for now, at least)
	//void addSpriteToUpdateList(Sprite *s);

	// add a sprite to the animation list
	// sprites in the animation list will have their current frame incremented
	//void addSpriteToAnimationList(Sprite *s);

	/* draw/rendering routines */
	void draw(); // called from the main

	void PreDraw(); // prior to drawing
	void DrawGame(); // actual drawing the frame
	void PostDraw(); // cleanup and prepare for next frame
	
	//void drawSprites(); // draw the sprite list
	//void drawTestPrimitives(); // test function

	/* update routines, the game loop */
	void update(); // called from main frequently

	// update the sprites in the sprite list
	//void updateSprites();

	// update the sprites animation (calling nextFrame())
	void updateAnimation();

	/* slated a sprite for deletion (adds to hitList) */
	//void remove(Sprite*);

	/* clear the list of sprite slated for destruction, deleting and removing each member */
	//void clearHitList();

	/* input callback functions */
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);
	void specialDown(int key, int x, int y);
	void specialUp(int key, int x, int y);

	/* camera positioning */
	//void centerCamera(double x = 0, double y = 0);

	// fails whenever killCurrentWorld or setNewWorld has already been called
	// WARNING! Deletes world pointer on failure, so be careful!
	void setNewWorld(World * world);

	// fails whenever setNewWorld has just been called
	void killCurrentWorld();

	// fails whenever killCurrentWorld or setNewWorld has already been called
	// WARNING! Deletes world pointer on failure, so be careful!
	void replacingCurrentWorld(World * world);

	/*********************************/
	/* DATA */
	/*********************************/
	
	/* game state info */
	GameStateInfo stateInfo;

	/* individual sprites to manipulate by name */
	//Sprite *testSprite;
	//Sprite *animatedSprite;
	//Sprite *animatedSprite2;

	//std::vector<Sprite*> testPlayerList;

	//// the background scroller
	//HorizontalScrollingBackground *bg;

	InputInfo input;

	/* sprite list to draw */
	//SpriteGroup spriteListToDraw;

	/* sprite list to update*/
	//SpriteGroup spriteUpdateList;

	/* sprite list to update animation*/
	//SpriteGroup spriteAnimationList;
	
	/* you could have more lists of sprite pointers */
	/* such as spritesToUpdateForPhysics  
	   or      spritesToUpdateForCollisions 
	   etc....
    */

	/* timer's for rendering and animation/physics update */
	Timer *renderingTimer;
	Timer *updateTimer; // for physics/collisions etc.

	/* map for holding SpriteGroups that the sprites are using */
	//std::map<std::string, SpriteGroup> groups;

	/* list of sprites marked for destruction after the current update cycle */
	//std::vector<Sprite*> hitList;

	/* camera position */
	//double cameraX;
	//double cameraY;

private:
	void setWorldNow();
	void killWorldNow();

	World * currentWorld;
	World * newWorld;
	bool killWorld;
};
