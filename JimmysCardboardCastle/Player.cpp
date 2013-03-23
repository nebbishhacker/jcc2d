#include "Player.h"
#include "Game.h"
#include <iostream>

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

	vy = 0;
	jumping = false;

	//jumpSound = soundEngine.loadSound();
}

void Player::initialize()
{
	input = world->input;
	world->groups["player"].add(this);
}

void Player::update()
{
	int dx = 0, dy = 0;

	vy -= 1.5;

	bool grounded = (collide(&world->groups["ground"], 0, -2) != NULL);
	 
	int moveSpeed = 7;
	if (input->keysDown['X']) moveSpeed *= 2;
	
	if (!jumping && input->specialsDown[GLUT_KEY_UP] && grounded) {
		vy = 30;
		jumping = true;
		//soundEngine.playSound(jumpSound);
	}

	if (input->specialsDown[GLUT_KEY_LEFT] && !input->specialsDown[GLUT_KEY_RIGHT]) {
		dx -= moveSpeed;
		if (grounded) { setCurrentAnimation(1); flipped = true; }
	}
	else if (input->specialsDown[GLUT_KEY_RIGHT] && !input->specialsDown[GLUT_KEY_LEFT]) {
		dx += moveSpeed;
		if (grounded) { setCurrentAnimation(1); flipped = false; }
	}
	else if (grounded) setCurrentAnimation(0);
	if (!grounded) {
		if (vy >= 0) setCurrentAnimation(2);
		else setCurrentAnimation(3);
	}

	if (jumping && !input->specialsDown[GLUT_KEY_UP]) jumping = false;
	
	dy += vy;
	moveCollideX(dx, &world->groups["ground"]);
	if (moveCollideY(dy, &world->groups["ground"])) vy = 0;

	world->centerCamera(positionX + centerX, positionY + centerY);
}