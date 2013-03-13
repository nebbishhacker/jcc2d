#pragma once

struct Hitbox
{
	double width;
	double height;
	double xPos;
	double yPos;
	Hitbox(double x, double y, double _width, double _height)
	{
		xPos = x;
		yPos = y;
		width = _width;
		height = _height;
	}
	Hitbox()
	{
		xPos = yPos = width = height = 0;
	}

	bool collide(Hitbox &b, double relX, double relY)
	{
		return !(xPos + width <= b.xPos + relX ||
			yPos + height <= b.yPos + relY ||
			xPos >= b.xPos + b.width + relX ||
			yPos >= b.yPos + b.height + relY
			);
	}
	double distanceToRight(Hitbox &b, double relX)
	{
		return (b.xPos + relX) - (xPos + width);
	}
	double distanceToLeft(Hitbox &b, double relX)
	{
		return xPos - (b.xPos + relX + b.width);
	}
	double distanceFromTop(Hitbox &b, double relY)
	{
		return (b.yPos + relY) - (yPos + height);
	}
	double distanceFromBottom(Hitbox &b, double relY)
	{
		return yPos - (b.yPos + relY + b.height);
	}
};