#include "CPU.h"

float CPU::A = 0.1;
float CPU::rot = 81;


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
	//for (float i=0;i<2;i+=0.01){
	drawCircle(0,0,0,2);
	//}
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
	std::vector<std::vector<Ant>::iterator> ants2;
	for (Ant a: ants){
		if ((abs(x - a.x) < 0.2) && (abs(y - a.y) < 0.2)){
			for (std::vector<Ant>::iterator antIterator = ants.begin(); antIterator != ants.end(); antIterator++) {
				if (antIterator->id == a.id){
					ants2.push_back(antIterator);
					break;
				}
			}
		}
	}
	for (auto it : ants2){
	ants.erase(it);
	kill++;
	}

}
void CPU::theANTs(int n){
	for (Ant a: ants){
		a.randAnt(0.01);
	}
	for (Ant a: ants){
		drawAnt(a.getX(), a.getY(), 0.09);
	}
}
void CPU::CPUroom(){
	drawGround(1000,1000,0,20);
	skybox(1000,1000,0,20,10);
	drawFan(1010,1010,10);
	drawBlades(1010,1010,8);
	theANTs(antNum);
}
void CPU::addAnt(int i){
	ants.push_back(Ant(1001+rand()%17,1001+rand()%17,0.1,i));
}
CPU::CPU(int* t){
	kill=0;
	tex =t;
	antNum = 5;
	for (int i =0;i<antNum;i++){
		addAnt(i * 10);
	}
}
