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

#include "vectorMath.h"
#include "Hitbox.h"

// Forward Declarations -- allow me to refererence World and SpriteGroup before they are included.
//		this deals with otherwise circular dependancies
class World;
class SpriteGroup;

// This is the base class for every sprite in the game.
//  - use Sprite* pointers to handle arbitrary sprites
//  - see TextureSprite for the spritesheet and animation handling
//  - mostly inherit from TextureSprite, instead of Sprite directly
class Sprite
{
public:
	Sprite();
	virtual ~Sprite(void);

	// Override initialize() if the sprite has any set-up involving World * Sprite::world
	//		(i.e. adding itself to a group, accessing groups, accessing game state or input.)
	//  - You can not reference the world in the constructor, since the world can't set the sprite's world
	//		pointer until after it's constructed, but immediately before calling initialize().
	virtual void initialize(){}

	//  - The layerID determines the order sprites are drawn in, and thus what's in front of what.
	//  - Sprites with a higher layerID are drawn on top of those with a lower layerID.
	//  - If this is not called, the default layerID is 0.
	void setLayerID(float value) { layerID = value; }

	//  - Set the center of rotation, relative to the lower-left corner of the sprite.
	void setCenter(Vector2D v) { center = v; }
	void setCenter(float x, float y) { setCenter(Vector2D(x, y)); }

	//  - You can also set the positionX and positionY variables directly
	void setPosition(Vector2D v) { position = v; }
	void setPosition(float x, float y) { setPosition(Vector2D(x, y)); }

	//  - Orientation is in degrees, going counter-clockwise.
	void setOrientation(float theta) { this->theta = theta; }
	float getOrientation() {return theta;}

	//  - Set scrollFactor for parallax, and the illusion of depth.
	//  - It determermines the rate the sprite appears to as the camera moves.
	//  - i.e. a factor if 0 doesn't scroll, a factor of 0.5 scrolls at half speed (appearing to be in the background),
	//		a factor of 1 is normal, and a factor 2 would scroll at double speed (appearing to be in the foreground)
	void setScrollFactor(float x, float y) { scrollFactorX = x; scrollFactorY = y; }

	//  - Don't call this. It's called automatically when the sprite is added to the world, between the constructor and initialize()
	void setWorld(World *world) {this->world = world;}

	//  - Marks the sprite for deletion.
	//  - When kill() is called, the sprite is added to the world's hitList, and at the end of the frame
	//		it is completely removed from all groups, the destructor is called and the memory is freed.
	virtual void kill();

	//  - If you want, you can override this in order to provide your own drawing routines.
	//  - Can actually be safely called any time during the draw cycle (i.e. say, from the draw() methed of another sprite),
	//		although there's mostly no reason.
	//  - TextureSprite will handle it for you, although you can override the method and call TextureSprite::draw() if you
	//		want to do something fancy while still using the TextureSprite rendering
	virtual void draw(Vector2D camera) {}

	//	- Override this for any updates or changes to a sprite's state that you want to apply every frame.
	//		Which is most of them. (i.e. movement, collision, input handling, AI)
	virtual void update() {}

	//  - Updates the animation state of the sprite. TextureSprite will handle this for you.
	virtual void updateAnimation() {}

	// COLLISIONS //

	//  - If you pass the collision function a Sprite, it return true on collision and false otherwise.
	//  - If you pass it a group, it checks each member of the group and returns the sprite you collided with,
	//		or NULL if there are no collisions.
	//  - offsetX and offsetY are used to offset the position of this sprite while checking for collisions,
	//		in case you want to if this sprite WOULD collide if it were, say, just a few pixels this way.
	bool collide(Sprite*, const Vector2D &offset = Vector2D(0, 0));
	bool collide(Sprite*, double offsetX, double offsetY);
	Sprite * collide(SpriteGroup*, const Vector2D &offset = Vector2D(0, 0));
	Sprite * collide(SpriteGroup*, double offsetX, double offsetY);

	//	- These functions use the provided hitbox instead of the sprite's default one
	//	- hitbox position is still relative to the sprite
	bool relBoxCollide(Sprite*, const Hitbox &hitbox, const Vector2D &offset = Vector2D(0, 0));
	bool relBoxCollide(Sprite*, const Hitbox &hitbox, double offsetX, double offsetY);
	Sprite * relBoxCollide(SpriteGroup*, const Hitbox &hitbox, const Vector2D &offset = Vector2D(0, 0));
	Sprite * relBoxCollide(SpriteGroup*, const Hitbox &hitbox, double offsetX, double offsetY);

