#include "Button.h"
#include "Game.h"

void Button::update()
{
	if (world)
		if (world->input->mousePressed && collidePoint(world->input->clickX, world->input->clickY))
			callback();
}