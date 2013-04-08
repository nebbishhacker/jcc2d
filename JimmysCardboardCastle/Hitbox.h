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

	bool collide(const Hitbox &b, const Vector2D &rel) const
	{
		return !(position.x + size.x <= b.position.x + rel.x ||
			position.y + size.y <= b.position.y + rel.y ||
			position.x >= b.position.x + b.size.x + rel.x ||
			position.y >= b.position.y + b.size.y + rel.y
			);
	}
	bool collide(const Hitbox &b, double relX, double relY) const
	{
		return collide(b, Vector2D(relX, relY));
	}
	double distanceToRight(const Hitbox &b, double relX) const
	{
		return (b.position.x + relX) - (position.x + size.x);
	}
	double distanceToLeft(const Hitbox &b, double relX) const
	{
		return position.x - (b.position.x + relX + b.size.x);
	}
	double distanceFromTop(const Hitbox &b, double relY) const
	{
		return (b.position.y + relY) - (position.y + size.y);
	}
	double distanceFromBottom(const Hitbox &b, double relY) const
	{
		return position.y - (b.position.y + relY + b.size.y);
	}
	bool collidePoint(double x, double y) const
	{
		return (x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y);
	}
	bool collidePoint(Vector2D point) const
	{
		return (point.x >= position.x && point.x <= position.x + size.x && point.y >= position.y && point.y <= position.y + size.y);
	}
};