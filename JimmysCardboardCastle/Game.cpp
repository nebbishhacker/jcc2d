//#include "drawPrimitives.h"
#include "Game.h"

/* this is called by std::sort to sort the list based on layerID 
 *  for drawing in the proper order 
 */
//bool spriteSortingFunction(Sprite *s1, Sprite *s2)
//{
//	// return true if s1's layerID is less than s2's layerID
//	return (s1->layerID < s2->layerID);
//}

/* constructor */
Game::Game()
{
	/* green background */
	stateInfo.bgClearColor.red = 0.7;
	stateInfo.bgClearColor.green = 1;
	stateInfo.bgClearColor.blue = 1;

	/* init state */
	stateInfo.gameState = STATE_GAMEPLAY;
	renderingTimer = new Timer("RENDER");
	updateTimer = new Timer("UPDATE");
	//cameraX = 0;
	//cameraY = 0;
	//setWorld(world);

	currentWorld = newWorld = NULL;
	killWorld = false;
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

//void Game::loadLevel()
//{
//	add(new Player(200, 200));
//	//add(new CollTestBox(0, 0));
//	//add(new CollTestBox(400, 200));
//
//	add(new Background(0, -100, 825, 638, "images/ben_background(0.25scale).png", -100, 0.5, 0.25));
//
//	std::shared_ptr<TileSheet> tileSheet(new TileSheet(32, 32, 4, 1, "images/JCC_PlatSPR.png"));
//
//	for (int i = 0; i < 50; ++i) {
//		Tile * tempTile = new Tile(i * 32, 0, rand() % 4, tileSheet);
//		groups["ground"].add(tempTile);
//		add(tempTile);
//	}
//
//	for (int i = 1; i <= 50; ++i) {
//		Tile * tempTile = new Tile(0, i * 32, rand() % 4, tileSheet);
//		groups["ground"].add(tempTile);
//		add(tempTile);
//	}
//
//	for (int i = 1; i <= 50; ++i) {
//		Tile * tempTile = new Tile(i / 2 * 32 + 544, 170 + i % 2 * 32, rand() % 4, tileSheet);
//		groups["ground"].add(tempTile);
//		add(tempTile);
//	}
//}

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
	glEnable(GL_TEXTURE_2D); // turn on texturing

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

	glDisable(GL_TEXTURE_2D);
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

/* drawSprites()
 * - this function is what actually draws the sprites
 *   onto the screen at their appropriate location
 * - it actually loops through a list of active sprites
 *   and then sorts them by their layerID and then draws them
 * - the sorting has to happen so that you draw from back to front
 *   just like a painter and a canvas.
 */
//void Game::drawSprites()
//{
//	/* we could just do the following to draw the three sprites
//	   but that would be silly since we have a list of sprites to draw
//	   stored, so all we need to do is go through the list and draw eaach 
//	   sprite in the list */
//	/* // silly way 
//	testSprite->draw();
//	animatedSprite->draw();
//	animatedSprite2->draw();
//	*/
//	
//	/* better way */
//	/* this is better because it doesn't matter how many sprites we have, they will always be drawn */
//	SpriteGroup::iterator it; 
//	for(it = spriteListToDraw.begin(); it != spriteListToDraw.end();)
//	{
//		Sprite *s = (*it++);
//		s->draw(cameraX, cameraY);
//	}
//
//}

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

	if (currentWorld) {
		currentWorld->update();
		currentWorld->updateAnimation();
	}

	input.mousePressed = false;
	input.mouseReleased = false;

	for (int i = 0; i <  128; i++) input.keysPressed[i] = false;
	for (int i = 0; i <  128; i++) input.keysReleased[i] = false;

	//clearHitList(); //World's job

	/* you should probably update all of the sprites in a list just like the drawing */
	/* maybe two lists, one for physics updates and another for sprite animation frame update */
	/*testSprite->update();
	animatedSprite->update();
	animatedSprite->nextFrame();
	animatedSprite2->nextFrame();
	bg->update();

	std::vector<Sprite*>::iterator it; 
	for(it=testPlayerList.begin(); it != testPlayerList.end();it++)
	{
		(*it)->update();
		(*it)->nextFrame();
	}

	if (input.keysDown[32]) std::cout << "Space";*/
}

