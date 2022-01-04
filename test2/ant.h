#pragma once
#include <math.h>
#include <iostream>
class Ant {
private:
	float x;
	float dx;
	float y;
	float dy;
	float z;
	float dz;

public:
	Ant(float xx, float yy, float zz);
	void stopAnt();
	void randAnt(float i);
	void move();
	void kill(float px, float py);

	float getX(){return x;}
	float getY(){return y;}
};