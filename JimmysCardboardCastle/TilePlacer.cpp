#include "TilePlacer.h"
#include "Game.h"
#include "drawPrimitives.h"
#include "convert.h"

void TilePlacer::update()
{
	Vector2D cam(world->camera.x * scrollFactorX, world->camera.y * scrollFactorY);
	Vector2D curr = world->input->current + cam;

	position.x = curr.x - tileSheet->tileWidth / 2;
	position.y = curr.y - tileSheet->tileHeight / 2;

	if (world->input->mouseDown)
	{
		// Add (or replace) a tile
		int tX = curr.x / tileSheet->tileWidth;
		int tY = curr.y / tileSheet->tileHeight;

		if (tX >= 0 && tY >= 0) {
			tileMapData->prepTile(tX, tY);

			if (tileMapData->data[tY][tX].entity != NULL) {
				tileMapData->data[tY][tX].entity->kill();
				tileMapData->data[tY][tX].entity = NULL;
			}
			Tile * t = new Tile(tX * tileSheet->tileWidth, tY * tileSheet->tileHeight, tileType.r * tileMapData->sheetWidth + tileType.c, tileSheet);
			tileMapData->data[tY][tX].entity = t;
			tileMapData->data[tY][tX].c = tileType.c;
			tileMapData->data[tY][tX].r = tileType.r;
			tileMapData->data[tY][tX].exists = true;
			world->groups["ground"].add(t);
			world->add(t);
		}
	}
	else if (world->input->rightMouseDown)
	{
		// remove a tile
		int tX = curr.x / tileSheet->tileWidth;
		int tY = curr.y / tileSheet->tileHeight;

		if (tX >= 0 && tY >= 0) {
			tileMapData->prepTile(tX, tY);

			if (tileMapData->data[tY][tX].entity != NULL) {
				tileMapData->data[tY][tX].entity->kill();
				tileMapData->data[tY][tX].entity = NULL;
			}
			tileMapData->data[tY][tX].c = -1;
			tileMapData->data[tY][tX].r = -1;
			tileMapData->data[tY][tX].exists = false;
		}
	}
	if (world->input->keysPressed['a']) {
		tileType.c -= 1;
		if (tileType.c < 0) tileType.c += tileMapData->sheetWidth;
	}
	if (world->input->keysPressed['d']) {
		tileType.c += 1;
		if (tileType.c >= tileMapData->sheetWidth) tileType.c -= tileMapData->sheetWidth;
	}
	if (world->input->keysPressed['s']) {
		tileType.r -= 1;
		if (tileType.r < 0) tileType.r += tileMapData->sheetHeight;
	}
	if (world->input->keysPressed['w']) {
		tileType.r += 1;
		if (tileType.r >= tileMapData->sheetHeight) tileType.r -= tileMapData->sheetHeight;
	}
}
void TilePlacer::draw(Vector2D camera)
{
	if (world->input->keysDown[' '])
	{
		// draw a semitransparent black fill
		setColor(0, 0, 0, 0.5);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		drawRectangle(true, 0, 0, world->stateInfo->screenWidth, world->stateInfo->screenHeight, 0);
		glDisable(GL_BLEND);

		// draw the tilesheet
		for (int c = 0; c < tileMapData->sheetWidth; ++c)
		{
			for (int r = 0; r < tileMapData->sheetHeight; ++r)
			{
				tileSheet->setFrame(r * tileMapData->sheetWidth + c);
				tileSheet->setPosition(position.x + (c - tileType.c) * (tileMapData->tileWidth + 3), position.y + (r - tileType.r) * (tileMapData->tileHeight + 3));
				tileSheet->draw(camera);
			}
		}
	}
	else
	{
		// draw the current tile
		tileSheet->setFrame(tileType.r * tileMapData->sheetWidth + tileType.c);
		tileSheet->setPosition(position);
		tileSheet->draw(camera);
	}

	setColor(1, 1, 1);
	drawRectangle(true, world->stateInfo->screenWidth - 160, 0, world->stateInfo->screenWidth, 25, 0);

	setColor(0, 0, 0);
	drawText(stringify(world->input->current.x - world->camera.x) + ", " + stringify(world->input->current.y - world->camera.y), world->stateInfo->screenWidth - 150, 5);
}