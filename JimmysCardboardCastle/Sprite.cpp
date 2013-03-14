#include "Sprite.h"
//#include "cmath"
#include "World.h"

/* THE SPRITE CLASS DEFINITION */
Sprite::Sprite()
{
	layerID = 0;
	theta = 0;
	centerX = centerY = 0;
	positionX = positionY = 0;
	scrollFactorX = scrollFactorY = 1;
	flipped = false;
	world = NULL;
}

Sprite::~Sprite(void)
{
	clearGroups();
}

void Sprite::kill()
{
	if (world) world->remove(this);
}

/* hitbox collision */
bool Sprite::collide(Sprite * sprite, double offsetX, double offsetY)
{
	return hitbox.collide(sprite->hitbox, sprite->positionX - positionX - offsetX, sprite->positionY - positionY - offsetY);
}

Sprite * Sprite::collide(SpriteGroup * group, double offsetX, double offsetY)
{
	for (SpriteGroup::iterator it = group->begin(); it != group->end(); ++it)
		if (collide(*it, offsetX, offsetY)) return *it;
	return NULL;
}

bool Sprite::moveCollideX(double x, Sprite * sprite)
{
	double oldX = positionX;
	double relX;
	positionX += x;
	if (collide(sprite)) {
		relX = sprite->positionX - positionX;
		if (x > 0) positionX = max(oldX, positionX + hitbox.distanceToRight(sprite->hitbox, relX));
		if (x < 0) positionX = min(oldX, positionX - hitbox.distanceToLeft(sprite->hitbox, relX));
		return true;
	}
	return false;
}

bool Sprite::moveCollideY(double y, Sprite * sprite)
{
	double oldY = positionY;
	double relY;
	positionY += y;
	if (collide(sprite)) {
		relY = sprite->positionY - positionY;
		if (y > 0) positionY = max(oldY, positionY + hitbox.distanceFromTop(sprite->hitbox, relY));
		if (y < 0) positionY = min(oldY, positionY - hitbox.distanceFromBottom(sprite->hitbox, relY));
		return true;
	}
	return false;
}

bool Sprite::moveCollide(double x, double y, Sprite * sprite)
{
	return (moveCollideX(x, sprite) || moveCollideY(y, sprite));
}

Sprite * Sprite::moveCollideX(double x, SpriteGroup * group)
{
	Sprite * returnSprite = NULL;
	double oldX = positionX;
	double relX;
	positionX += x;
	for (SpriteGroup::iterator it = group->begin(); it != group->end(); ++it) {
		Sprite * sprite = *it;
		if (collide(sprite)) {
			relX = sprite->positionX - positionX;
			if (x > 0) positionX = max(oldX, positionX + hitbox.distanceToRight(sprite->hitbox, relX));
			if (x < 0) positionX = min(oldX, positionX - hitbox.distanceToLeft(sprite->hitbox, relX));
			returnSprite = sprite;
			if (positionX == oldX) break;
		}
	}
	return returnSprite;
}

Sprite * Sprite::moveCollideY(double y, SpriteGroup * group)
{
	Sprite * returnSprite = NULL;
	double oldY = positionY;
	double relY;
	positionY += y;
	for (SpriteGroup::iterator it = group->begin(); it != group->end(); ++it) {
		Sprite * sprite = *it;
		if (collide(sprite)) {
			relY = sprite->positionY - positionY;
			if (y > 0) positionY = max(oldY, positionY + hitbox.distanceFromTop(sprite->hitbox, relY));
			if (y < 0) positionY = min(oldY, positionY - hitbox.distanceFromBottom(sprite->hitbox, relY));
			returnSprite = sprite;
			if (positionY == oldY) break;
		}
	}
	return returnSprite;
}

Sprite * Sprite::moveCollide(double x, double y, SpriteGroup * group)
{
	Sprite * returnSprite = NULL;
	if (Sprite * s = moveCollideX(x, group)) returnSprite = s;
	if (Sprite * s = moveCollideY(y, group)) returnSprite = s;
	return returnSprite;
}

bool Sprite::collidePoint(double pointX, double pointY)
{
	return hitbox.collidePoint(pointX - positionX, pointY - positionY);
};

/* group related stuff */
bool Sprite::inGroup(SpriteGroup *group)
{
	if (groups.find(group) != groups.end()) return true;
	return false;
}

void Sprite::clearGroups()
{
	for(iterator it = groups.begin(); it != groups.end();)
		(*it++)->remove(this);
}


SpriteGroup::~SpriteGroup()
{
	clear();
}
void SpriteGroup::add(Sprite *sprite)
{
	if (!sprite->inGroup(this)) {
		sprites.push_back(sprite);
		sprite->groups.insert(this);
	}
}
bool SpriteGroup::contains(Sprite *sprite)
{
	if (!sprite->inGroup(this)) return true;
	return false;
}
void SpriteGroup::remove(Sprite *sprite)
{
	sprites.remove(sprite);
	sprite->groups.erase(this);
}
void SpriteGroup::clear()
{
	for(iterator it = sprites.begin(); it != sprites.end(); ++it) {
		(*it)->groups.erase(this);
	}
	sprites.clear();
}