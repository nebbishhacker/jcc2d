#include "TilePlacer.h"
#include "Game.h"
#include "drawPrimitives.h"

void TilePlacer::update()
{
	float currX = world->input->currentX + world->cameraX * scrollFactorX;
	float currY = world->input->currentY + world->cameraY * scrollFactorY;

	positionX = currX - tileSheet->tileWidth / 2;
	positionY = currY - tileSheet->tileHeight / 2;

	if (world->input->mouseDown)
	{
		// Add (or replace) a tile
		int tX = currX / tileSheet->tileWidth;
		int tY = currY / tileSheet->tileHeight;

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
		int tX = currX / tileSheet->tileWidth;
		int tY = currY / tileSheet->tileHeight;

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
	if (world->input->keysPressed['d']) {
		tileType.c -= 1;
		if (tileType.c < 0) tileType.c += tileMapData->sheetWidth;
	}
	if (world->input->keysPressed['a']) {
		tileType.c += 1;
		if (tileType.c >= tileMapData->sheetWidth) tileType.c -= tileMapData->sheetWidth;
	}
	if (world->input->keysPressed['w']) {
		tileType.r -= 1;
		if (tileType.r < 0) tileType.r += tileMapData->sheetHeight;
	}
	if (world->input->keysPressed['s']) {
		tileType.r += 1;
		if (tileType.r >= tileMapData->sheetHeight) tileType.r -= tileMapData->sheetHeight;
	}
}
void TilePlacer::draw(double cameraX, double cameraY)
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
				tileSheet->setPosition(positionX + (c - tileType.c) * (tileMapData->tileWidth + 3), positionY + (r - tileType.r) * (tileMapData->tileHeight + 3));
				tileSheet->draw(cameraX, cameraY);
			}
		}
	}
	else
	{
		// draw the current tile
		tileSheet->setFrame(tileType.r * tileMapData->sheetWidth + tileType.c);
		tileSheet->setPosition(positionX, positionY);
		tileSheet->draw(cameraX, cameraY);
	}
}