	//  - The moveCollide functions move the sprite by a certain amount, stopping if it collides,
	//		and returning the same way the collide() function does.
	bool moveCollideX(double x, Sprite*);
	bool moveCollideY(double y, Sprite*);
	bool moveCollide(double x, double y, Sprite*);
	bool moveCollide(const Vector2D &v, Sprite*);
	Sprite * moveCollideX(double x, SpriteGroup*);
	Sprite * moveCollideY(double y, SpriteGroup*);
	Sprite * moveCollide(double x, double y, SpriteGroup*);
	Sprite * moveCollide(const Vector2D &v, SpriteGroup*);
	bool collidePoint(double pointX, double pointY);
	bool collidePoint(Vector2D v);


	// GROUP STUFF //

	// There is more on groups in the SpriteGroup declaration at the bottom of this file

	//  - Check if the sprite is a member of a group
	bool inGroup(SpriteGroup *group);

	//  - Don't call this. It's remove the sprite from the draw() and update() groups as well, making it
	//		effectively disappear, but without freeing the memory. This will cause a momory leak.
	//  - It can only safely be called if you keep track of the sprite or handle the memory some other way.
	//		Normally it's only called by the destructor.
	void clearGroups();

	//  - Tools for iterating over groups the sprite is a member of.
	//  - begin(), end(), and Sprite::interator can be used the same as STL iterators
	typedef std::set<SpriteGroup*>::iterator iterator;
	iterator begin() {return groups.begin();}
	iterator end() {return groups.end();}


	// DATA //

	// The pointer to the parent World object.
	//  - This can be used to access various things, notably:
	//		- world->stateInfo, a struct with some info on the game and window state.
	//			You'll probably only have use of screenWidth, screenHeight, and maybe bgClearColor, if anything
	//		- world->input, a struct with information on the current input state (keyboard and mouse)
	//		- world->groups, a map of groups
	//	- See World.h for more information
	World *world;

	//  - hopefully self-explanatory, at least if you read the setter function comments above
	Vector2D position;
	Vector2D center;
	float theta;

	//	- Set this to determine whether the sprite is drawn horizontally mirrored.
	//	- This is (in affect) applied BEFORE rotation, and doesn't affect the direction it rotates.
	bool flipped;

	//  - scroll factors, which determine how much an oblect scrolls when the camera moves
	//		(0.5 scrolls half the distance, 2 is twice the distance)
	float scrollFactorX;
	float scrollFactorY;

	//  - which layer this sprite is on, lower is further away, 
	int layerID;

	//  - the sprite's hitbox - can be set along the lines of
	//			hitbox = Hitbox(lowerLeftX, lowerLeftY, width, height);
	Hitbox hitbox;

private:
	std::set<SpriteGroup*> groups;

	friend class SpriteGroup;
};

//  - SpriteGroups! These wonderfull things will help you manage your sprites, and help them reference eachother and interact.
//  - SpriteGroups are somewhat like standard containers, except when a sprite is deleted it automatically removes itself from
//		all containing groups and vice-versa, thus making them safer.
//	- Each World contains a mapping (map) of SpriteGroups, which can be used as a standardized form of access.
//		- SpriteGroups in the map can be accessed like so:
//				world->groups["groupname"];
//		- Thanks to the properties of maps, if you try to access a SpriteGroup which does not exist, an empty one is
//			initialized on the spot.
//		- So for a sprite to add itself to a group, regardless of whether said group actually exists:
//				world->groups["cheese"].add(this);
//		- To create a pointer to one of these groups:
//				SpriteGroup * cheeseGroup = &world->groups["cheese"];
//			(please use pointers, not references (just to set convention) and don't forget the reference operator (&)!)
//		- To iterate through all members of a group:
//				for (SpriteGroup::iterator it = world->groups["cheese"].begin(); it != world->groups["cheese"].end(); ++it)
//				{
//					// Do something
//				}
class SpriteGroup
{
public:
	SpriteGroup(){}
	~SpriteGroup();

	void add(Sprite *sprite);
	void remove(Sprite *sprite);

	//  - Check if the group contains a certain sprite
	bool contains(Sprite *sprite);
	
	//  - Remove every sprite. This can be called safely, if you're wondering from my rant on clearGroups()
	void clear();

	//  - Iterator stuff. Acts like the STL iterators.
	typedef std::list<Sprite*>::iterator iterator;
	iterator begin() {return sprites.begin();}
	iterator end() {return sprites.end();}

	unsigned int size() { return sprites.size(); }
	bool empty() { return sprites.empty(); }

	Sprite * front() { return sprites.front(); }
	Sprite * back() { return sprites.back(); }

	//  - This is just to allow for sorting.
	template <class Compare>
	void sort(Compare comp) {sprites.sort(comp);}

private:
	std::list<Sprite*> sprites;

	friend class Sprite;
};