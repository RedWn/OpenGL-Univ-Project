#include <math.h>
#include <iostream>
class Ant 
{
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

	float getX(){return x;}
	float getY(){return y;}
};