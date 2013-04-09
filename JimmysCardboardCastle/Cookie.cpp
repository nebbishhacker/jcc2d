#include "Cookie.h"
#include "Game.h"
#include "Player.h"

#include <random>

Cookie::Cookie(double x, double y) : TextureSprite("images/spr_cookiescore.png")
{
	setPosition(x, y);

	// animations, even though there's only one.
	// 0 - sparkling cookie

	// ANIMATION SETUP //
	setNumberOfAnimations(1);
	setSpriteFrameSize(32, 32);

	addSpriteAnimRow(0, 0, 0, 32, 0, 7); // first, and only animation
	setAnimationSpeed(0, 0.25);

	setCurrentAnimation(0);

	hitbox = Hitbox(0, 0, 32, 32);
}

/*void Cookie::initialize();
{
Left out because the cookie doesn't currently need to use the "ground" group.
}*/

void Cookie::update()
{
	Sprite * s = collide(&world->groups["player"]);
	if (s != NULL)
	{
		Player * p = static_cast<Player*>(s);
		++p->score;
		this->kill();
	}
}