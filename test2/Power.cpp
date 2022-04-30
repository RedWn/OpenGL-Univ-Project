#include "Power.h"

float Power::A = 0.1;
float Power::rot = 81;

void Power::drawGround(int x,int y,int z,int d){
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
void Power::skybox(float x,float y,float z,float d,float dz){

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D,tex[1]);
	glBegin(GL_QUADS);
	glColor4f(0.8f,0.8f,0.8f,0.5f);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glColor4f(0.8f,0.8f,0.8f,0.5f);
	glTexCoord2d(1, 0);
	glVertex3f(x+d,y,z);
	glColor4f(0.8f,0.8f,0.8f,0.5f);
	glTexCoord2d(1, 1);
	glVertex3f(x+d,y,z+dz);
	glColor4f(0.8f,0.8f,0.8f,0.5f);
	glTexCoord2d(0, 1);
	glVertex3f(x,y,z+dz);
	glEnd();
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D,tex[1]);
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

	glBindTexture(GL_TEXTURE_2D,tex[1]);
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
void Power::drawWires(int n){
	glPushMatrix();
	glTranslatef(1000,1000,0);

	int x,y,z,r;
	for(int i=0;i<n;++i){
		glPushMatrix();

		r = (i+20)%46;
		x = (19*i)%20;
		y = (18*i)%20;
		glTranslatef(x,y,0);
		glColor3i(x,y,r);
		glRotatef(r,1.0f,0.0f,0.0f);
		/*
		TODO
		*/
		glPopMatrix();
	}

	glPopMatrix();
}
void Power::drawCircle(float x, float y, float z, float r){
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
void Power::checkAnt(float x, float y){
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
void Power::drawFan(float x, float y, float z){
	glPushMatrix();
	glTranslatef(1009,1019,5);
	glRotatef(90,1.0f,0,0);
	glScalef(0.5f,0.5f,0.5f);
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
	glPopMatrix();
}
void Power::drawAnt(float x, float y,float z){
	ant = Model_3DS();
	char* s = (char*)"assets/ant2.3ds";
	ant.Load(s);
	ant.pos.x = x;
	ant.pos.y = y;
	ant.pos.z = z;
	ant.Draw();
}
void Power::theANTs(int n){
	for (Ant a: ants){
		a.randAnt(0.01);
	}
	for (Ant a: ants){
		drawAnt(a.getX(), a.getY(), 0.09);
	}
}
void Power::Powerroom(){
	drawGround(1000,1000,0,20);
	skybox(1000,1000,0,20,10);
	drawFan(1010,1010,10);
	theANTs(antNum);
}
void Power::addAnt(int i){
	ants.push_back(Ant(1001+rand()%17,1001+rand()%17,0.1,i));
}

Power::Power(int* t){
	kill=0;
	tex =t;
	antNum = 5;
	for (int i =0;i<antNum;i++){
		addAnt(i * 10);
	}	
}
Power::Power(){};