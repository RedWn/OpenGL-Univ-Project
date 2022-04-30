#pragma once
#include <math.h>
#include <iostream>
class Ant {
private:
	

public:
	int id;
	float x;
	float dx;
	float y;
	float dy;
	float z;
	float dz;
	Ant(float xx, float yy, float zz, int idd);
	void stopAnt();
	void randAnt(float i);
	void move();
	void kill(float px, float py);

	float getX(){return x;}
	float getY(){return y;}
};