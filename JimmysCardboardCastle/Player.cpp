#include "Player.h"
#include "Game.h"
#include <iostream>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


const double Player::airDrag = 0.1; // coefficient of fluid drag... ir something
const double Player::groundFriction = 0.75; // coefficient of friction; also, in affect, how fast he accelerates
const Vector2D Player::moveSpeed = Vector2D(8, 0); // Normal horizontal movement speed
const double Player::airManeuverability = 0.75; // what fraction of ground friction is still (oddly) in affect in the air
const double Player::jumpVelocity = 30; // the initial vertical velocity of his jumps
const Vector2D Player::gravity = Vector2D(0, -1.5); // gravity!	| ^ this way up ^ |

Player::Player(double x, double y) : TextureSprite("images/dev/SamSheet.png")
{
	// animations:
	// 0 - idle
	// 1 - walk left
	// 2 - jump up
	// 3 - fall down
	setNumberOfAnimations(4);
	setSpriteFrameSize(128,128);
	addSpriteAnimRow(0, 0, 0, 128, 0, 6);
	setAnimationSpeed(0,0.05);
	addSpriteAnimRow(1, 128*6, 0, 128, 0, 9);
	setAnimationSpeed(1,0.25);
	addSpriteAnimFrame(2, 128*8, 0);
	addSpriteAnimFrame(3, 128*7, 0);
	setCurrentAnimation(0);
		
	setPosition(x,y);

	setCenter(50, 50);

	hitbox = Hitbox(42, 3, 44, 120);
	setLayerID(2);

	jumpReady = false;

	jumpSound = soundEngine.loadSound("sound/retrojump.wav");

	mass = 50;
}

void Player::initialize()
{
	input = world->input;
	world->groups["player"].add(this);
}

void Player::update()
{
	// Handle jumping (and resultant instantaneous changes in velocity) //
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL); // Is the character on the ground?
	if (jumpReady && input->specialsDown[GLUT_KEY_UP] && grounded) // JUMP!
	{
		velocity.y = jumpVelocity; // Directly set velocity, 'cause it's simpler and more reliable than forces in this case
		jumpReady = false; // only wanna jump once
		soundEngine.playSound(jumpSound); // boing
	}
	if (!jumpReady && !input->specialsDown[GLUT_KEY_UP]) jumpReady = true; // Ready to jump once more

	// Handle input for maneuvering //
	// contactVelocity is the theoretical speed of the character's feet -- whichever way his feet move, friction makes him move in the opposite direction
	Vector2D contactVelocity = velocity;
	if (input->specialsDown[GLUT_KEY_LEFT] && !input->specialsDown[GLUT_KEY_RIGHT]) // moving left
	{
		if (grounded) {
			setCurrentAnimation(1); // walking
			flipped = true; // facing left
		}
		contactVelocity += moveSpeed; // move those feet!
	}
	else if (input->specialsDown[GLUT_KEY_RIGHT] && !input->specialsDown[GLUT_KEY_LEFT]) // moving right
	{
		if (grounded) {
			setCurrentAnimation(1); // walking
			flipped = false; // facing right
		}
		contactVelocity -= moveSpeed; // you heard me.
	}
	else if (grounded) {
		setCurrentAnimation(0); // on the ground and not moving? Idle!
	}

	// Handles ground friction and acceleration due to foot movement //
	if (grounded)
		// Using just gravity instead of the normal force, 'cause I don't really want to freeze under pressure
		netAcceleration.x -= sgn(contactVelocity.x) * min(groundFriction * abs(gravity.y), abs(contactVelocity.x));
	if (!grounded) {
		// There is still ground friction while airborn, but to a lesser degree. This is a game. It is not real.
		netAcceleration.x -= sgn(contactVelocity.x) * min(groundFriction * airManeuverability * abs(gravity.y), abs(contactVelocity.x));
		if (velocity.y >= 0) setCurrentAnimation(2);
		else setCurrentAnimation(3);
	}
	// Handles air drag //
	if (velocity.length_squared() != 0) netForce -= velocity.normalize() * 1/2 * airDrag * velocity.length_squared();

	netForce += gravity * mass;

	// Figure out the net acceleration from forces //
	netAcceleration += netForce / mass;

	// Move the sprite, checking for collisions //
	Vector2D delta = velocity + netAcceleration * 0.5;
	if (moveCollideX(delta.x, &world->groups["ground"])) velocity.x = 0;
	if (moveCollideY(delta.y, &world->groups["ground"])) velocity.y = 0;

	// update velocity to reflect acceleration //
	velocity += netAcceleration;

	// center da camera on the sprite //
	world->centerCamera(position + center);

	// reset netForce and netAcceleration for the next timestep (so they can be modified externally, if need be)
	netForce = netAcceleration = Vector2D(0, 0);
}