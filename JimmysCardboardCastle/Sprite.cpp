#include "Sprite.h"
//#include "cmath"
#include "World.h"

/* THE SPRITE CLASS DEFINITION */
Sprite::Sprite()
{
	layerID = 0;
	theta = 0;
	center = Vector2D(0, 0);
	position = Vector2D(0, 0);
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
bool Sprite::collide(Sprite * sprite, const Vector2D &offset)
{
	return hitbox.collide(sprite->hitbox, sprite->position - position - offset);
}
bool Sprite::collide(Sprite * sprite, double offsetX, double offsetY)
{
	return collide(sprite, Vector2D(offsetX, offsetY));
}

Sprite * Sprite::collide(SpriteGroup * group, const Vector2D &offset)
{
	for (SpriteGroup::iterator it = group->begin(); it != group->end(); ++it)
		if (collide(*it, offset)) return *it;
	return NULL;
}
Sprite * Sprite::collide(SpriteGroup * group, double offsetX, double offsetY)
{
	return collide(group, Vector2D(offsetX, offsetY));
}

bool Sprite::moveCollideX(double x, Sprite * sprite)
{
	double oldX = position.x;
	double relX;
	position.x += x;
	if (collide(sprite)) {
		relX = sprite->position.x - position.x;
		if (x > 0) position.x = max(oldX, position.x + hitbox.distanceToRight(sprite->hitbox, relX));
		if (x < 0) position.x = min(oldX, position.x - hitbox.distanceToLeft(sprite->hitbox, relX));
		return true;
	}
	return false;
}

bool Sprite::moveCollideY(double y, Sprite * sprite)
{
	double oldY = position.y;
	double relY;
	position.y += y;
	if (collide(sprite)) {
		relY = sprite->position.y - position.y;
		if (y > 0) position.y = max(oldY, position.y + hitbox.distanceFromTop(sprite->hitbox, relY));
		if (y < 0) position.y = min(oldY, position.y - hitbox.distanceFromBottom(sprite->hitbox, relY));
		return true;
	}
	return false;
}

bool Sprite::moveCollide(double x, double y, Sprite * sprite)
{
	return (moveCollideX(x, sprite) || moveCollideY(y, sprite));
}
bool Sprite::moveCollide(const Vector2D &v, Sprite * sprite)
{
	return moveCollide(v.x, v.y, sprite);
}

Sprite * Sprite::moveCollideX(double x, SpriteGroup * group)
{
	Sprite * returnSprite = NULL;
	double oldX = position.x;
	double relX;
	position.x += x;
	for (SpriteGroup::iterator it = group->begin(); it != group->end(); ++it) {
		Sprite * sprite = *it;
		if (collide(sprite)) {
			relX = sprite->position.x - position.x;
			if (x > 0) position.x = max(oldX, position.x + hitbox.distanceToRight(sprite->hitbox, relX));
			if (x < 0) position.x = min(oldX, position.x - hitbox.distanceToLeft(sprite->hitbox, relX));
			returnSprite = sprite;
			if (position.x == oldX) break;
		}
	}
	return returnSprite;
}

Sprite * Sprite::moveCollideY(double y, SpriteGroup * group)
{
	Sprite * returnSprite = NULL;
	double oldY = position.y;
	double relY;
	position.y += y;
	for (SpriteGroup::iterator it = group->begin(); it != group->end(); ++it) {
		Sprite * sprite = *it;
		if (collide(sprite)) {
			relY = sprite->position.y - position.y;
			if (y > 0) position.y = max(oldY, position.y + hitbox.distanceFromTop(sprite->hitbox, relY));
			if (y < 0) position.y = min(oldY, position.y - hitbox.distanceFromBottom(sprite->hitbox, relY));
			returnSprite = sprite;
			if (position.y == oldY) break;
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
Sprite * Sprite::moveCollide(const Vector2D &v, SpriteGroup* group)
{
	return moveCollide(v.x, v.y, group);
}

bool Sprite::collidePoint(Vector2D point)
{
	return hitbox.collidePoint(point - position);
};
bool Sprite::collidePoint(double pointX, double pointY)
{
	return hitbox.collidePoint(pointX - position.x, pointY - position.y);
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