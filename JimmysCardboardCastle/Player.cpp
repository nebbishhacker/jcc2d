#include "Player.h"
#include "Game.h"
#include "GameWorld.h"
#include "healthHandler.h"
#include <iostream>

Player::Player(double x, double y) : PhysicsSprite("images/aa_spr_sam.png")
{
	// animations:
	// 0 - idle
	// 1 - walk right
	// 2 - jump up
	// 3 - fall down
	// 4 - bat
	// 5 - lava hit
	// 6 - shield
	// 7 - shoot
	// 8 - spring shoes
	setNumberOfAnimations(9);
	setSpriteFrameSize(128,128);

	addSpriteAnimRow(0, 0, 0, 128, 0, 6);
	setAnimationSpeed(0,0.05);

	

	addSpriteAnimRow(1, 128*6, 0, 128, 0, 9);
	setAnimationSpeed(1,0.25);
	addSpriteAnimFrame(2, 128*8, 0);
	addSpriteAnimFrame(3, 128*7, 0);

	addSpriteAnimRow(4, 0, 128*1, 128, 0, 4);
	setAnimationSpeed(4, 0.25);

	addSpriteAnimRow(5, 0, 0, 128, 0, 1); 
	setAnimationSpeed(5,0.25); 

	addSpriteAnimRow(6, 0, 0, 128, 0, 5); 
	setAnimationSpeed(6, 0.25); 

	addSpriteAnimRow(7, 0, 0 , 128, 0, 6); 
	setAnimationSpeed(7, 0.25); 

	addSpriteAnimFrame(8, 0, 608);

	setCurrentAnimation(0);
		
	setPosition(x,y);

	setCenter(62, 64);

	hitbox = Hitbox(38, 3, 44, 110);
	setLayerID(2);

	jumpReady = false;

	jumpSound = soundEngine.loadSound("sound/retrojump.wav");
	batSound = soundEngine.loadSound("sound/bat_sound.wav");
	moonJumpSound = soundEngine.loadSound("sound/moon_jump.wav");
	lavaHitSound = soundEngine.loadSound("sound/lava_hit.wav");

	mass = 50;
	airDrag = 0.1; // coefficient of fluid drag... ir something
	groundFriction = 0.75; // coefficient of friction; also, in affect, how fast he accelerates
	moveSpeed = Vector2D(8, 0); // Normal horizontal movement speed
	airGroundFriction = 0.5; // what fraction of ground friction is still (oddly) in affect in the air
	jumpVelocity = 25; // the initial vertical velocity of his jumps
	bootJumpVelocity = 30; // the initial vertical velocity of his moonboot jumps
	//gravity = Vector2D(0, -1.5); // gravity!	| ^ this way up ^ |

	hasBoots = false;
	hasBat = false;
	hasWaterGun = false; 
	useBat = false;
	useWaterGun = false; 
	score = 0;
	cookies = 0;
	marbles = 0;
	health = 5;
	invincibleTimer = 0;
	invincibleLength = 80;
	key = 0; 
}

void Player::initialize()
{
	input = world->input;
	world->groups["player"].add(this);
	world->groups["ground"].add(this);

	Sprite * t = new healthHandler(this, 5);
	world->add(t);
}

