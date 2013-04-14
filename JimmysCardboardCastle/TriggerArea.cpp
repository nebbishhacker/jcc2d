#pragma once
#include "TriggerArea.h"
#include "World.h"

void TriggerArea::update()
{
	if (collide(&world->groups[targetGroup]))
		world->groups[groupToAdd].add(this);
	else world->groups[groupToAdd].remove(this);
}