/* updateSprites()
 * - this function calls the update() function of all the sprites in the update list
 */
//void Game::updateSprites()
//{
//	SpriteGroup::iterator it; 
//	for(it=spriteUpdateList.begin(); it != spriteUpdateList.end();)
//	{
//		Sprite * s = *it++;
//		s->update();
//	}
//}

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

/*
 * add()
 * - adds a sprite to the draw list, the update list, etc.
 * - also sets this as the sprite's game
 * - and calls the sprite's initialize() method
 */
//void Game::add(Sprite *s)
//{
//	addSpriteToDrawList(s);
//	addSpriteToAnimationList(s);
//	addSpriteToUpdateList(s);
//	s->setGame(this);
//	s->initialize();
//}

/* 
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
//void Game::addSpriteToDrawList(Sprite *s)
//{
//	if(s)
//	{
//		/* push the sprite to the back of the list */
//		this->spriteListToDraw.add(s);
//	}
//}

/* 
 * addSpriteToUpdateList()
 * - this function simply pushes the sprite to the end of the list
 */
//void Game::addSpriteToUpdateList(Sprite *s)
//{
//	if(s)
//	{
//		/* push the sprite to the back of the list */
//		this->spriteUpdateList.add(s);
//	}
//}

/* 
 * addSpriteToAnimationList()
 * - this function simply pushes the sprite to the end of the list
 */
//void Game::addSpriteToAnimationList(Sprite *s)
//{
//	if(s)
//	{
//		/* push the sprite to the back of the list */
//		this->spriteAnimationList.add(s);
//	}
//}


/*
 * removeSprite()
 * - slates a sprite for deletion (adds to hitList)
 */
//void Game::remove(Sprite * sprite)
//{
//	hitList.push_back(sprite);
//}

/*
 * clearHitList()
 * - this function deletes and removing each member of the list of sprites slated for destruction
 */
//void Game::clearHitList()
//{
//	while (!hitList.empty()) {
//		delete hitList.back();
//		hitList.pop_back();
//	}
//}

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
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
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
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(1);
		break;
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
		if (!input.mouseDown) input.mousePressed = true;
		input.mouseDown = true;
		input.clickX = x*stateInfo.ratioWidth;
		input.clickY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
		input.button = button;

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
		
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		}
	}
	else
	{
		if (input.mouseDown) input.mouseReleased = true;
		input.mouseDown = false;
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
	input.currentX = x*stateInfo.ratioWidth;
	input.currentY = (stateInfo.windowHeight-y)*stateInfo.ratioHeight;
	//std::cout << input.currentX << " " << input.currentY << "\n";
}

//void Game::centerCamera(double x, double y)
//{
//	cameraX = x - stateInfo.screenWidth / 2;
//	cameraY = y - stateInfo.screenHeight / 2;
//}

//bool InputInfo::shiftDown()
//{
//	return glutGetModifiers() & GLUT_ACTIVE_SHIFT;
//}
//bool InputInfo::ctrlDown()
//{
//	return glutGetModifiers() & GLUT_ACTIVE_CTRL;
//}
//bool InputInfo::altDown()
//{
//	return glutGetModifiers() & GLUT_ACTIVE_ALT;
//}

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

void Game::setWorldNow()
{
	if (newWorld) {
		newWorld->nextWorldDown = currentWorld;
		currentWorld = newWorld;
		newWorld = NULL;
		currentWorld->initialize();
	}
}

void Game::killWorldNow()
{
	if (killWorld && currentWorld) {
		World * temp = currentWorld->nextWorldDown;
		delete currentWorld;
		currentWorld = temp;
	}
}