void Player::update()
{
	if (input->keysPressed['z']) {
		hasBoots = !hasBoots;
	}
	if (input->keysPressed['a']) {
		health-=0.5;
	}

	if (collide(&world->groups["lava"], 0, -2) != NULL)
	{
		damage(1);
		velocity.y = jumpVelocity;
		soundEngine.playSound(lavaHitSound); // oooh, burn
	}

	if (flipped)
		batDistance = -45;
	else
		batDistance = 45;

	// Handle jumping (and resultant instantaneous changes in velocity) //
	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL); // Is the character on the ground?

	
	// Play the bat swinging animation //
	if ((input->specialsDown[GLUT_KEY_END] || (input->keysDown['x'] && hasBat)) && grounded && !useBat)
	{
		setCurrentAnimation(4);
		setFrame(0);
		useBat = true;
		soundEngine.playSound(batSound); // swoosh
	}
	//if ((input->specialsDown[GLUT_KEY_END] || (input->keysDown['c'] && hasWaterGun)) && grounded && !useWaterGun)
	//{
	//	setCurrentAnimation(7);
	//	setFrame(0);
	//	useWaterGun = true;
	//	//soundEngine.playSound(batSound); // swoosh
	//}
	// These events will not occur if the player is swinging his bat //
	if (!useBat)
	{
		bool jumpKeysDown = (input->specialsDown[GLUT_KEY_UP] || input->keysDown[' ']);
		if (jumpReady && jumpKeysDown && grounded && !useBat) // JUMP!
		{
			velocity.y = hasBoots ? bootJumpVelocity : jumpVelocity; // Directly set velocity, 'cause it's simpler and more reliable than forces in this case
			jumpReady = false; // only wanna jump once

			if (hasBoots)
				soundEngine.playSound(moonJumpSound); // different boing
			else
				soundEngine.playSound(jumpSound); // boing
		}
		if (!jumpReady && !jumpKeysDown) jumpReady = true; // Ready to jump once more

	if (!useWaterGun)
	{
		bool jumpKeysDown = (input->specialsDown[GLUT_KEY_UP] || input->keysDown[' ']);
		if (jumpReady && jumpKeysDown && grounded && !useWaterGun) // JUMP!
		{
			velocity.y = hasBoots ? bootJumpVelocity : jumpVelocity; // Directly set velocity, 'cause it's simpler and more reliable than forces in this case
			jumpReady = false; // only wanna jump once

			if (hasBoots)
				soundEngine.playSound(moonJumpSound); // different boing
			else
				soundEngine.playSound(jumpSound); // boing
		}
		if (!jumpReady && !jumpKeysDown) jumpReady = true;
	}
		// Ready to jump once more
		// Handle input for maneuvering //
		// contactVelocity is the theoretical speed of the character's feet -- whichever way his feet move, 2friction makes him move in the opposite direction
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
			setCurrentAnimation(0); // on the ground and not moving/using bat? Idle!
		}
	}

	// Handles ground friction and acceleration due to foot movement //
	if (grounded)
		applyGroundFriction();
	else {
		// There is still ground friction while airborn, but to a different extent. This is a game. It is not real.
		applyAirGroundFriction();
		if (velocity.y >= 0) if (hasBoots) setCurrentAnimation(8); else setCurrentAnimation(2);
		else setCurrentAnimation(3);
	}

	// Bat using events //
	if (useBat)
	{
		// Objects destroyed upon contact //
		Sprite * hitObject;
		hitObject = collide(&world->groups["breakable"],batDistance,5);
		if (hitObject)
		{
			hitObject->kill();
		}

		hitObject = collide(&world->groups["reflectable"],batDistance,5);
		if (hitObject)
		{
			world->groups["reflectable"].remove(hitObject);
			if (hitObject->flipped)
				hitObject->flipped = false;
			else
				hitObject->flipped = true;
		}

		// At the end of the bat animation stop from swinging //
		if (animations[currentAnimation]->currentFrame == 3 || currentAnimation != 4)
		{
			useBat = false;
		}
	}

	if (useWaterGun)
	{
		// At the end of the bat animation stop from swinging //
		if (animations[currentAnimation]->currentFrame == 3 || currentAnimation != 4)
		{
			useWaterGun = false;
		}
	}

	// Handles air drag //
	applyAirDrag();

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
	resetPhysicsVars();

	if (invincibleTimer > 0)
	{
		if (invincibleTimer % 4 == 0) { visible = !visible; }
		--invincibleTimer;
		if (invincibleTimer == 0) visible = true;
	}
}