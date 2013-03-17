#include "TextureSprite.h"
#include "cmath"
#include "Game.h"
#include "TextureCache.h"

/* THE SPRITE CLASS DEFINITION */
TextureSprite::TextureSprite(std::string spriteSheetFilename)
{
	this->loadSpriteSheet(spriteSheetFilename.c_str());
	currentAnimation = 0;
}

TextureSprite::~TextureSprite(void)
{
	while (!animations.empty()) {
		delete animations.back();
		animations.pop_back();
	}
}

void TextureSprite::loadSpriteSheet(const char *filename)
{
	sheet.textureID = textureCache.loadTexture((char*)filename);//ilutGLLoadImage((char*)filename);
	sheet.width = textureCache.getWidth(sheet.textureID);//ilGetInteger(IL_IMAGE_WIDTH);
	sheet.height = textureCache.getHeight(sheet.textureID);//ilGetInteger(IL_IMAGE_HEIGHT);
}

void TextureSprite::setSpriteFrameSize(int width, int height)
{
	sz.width = width;
	sz.height = height;
	sz.normalizedWidth = (float)width/(float)sheet.width;
	sz.normalizedHeight = (float)height/(float)sheet.height;
}

void TextureSprite::setNumberOfAnimations(int num)
{
	numberOfAnimations = num;
	animations.reserve(num);
	for(int i=0;i<num;i++)
	{
		SpriteAnimation *anim = new SpriteAnimation();
		animations.push_back(anim);
	}
}

/*
 * addSpriteAnimFrame()
 *  - this adds a sprite animation frame to the end of the particular animation list
 *  - (x,y) specify the pixel values of the bottom left corner of the frame
 *  - animationNumber specifies which animation (i.e. JUMP, RUN, etc)
 *    you could use enum's for easier coding 
 */
void TextureSprite::addSpriteAnimFrame(int animationNumber, int x, int y)
{
	float u,v;
	u = (float)x/sheet.width;
	v = (float)y/sheet.height;

	XY_Coordinate *xy = new XY_Coordinate(x,y, u,v);
	animations[animationNumber]->coords.push_back(xy);
}

void TextureSprite::addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames)
{
	float x,y;
	x = startX;
	y = startY;
	for(int i=0;i<numFrames;i++)
	{
		addSpriteAnimFrame(animationNumber, x,y);
		x += spacingX;
		y += spacingY;
	}
}

void TextureSprite::setAnimationSpeed(int animationNumber, float speed)
{
	animations[animationNumber]->speed = speed;
}

/*
 * draw()
 * - this draws the sprite texture at its current frame of its current animation
 * - it positions the sprite based on the transformation formula:
 *    v' = RotationMatrix*(v-center) + position
 * where position is the bottom left corner of the sprite
 * and v is each corner of the sprite rectangle, v' is the transformed corner
 * and RotationMatrix is defined by the sprite's theta value (counter clockwise)
 */
void TextureSprite::draw(double cameraX, double cameraY)
{
	/* draw the sprite */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();

	/* position the sprite into the particular pixel location */
	glTranslatef(positionX - cameraX * scrollFactorX, positionY - cameraY * scrollFactorY, 0);

	// apply the rotation around the center of the sprite
	glTranslatef(centerX,centerY,0);
	glRotatef(theta, 0,0,1);
	glTranslatef(-centerX,-centerY,0);

	/* get the texture coordinate from the sprite so we know which frame to draw */
	SpriteAnimation *anim = animations[currentAnimation];
	int currentFrame = anim->currentFrame;
	float u,v;
	u = anim->coords[currentFrame]->u;
	v = anim->coords[currentFrame]->v;
	bool f = anim->flipped != this->flipped;

	glColor3f(1,1,1);
		/* bind the appropriate texture frame */
		glBindTexture(GL_TEXTURE_2D,sheet.textureID);
		/* Make texture scaling pixelly */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		/* draw the image as a quad the size of the first loaded image */
		glBegin(GL_QUADS);
		    glTexCoord2f(u+sz.normalizedWidth*f,v);
			glVertex3f(0,0,0);
			
			glTexCoord2f(u+sz.normalizedWidth*f,v+sz.normalizedHeight);
			glVertex3f(0,sz.height,0);
			
			glTexCoord2f(u+sz.normalizedWidth*!f,v+sz.normalizedHeight);
			glVertex3f(sz.width,sz.height,0);
			
			glTexCoord2f(u+sz.normalizedWidth*!f,v);
			glVertex3f(sz.width,0,0);
		glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}