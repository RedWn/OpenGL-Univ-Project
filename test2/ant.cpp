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
	dx = (rand()%5 - 2) * i;
	dy = (rand()%5 - 2) * i;
}
void Ant::move(){
	x+=dx;
	y+=dy;
	if (x > 1020 || x < 1000) //TODO fix the hardcoded and slap someone
		x=1010;
	if (y > 1020 || y < 1000)
		y=1010;
}