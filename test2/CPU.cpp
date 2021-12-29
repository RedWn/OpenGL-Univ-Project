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

/*void CPU::cameraMovement(){
	if (keys['W']){
		playerX += 1 * cos(Diff * 3.1415 / 180); 
		playerY += 1 * sin(Diff * 3.1415 / 180);
	}
	if (keys['S']){
		playerX -= 1 * cos(Diff * 3.1415 / 180); 
		playerY -= 1 * sin(Diff * 3.1415 / 180);
	}
	if (keys['D']){
		playerX -= 1 * sin(Diff * 3.1415 / 180);
		playerY -= 1 * cos(Diff * 3.1415 / 180);
	}
	if (keys['A']){
		playerX += 1 * sin(Diff * 3.1415 / 180); 
		playerY += 1 * cos(Diff * 3.1415 / 180);
	}
	if (keys[VK_LEFT]){
		Diff += 5;
	}
	if (keys[VK_RIGHT]){
		Diff -= 5;
	}
	if (keys[VK_UP]){
		Diff2 += 5;
	}
	if (keys[VK_DOWN]){
		Diff2 -= 5;
	}
	if (keys['I']){
		if (playerZ < 10){
			playerZ = 10;
		}else if (playerZ > 0.2){
			playerZ = 0.2;
		}
	}
	cameraX = playerX + 5 * cos(Diff * 3.1415 / 180);
	cameraY = playerY + 5 * sin(Diff * 3.1415 / 180);
	cameraZ = playerZ + 5 * sin(Diff2 * 3.1415 / 180);
	gluLookAt(playerX,playerY,playerZ,cameraX,cameraY,cameraZ,0,0,1);
}
*/
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
		glColor3f(0.5,0.5,0.5);
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
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glVertex3f(x,y+5,z);
		glVertex3f(x,y+9,z);
		glVertex3f(x,y+9,z-10);
		glVertex3f(x,y+5,z-10);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}
void CPU::drawAnt(float x, float y,float z){
	drawCube(x,y,z,0.2,0.2,0.2);
	drawCube(x+0.05,y+0.2,z+0.05,0.1,0.1,0.1);
	drawCube(x,y+0.3,z,0.2,0.3,0.2);
}
void CPU::theANTs(int n){
	for (int i=0;i<n;i++){
		ants[i].randAnt(0.1);
	}
	for (int i=0;i<n;i++){
		drawAnt(ants[i].getX(), ants[i].getY(), 0.09);
	}
	moveAnts(antNum);
}
void CPU::moveAnts(int n){
	for (int i=0;i<n;i++){
		ants[i].move();
	}
}
void CPU::CPUroom(){
	drawGround(1000,1000,0,20);
	skybox(1000,1000,0,20,10);
	drawFan(1010,1010,10);
	drawBlades(1010,1010,8);
	theANTs(antNum);
}
void CPU::addAnt(){
	ants.push_back(Ant(1000+rand()%20,1000+rand()%20,0.2));
}
CPU::CPU(float x, float y, float z, float d, float d2, float cx, float cy, float cz,int t[10]){
	for(int i=0;i<3;i++)
		tex[i]=t[i];
	antNum = 5;
	//TODO FIX THIS
	for (int i =0;i<antNum;i++){
		addAnt();
	}
	playerX=x,playerY=y,playerZ=z,Diff=d,Diff2=d2 ,cameraX=cx ,cameraY=cy ,cameraZ=cz;
	CPUroom();

}
