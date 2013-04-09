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
void TextureSprite::draw(Vector2D camera)
{
	glEnable(GL_TEXTURE_2D); // turn on texturing

	/* draw the sprite */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();

	/* create the drawing tranformation matrix */
	Matrix2x2 matrix(1, 0, 0, 1); // identity matrix
	if (flipped) matrix *= Matrix2x2(-1, 0, 0, 1); // if the image is flipped, multiply by a horizontal reflection matrix
	matrix *= Matrix2x2(cos(theta), sin(theta), -sin(theta), cos(theta)); // multiply by a rotation matrix
	
	/* find pixel location */
	Vector2D screenPos = position + center - getScrollMatrix() * camera; // scrollMatrix is used for parallax scrolling

	/* find the corner points of the image */
	Vector2D p00 = (matrix * Vector2D(-center.x, -center.y)) + screenPos;
	Vector2D p01 = (matrix * Vector2D(-center.x, sz.height - center.y)) + screenPos;
	Vector2D p10 = (matrix * Vector2D(sz.width - center.x, sz.height - center.y)) + screenPos;
	Vector2D p11 = (matrix * Vector2D(sz.width - center.x, -center.y)) + screenPos;

	/* get the texture coordinate from the sprite so we know which frame to draw */
	SpriteAnimation *anim = animations[currentAnimation];
	int currentFrame = anim->currentFrame;
	float u,v;
	u = anim->coords[currentFrame]->u;
	v = anim->coords[currentFrame]->v;

	glColor3f(1,1,1);
		/* bind the appropriate texture frame */
		glBindTexture(GL_TEXTURE_2D,sheet.textureID);
		/* Make texture scaling pixelly */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		/* draw the image as a quad the size of the first loaded image */
		glBegin(GL_QUADS);
		    glTexCoord2f(u,v);
			glVertex3f(p00.x,p00.y,0);
			
			glTexCoord2f(u,v+sz.normalizedHeight);
			glVertex3f(p01.x,p01.y,0);
			
			glTexCoord2f(u+sz.normalizedWidth,v+sz.normalizedHeight);
			glVertex3f(p10.x,p10.y,0);
			
			glTexCoord2f(u+sz.normalizedWidth,v);
			glVertex3f(p11.x,p11.y,0);
		glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
}