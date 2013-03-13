// TextureSprite declarations and comments are down there somewhere

#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <set>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "Sprite.h"

// Forward Declaration
class Game;

//	- This is used in SpriteAnimation -- don't worry about it.
class XY_Coordinate
{
public:
	XY_Coordinate(float _x, float _y, float _u, float _v){ x=_x; y=_y; u = _u; v=_v;}
	~XY_Coordinate(){}
	float x,y;
	float u,v;
};

//	- This is used by TextureSprite, but you won't have to interface with it directly -- don't worry about it.
class SpriteAnimation 
{
public:
	SpriteAnimation(void)
	{
		currentFrame = 0;
		currentFrameRemainder = 0;
		doesLoop = true;
		speed = 1;
		flipped = false;
	}
	~SpriteAnimation(void){}
	
	void nextFrame()
	{
		int numFrames = coords.size();
		currentFrameRemainder += speed;
		while (currentFrameRemainder >= 1) {
			++currentFrame;
			--currentFrameRemainder;
		}
		if(currentFrame >= numFrames)
		{
			if(doesLoop) currentFrame = 0;
			else currentFrame = numFrames - 1;
		}
	}

	void setFrame(int frameNum)
	{
		currentFrame = frameNum % coords.size();
	}

	void setLooping(bool loop) {doesLoop = loop;}

	/* each animation has a list of x,y coordinates
	   that can be cycled through */
	std::vector<XY_Coordinate*> coords;
	bool doesLoop;
	int currentFrame;
	float currentFrameRemainder;
	float speed;
	bool flipped;
};

typedef struct _SpriteSheetInfo
{
	unsigned int textureID;
	float width,height;
}SpriteSheetInfo;

typedef struct _SpriteSize
{
	float width, height;
	float normalizedWidth,normalizedHeight;
}SpriteSize;

/* Sprite class
 * - this class takes care of everything
     related to sprites 
	 loading/drawing/setting states etc.
 */ 
class TextureSprite : public Sprite
{
public:
	TextureSprite(std::string spriteSheetFilename);
	virtual ~TextureSprite(void);

	//	- Load a sprite sheet.
	//	- Both the height and width should ideally be a power of two, i.e. 512x512 or 256x32
	//	- Required.
	void loadSpriteSheet(const char *filename);

	//	- Set the size of individual frames.
	//	- Required.
	void setSpriteFrameSize(int width, int height);

	//	- Make sure this is set right when you add a mess with the animations.
	//	- Required.
	void setNumberOfAnimations(int num);

	//	- animationNumber is how you always identify animations - each number refers to a seperate animation,
	//		right up to whatever you set in setNumberOfAnimations()
	//	- x and y are the position of the lower-left corner of the frame on the spritesheet.
	//	- You probably want at least one call to either this or addSpriteAnimRow()
	//	- You can combine the two methods -- addSpriteAnimRow() just calls addSpriteAnimFrame() repeatedly, anyways.
	void addSpriteAnimFrame(int animationNumber, int x, int y);

	//	- startX and startX are the position of the lower-left corner of the FIRST frame.
	//	- spacingX and spacingY are the difference in position between each frame.
	//		- If the frames are in a perfect row, spacingY should be 0.
	//		- If the frames are in a perfect column, spacingX should be 0.
	//	- numFrames is the number of frames to add. (duh)
	void addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames);

	//	- Set the speed that a particular animation plays at.
	//	- 1.0 is the game framerate (40fps) , 2.0 is twice the game framerate (80fps), 0.1 is 1/10 the game framerate (4fps), etc.
	void setAnimationSpeed(int animationNumber, float speed);


	virtual void draw(double cameraX = 0, double cameraY = 0);

	void setCurrentAnimation(int anim) {
		currentAnimation = anim;
		if(currentAnimation >= (int)animations.size()) currentAnimation = 0;
	}

	//	- Called by World.
	virtual void updateAnimation(){ animations[currentAnimation]->nextFrame(); }

	//	- Set the current frame of the current animation (be wary of out-of-bounds errors)
	void setFrame(int frameNum) { animations[currentAnimation]->setFrame(frameNum);}

	/* sprite info */
	SpriteSize sz;
	SpriteSheetInfo sheet;
	int numberOfAnimations;
	int currentAnimation;

	/* list of animations */
	std::vector<SpriteAnimation*> animations;
};