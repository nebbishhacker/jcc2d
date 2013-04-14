#pragma once
#include "physicssprite.h"

class Chest : public PhysicsSprite
{
public: 
	Chest(double x, double y); 
	void initialize(); 
	void update(); 
	
private:
	bool itemObtained; 
	bool opening; 
	bool locked; 

}; 
