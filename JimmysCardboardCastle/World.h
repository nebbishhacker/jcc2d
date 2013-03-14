#pragma once

#include <map>
#include <string>
#include <vector>

#include "Sprite.h"

// Forward declarations
class Game;
typedef struct _GameStateInfo GameStateInfo;
typedef struct _InputInfo InputInfo;

// This is the base class for "World" objects
//	- These are the objects that handle sprites, input, drawlists etc. but can be easily swapped out
//		with each other, thus conveniently changing the overall gamestate without worring too much about
//		cleanup etc, and without necessarily destroying the previous state.
//	- A World would be along the lines of a single level, a single menu screen, a single segment of cutscene etc.
//	- Worlds are handled as a stack.
//	- When you add a new world, it goes on top of the stack and recieves control.
//	- When you delete the current world, the world underneath it is handed control nd takes over. This is useful
//		for returning to the main menu when you exit a submenu or quit a game, or for returning to the game when
//		exiting the pause menu.
//  - If you want to replace the current world so that control doesn't return to it when the new world is deleted,
//		you can do that out instead of just adding the new one to the top of the stack.
//	- You can change the current world by calling the appropriate methods of Game:
//		- game->setNewWorld(World * world);		// adds world to the top of the stack, and hands it control
//		- game->killCurrentWorld();				// destroys the current world, handing control to the one under it
//		- replacingCurrentWorld(World * world);	// destroys the current world, adds the new world to the top of the
//			stack, and hands it control
//		(these methods are all actually delayed 'till the end of the frame)
class World
{
public:
	//	- Subclasses should almost always provide their own constructor and/or override initialize
	World();
	virtual ~World();

	//	- Override this if you need access to game, stateInfo, or input for you initialization.
	//  - between the constructor and initialize the world should do all it's initial setup, such as loading the
	//		level, adding menu button sprites, adding the hud sprites (if the hud uses sprites?), or whatever, as
	//		appropriate
	virtual void initialize(){};

	//	- add(s) calls addToDrawList(s), addToUpdateList(s), and addToAnimationList(s).
	//	- All of these use SpriteGroups internally, which are particular to the current World (not handled by Game)
	void add(Sprite *s);
	void addToDrawList(Sprite *s);
	void addToUpdateList(Sprite *s);
	void addToAnimationList(Sprite *s);

	//	- These all just iterate through the appropriate list of sprites and call the appropriate methods on the sprites
	//		(pre-draw and post-draw stuff is handled by Game)
	//	- You can override these, if given reason; for instance, you could override draw() to call the draw method of
	//		the next world down before calling it's own World::draw(), thus drawing the previous world below the current
	//		one (handy for pause menus that overlay the gameplay screen instead of replacing it)
	virtual void draw();
	virtual void update();
	virtual void updateAnimation();

	//  - When remove() is called, the sprite is added to the world's hitList, and at the end of the frame
	//		it is completely removed from all groups, the destructor is called and the memory is freed.
	void remove(Sprite*);

	//	- Centers the camera on the given position. (duh)
	void centerCamera(double x = 0, double y = 0);

	// DATA //

	//	- stateInfo is a struct providing the following data:
	//		- int gameState						// I have no plans to use this. I may get rid of it.
	//		- RGBColor bgClearColor				// Background colour, essentially.
	//			- float red;
	//			- float green;
	//			- float blue;
	//		- int windowWidth, windowHeight;	// Size of the window -- you probably want the screen size, not the window size.
	//		- int screenWidth, screenHeight;	// Size of the screen -- useful for huds and layouts
	//		- float ratioWidth,ratioHeight;		// ...I'm not actually sure. Huh.
	GameStateInfo * stateInfo;

	//	- input struct providing the following data:
	//		- bool mouseDown;			// is the mouse down?
	//		- int button;				// which mouse button (can be GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON, I think)
	//		- float clickX,clickY;		// where the mouse was clicked
	//		- float currentX,currentY;	// where the mouse is right now
	//									// I plan to add more boolean values, for whether the mouse was pressed just now and stuff
	//		- bool keysDown[128];		// array of boolean keystates, for tracking whether each key is down
	//										usage: if (input->keysDown['a']) /* do something */;
	//		- bool specialsDown[128];	// array of boolean keystates, for tracking whether each special key is down
	//										usage: if (input->specialsDown[GLUT_KEY_UP]) /* do something */;
	InputInfo * input;

	//	- The map of SpriteGroups
	//	- There's a description of how to access this at the bottom of Sprite.h with the SpriteGroup declaration, which I didn't feel like
	//		copying or moving
	std::map<std::string, SpriteGroup> groups;

	//	- This points to the next world down in the stack. You can access the pointer (don't depend on it, make sure it's not NULL), but
	//		please don't try to modify it.
	World * nextWorldDown;

	//	- Camera position.
	//	- Be aware that this is the position of the bottom-left corner, not the center.
	double cameraX;
	double cameraY;

private:
	void executeHitList();

	SpriteGroup drawList;
	SpriteGroup updateList;
	SpriteGroup animationList;

	std::vector<Sprite*> hitList;
};