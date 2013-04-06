#include "Game.h"

#include "drawPrimitives.h"
#include "convert.h"

/* constructor */
Game::Game()
{
	/* green background */
	stateInfo.bgClearColor.red = 0.7;
	stateInfo.bgClearColor.green = 1;
	stateInfo.bgClearColor.blue = 1;

	/* init state */
	renderingTimer = new Timer("RENDER");
	updateTimer = new Timer("UPDATE");
	//cameraX = 0;
	//cameraY = 0;
	//setWorld(world);

	currentWorld = newWorld = NULL;
	killWorld = false;

	fpsCounterOn = false;
}

/* destructor */
Game::~Game()
{
	delete renderingTimer;
	delete updateTimer;
	delete currentWorld;
	/* deallocate memory and clean up here. if needed */
}

/* 
 * initializeGame()
 * - this function is called in the constructor to initialize everything related
 *   to the game, i..e loading sprites etc.
 * - MUST be called prior to any drawing/updating (you should add in checks to ensure this occurs in the right order)
 */
void Game::initializeGame()
{
	//loadLevel();
	//setWorld(new TestWorld(this));
	killWorldNow();
	setWorldNow();
}

/* draw()
 * - this gets called automatically about 30 times per second
 * - this function just draws the sprites 
 */
void Game::draw()
{
	/* pre-draw - setup the rendering */
	PreDraw();

	/* draw - actually render to the screen */
	DrawGame();
	
	/* post-draw - after rendering, setup the next frame */
	PostDraw();
}

/*
 * Pre-Draw() is for setting up things that need to happen in order to draw
 *    the game, i.e. sorting, splitting things into appropriate lists etc.
 */
