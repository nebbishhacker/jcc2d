#pragma once
#include "physicssprite.h"
class PaperGirl : public PhysicsSprite
{
public:
	PaperGirl(double x, double y);
	void initialize();
	void update();

private:
	// state variables
	bool walking;
	bool attacking;
	bool immobolized;
	bool specialAttack; 

	double health; 
};