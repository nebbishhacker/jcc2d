#pragma once
#include <string>
#include "TextureSprite.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class PhysicsSprite: public TextureSprite
{
public:
	PhysicsSprite(std::string spriteSheetFilename) : TextureSprite(spriteSheetFilename)
	{
		// Defaults!! Should probably reset mass in derived classes, less so gravity
		mass = 100;
		airDrag = 0;
		groundFriction = 0;
		airGroundFriction = 0;
		gravity = Vector2D(0, -1.5);
	}

	void applyGroundFriction()
	{
		// Using just gravity instead of the normal force, 'cause I don't really want to freeze under pressure
		netAcceleration.x -= sgn(contactVelocity.x) * min(groundFriction * abs(gravity.y), abs(contactVelocity.x));
	}

	void applyAirGroundFriction()
	{
		// There is still ground friction while airborn, but to a different extent. This is a game. It is not real.
		netAcceleration.x -= sgn(contactVelocity.x) * min(airGroundFriction * abs(gravity.y), abs(contactVelocity.x));
	}

	void applyAirDrag()
	{
		if (velocity.length_squared() != 0) netForce -= velocity.normalize() * 1/2 * airDrag * velocity.length_squared();
	}

	void resetPhysicsVars()
	{
		netForce = netAcceleration = Vector2D(0, 0);
		contactVelocity = velocity;
	}
	
	// Physical properties / constants
	double mass;
	double airDrag;
	double groundFriction;
	double airGroundFriction;
	Vector2D gravity;

	// netForce & netAcceleration are reset each frame
	Vector2D netForce;
	Vector2D netAcceleration;

	// velocity isn't
	Vector2D velocity;

	// contact velocity is the velocity used in groundFriction equations
	// (set to velocity each frame)
	Vector2D contactVelocity;
};