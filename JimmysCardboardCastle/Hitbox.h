#pragma once

#include "vectorMath.h"

struct Hitbox
{
	Vector2D size;
	Vector2D position;
	
	Hitbox() {}
	Hitbox(Vector2D position, Vector2D size)
	{
		this->position = position;
		this->size = size;
	}
	Hitbox(double x, double y, double width, double height)
	{
		position = Vector2D(x, y);
		size = Vector2D(width, height);
	}

	bool collide(Hitbox &b, const Vector2D &rel)
	{
		return !(position.x + size.x <= b.position.x + rel.x ||
			position.y + size.y <= b.position.y + rel.y ||
			position.x >= b.position.x + b.size.x + rel.x ||
			position.y >= b.position.y + b.size.y + rel.y
			);
	}
	bool collide(Hitbox &b, double relX, double relY)
	{
		return collide(b, Vector2D(relX, relY));
	}
	double distanceToRight(Hitbox &b, double relX)
	{
		return (b.position.x + relX) - (position.x + size.x);
	}
	double distanceToLeft(Hitbox &b, double relX)
	{
		return position.x - (b.position.x + relX + b.size.x);
	}
	double distanceFromTop(Hitbox &b, double relY)
	{
		return (b.position.y + relY) - (position.y + size.y);
	}
	double distanceFromBottom(Hitbox &b, double relY)
	{
		return position.y - (b.position.y + relY + b.size.y);
	}
	bool collidePoint(double x, double y)
	{
		return (x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y);
	}
	bool collidePoint(Vector2D point)
	{
		return (point.x >= position.x && point.x <= position.x + size.x && point.y >= position.y && point.y <= position.y + size.y);
	}
};