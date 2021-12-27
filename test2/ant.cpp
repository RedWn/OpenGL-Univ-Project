#include <iostream>
#include "ant.h"

Ant::Ant(float xx, float yy, float zz){
	x = xx;
	y = yy;
	z = zz;
}
void Ant::stopAnt(){
	dx = 0;
	dy = 0;
}
void Ant::randAnt(float i){
	dx = (rand()%11 - 5) * i;
	dy = (rand()%11 - 5) * i;
}
void Ant::move(){
	x+=dx;
	y+=dy;
	if (x > 1020 || x < 1000)
		x=1010;
	if (y > 1020 || y < 1000)
		y=1010;
}