void Game::PreDraw()
{
	/* clear the screen */
	glViewport(0,0,stateInfo.windowWidth,stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red, 
				 stateInfo.bgClearColor.green, 
				 stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // clear out the transformation matrix

	// if we update our timer it will tell us the elapsed time since the previous 
	// frame that we rendered
	renderingTimer->tick();


	/* sort the sprites by layerID so we draw them in the right order */
	/* World does this now */
	//spriteListToDraw.sprites.sort(spriteSortingFunction);

}

/* 
 * DrawGame()
 *  - this is the actual drawing of the current frame of the game.
 */
void Game::DrawGame()
{
	/* here is where your drawing stuff goes */
	if (currentWorld) currentWorld->draw();

	if (fpsCounterOn) {
		setColor(0, 0, 0);
		drawText("Update: " + stringify(1000 / updateTimer->getElapsedTimeMS()), 2, 2);
		drawText("Render: " + stringify(1000 / renderingTimer->getElapsedTimeMS()), 2, 22);
	}
	//drawTestPrimitives();

	/* this makes it actually show up on the screen */
	glutSwapBuffers();
}

/*
 * PostDraw()
 *  - in here you should clean up and set up things for the next frame
 *  - i.e. once I've used my assets, I can change them to set up things for
 *    the next frame, usually just memory management or setting up game state 
 *    boolean values etc.  
 */
void Game::PostDraw()
{
	// nothing here at the moment
}

/* for testing purposes to show you how to use
   the drawing primitives capabilities */
//void Game::drawTestPrimitives()
//{
//	/* draw line */
//	setLineWidth(5.f);
//	setColor(1,0,0);
//	drawLine(100,100,200,200);
//	setLineWidth(1.f);
//
//	/* draw rectangle */
//	setColor(1,1,0);
//	drawRectangle(true, 200,200,50,50,45.f);
//
//	/* draw circle */
//	setLineWidth(5.f);
//	setColor(0,1,1);
//	drawCircle(20, 50, 200,200);
//	drawFilledCircle(20,50,500,200);
//	setLineWidth(1.f);
//
//	/* draw triangle */
//	setColor(0.5,0,0.5);
//	drawTriangle(true, 100,100,200,200,300,100);
//
//	/* draw text */
//	setColor(1,1,1);
//	drawText("HELLO WORLD",200,200);
//}

/* update()
  - this function is essentially the game loop
    it gets called often and as such you
	don't actually need a "loop" to define the game
	it happens behind the scenes
  - think of this function as one iteration of the game loop
  - if you need to update physics calculations, sprite animation info,
    or sound etc, it goes in here
*/
void Game::update()
{
	// update our clock so we have the delta time since the last update
	updateTimer->tick();
	
	killWorldNow();
	setWorldNow();

	if (!currentWorld) exit(0);
	else {
		currentWorld->update();
		currentWorld->updateAnimation();
	}

	input.mousePressed = false;
	input.mouseReleased = false;

	for (int i = 0; i <  128; i++) input.keysPressed[i] = false;
	for (int i = 0; i <  128; i++) input.keysReleased[i] = false;
}

/* updateAnimation()
 * - this function calls the nectFrame() function of all the sprites in the animation list
 */
void Game::updateAnimation()
{
	//SpriteGroup::iterator it; 
	//for(it=spriteAnimationList.begin(); it != spriteAnimationList.end(); it)
	//{
	//	(*it++)->nextFrame();
	//}

	if (currentWorld) currentWorld->updateAnimation();
}


/*************************************************/
/* INPUT - keyboard/mouse functions below        */
/*************************************************/
/* keyboardDown()
   - this gets called when you press a key down
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	// set lowercase version
	key = std::tolower(key);
	if (!input.keysDown[key]) input.keysPressed[key] = true; 
	input.keysDown[key] = true;

	// set uppercase version
	key = std::toupper(key);
	if (!input.keysDown[key]) input.keysPressed[key] = true; 
	input.keysDown[key] = true;

	switch(key)
	{
	case '\t':
		fpsCounterOn = !fpsCounterOn;
		break;
	case 32: // the space bar
		break;
	//case 27: // the escape key
	//case 'q': // the 'q' key
	//	exit(1);
	//	break;
	}
}
/* keyboardUp()
   - this gets called when you lift a key up
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	// set lowercase version
	key = std::tolower(key);
	if (input.keysDown[key]) input.keysReleased[key] = true; 
	input.keysDown[key] = false;

	// set uppercase version
	key = std::toupper(key);
	if (input.keysDown[key]) input.keysReleased[key] = true; 
	input.keysDown[key] = false;

	switch(key)
	{
	case 32: // the space bar
		break;
	//case 27: // the escape key
	//case 'q': // the 'q' key
	//	exit(1);
	//	break;
	}
}

/* specialDown()
   - this gets called when you press a special key down
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
   - the key argument will be one of the GLUT_KEY_* constants, ie. GLUT_KEY_F1, GLUT_KEY_PAGE_DOWN, etc.
*/
void Game::specialDown(int key, int mouseX, int mouseY)
{
	// sets the key as being down
	input.specialsDown[key] = true;
}

/* specialUp()
   - this gets called when you lift a special key up
   - you are given the key that was pressed
     and where the (x,y) location of the mouse is when pressed
*/
void Game::specialUp(int key, int mouseX, int mouseY)
{
	// sets the key as being down
	input.specialsDown[key] = false;
}

/*
 * mouseClicked
 * - this function is called when the mouse is clicked and it handles the 
 *   input state managment
 */
void Game::mouseClicked(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN) 
	{

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			if (!input.mouseDown) input.mousePressed = true;
			input.mouseDown = true;
			input.click.x = x*stateInfo.ratioWidth;
			input.click.y = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
			input.button = button;
			break;
		case GLUT_RIGHT_BUTTON:
			if (!input.rightMouseDown) input.rightMousePressed = true;
			input.rightMouseDown = true;
			input.rightClick.x = x*stateInfo.ratioWidth;
			input.rightClick.y = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
			input.button = button;
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
	}
	else
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			if (input.mouseDown) input.mouseReleased = true;
			input.mouseDown = false;
			break;
		case GLUT_RIGHT_BUTTON:
			if (input.rightMouseDown) input.rightMouseReleased = true;
			input.rightMouseDown = false;
			break;
		}
	}

}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus 
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
	/* convert from window to screen pixel coordinates */
	input.current.x = x*stateInfo.ratioWidth;
	input.current.y = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
	//std::cout << input.currentX << " " << input.currentY << "\n";
}

void Game::setNewWorld(World * world)
{
	if (!killWorld && !newWorld) {
		world->stateInfo = &stateInfo;
		world->input = &input;
		world->game = this;
		newWorld = world;
	}
	else delete world;
}

void Game::killCurrentWorld()
{
	if (!newWorld) killWorld = true;
}

void Game::replacingCurrentWorld(World * world)
{
	if (!killWorld && !newWorld) {
		world->stateInfo = &stateInfo;
		world->input = &input;
		world->game = this;
		newWorld = world;
		killWorld = true;
	}
	else delete world;
}

bool Game::setWorldNow()
{
	if (newWorld) {
		newWorld->nextWorldDown = currentWorld;
		currentWorld = newWorld;
		newWorld = NULL;
		currentWorld->initialize();
		return true;
	}
	return false;
}

bool Game::killWorldNow()
{
	if (killWorld && currentWorld) {
		World * temp = currentWorld->nextWorldDown;
		delete currentWorld;
		currentWorld = temp;
		killWorld = NULL;
		return true;
	}
	return false;
}