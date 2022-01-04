#include "CPU.h"

float CPU::A = 0.1;
float CPU::rot = 0;


void CPU::drawGround(int x,int y,int z,int d){
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D,tex[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);
	glVertex3f(x,y,z);
	glTexCoord2d(0, 0);
	glVertex3f(x+d,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+d,y+d,z);
	glTexCoord2d(1, 1);
	glVertex3f(x,y+d,z);
	glEnd();

}
void CPU::drawCube(float x,float y,float z,float dx,float dy,float dz){

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y+dy,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+dx,y+dy,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+dx,y+dy,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y+dy,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+dx,y,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+dx,y+dy,z);
	glTexCoord2d(0, 1);
	glVertex3f(x,y+dy,z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z+dz);
	glTexCoord2d(1, 0);
	glVertex3f(x+dx,y,z+dz);
	glTexCoord2d(1, 1);
	glVertex3f(x+dx,y+dy,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y+dy,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+dx,y,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+dx,y,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x,y+dy,z);
	glTexCoord2d(1, 1);
	glVertex3f(x,y+dy,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x+dx,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+dx,y+dy,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+dx,y+dy,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x+dx,y,z+dz);
	glEnd();
}
void CPU::skybox(float x,float y,float z,float d,float dz){

	glBindTexture(GL_TEXTURE_2D,tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y+d,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+d,y+d,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+d,y+d,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y+d,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+d,y,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+d,y,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x,y+d,z);
	glTexCoord2d(1, 1);
	glVertex3f(x,y+d,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x,y,z+dz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x+d,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+d,y+d,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+d,y+d,z+dz);
	glTexCoord2d(0, 1);
	glVertex3f(x+d,y,z+dz);
	glEnd();
}
void CPU::drawCircle(float x, float y, float z, float r){
	float dx=0,dy=0;
	glBegin(GL_TRIANGLE_FAN);
	for (float i=0.0f;i <= (2*3.15f*r);i += 0.01f){
		glVertex3f(x,y,z);
		glVertex3f(dx,dy,z);
		dx = r * cos(i);
		dy = r * sin(i);
		glVertex3f(dx,dy,z);
	}
	glEnd();
}
void CPU::drawFan(float x, float y, float z){
	glTranslatef(1010,1010,9);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.5,0.5,0.5);
	for (float i=0;i<2;i+=0.01){
	drawCircle(0,0,i,2);
	}
	glEnable(GL_TEXTURE_2D);
	glTranslatef(-1010,-1010,-9);
	for (int i = 0; i < 360; i += 60){
		glPushMatrix();
		glTranslatef(x,y,z);
		glRotatef(rot+i,0,0,1);
		glTranslatef(-x,-y,-z);
		if (A<0)
			A=0;
		rot += A;
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.2f,0.2f,0.3f);
		glBegin(GL_QUADS);
		glVertex3f(x,y,z+1);
		glVertex3f(x+2,y,z-1);
		glVertex3f(x+2,y+10,z-1);
		glVertex3f(x,y+10,z+1);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}
void CPU::drawBlades(float x,float y,float z){
	for (int i=0;i<360;i+=18){
		glPushMatrix();
		glTranslatef(x,y,z);
		glRotatef(i,0,0,1);
		glTranslatef(-x,-y,-z);
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,tex[3]);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(x,y+5,z);
		glTexCoord2d(0, 1);
		glVertex3f(x,y+9,z);
		glTexCoord2d(1, 1);
		glVertex3f(x,y+9,z-10);
		glTexCoord2d(1, 0);
		glVertex3f(x,y+5,z-10);
		glEnd();
		glPopMatrix();
	}
}
void CPU::drawAnt(float x, float y,float z){
	ant = Model_3DS();
	char* s = (char*)"assets/ant2.3ds";
	ant.Load(s);
	ant.pos.x = x;
	ant.pos.y = y;
	ant.pos.z = z;
	ant.Draw();
}
void CPU::checkAnt(float x, float y){
	for (int i=0;i<antNum;i++){
		if ((abs(x - antsX.at(i)) < 0.1) && (abs(y - antsY.at(i)) < 0.1)){
			ants.erase(ants.begin()+i);
		}
	}
}
void CPU::theANTs(int n){
	for (int i=0;i<n;i++){
		ants[i].randAnt(0.01);
	}
	for (int i=0;i<n;i++){
		drawAnt(ants[i].getX(), ants[i].getY(), 0.09);
	}
	//moveAnts(antNum);
}
void CPU::CPUroom(){
	drawGround(1000,1000,0,20);
	skybox(1000,1000,0,20,10);
	drawFan(1010,1010,10);
	drawBlades(1010,1010,8);
	theANTs(antNum);
}
void CPU::addAnt(){
	float x = 1001+rand()%17;
	float y = 1001+rand()%17;
	ants.push_back(Ant(x,y,0.1));
	antsX.push_back(x);
	antsY.push_back(y);
}
CPU::CPU(float x, float y, float z, float d, float d2, float cx, float cy, float cz,int* t){
	tex =t;
	antNum = 5;
	for (int i =0;i<antNum;i++){
		addAnt();
	}
	playerX=x,playerY=y,playerZ=z,Diff=d,Diff2=d2 ,cameraX=cx ,cameraY=cy ,cameraZ=cz;
	//CPUroom();

}
