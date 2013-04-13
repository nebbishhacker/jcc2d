#pragma once
#include "Sprite.h"
#include "GameWorld.h"
#include "levelList.h"
#include "World.h"
#include "healthMilk.h"

class healthHandler : public Sprite
{
public:
	healthHandler(Player * t, int size) : Sprite()
	{
		p = t;
		milks = new healthMilk*[size];
		numMilks = size;
	};
	void initialize()
	{
		for (int _i = 0; _i < numMilks; _i++)
		{
			milks[_i] = new healthMilk();
			world->add(milks[_i]);
		}
	};
	void update()
	{
		for (int _i = 0; _i < numMilks; _i++)
		{
			milks[_i]->setPosition((p->position.x + 64*_i) - 325, p->position.y + 270);
		}
		if (p->health > 0)
		{
			int _i = (int)((p->health*2));
			while (_i > 0)
			{
				if (_i%2 == 1)
				{
					int x = _i+1;
					milks[x/2-1]->setFrame(_i%2);
				}
				else
				{
					milks[_i/2-1]->setFrame(_i%2);
					_i--;
				}
				_i--;
			}
			if (p->health < numMilks && (int)(p->health*2)%2 != 1)
				milks[(int)(p->health)]->setFrame(2);
		}
	};

	Player * p;
	healthMilk ** milks;
	int numMilks;
};