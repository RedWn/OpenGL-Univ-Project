#include "RAM.h"

float RAM::A = 0.1;
float RAM::rot = 0;


void RAM::drawRoof(int x,int y,int z,int d){
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D,tex[5]);
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
void RAM::drawGround(int x,int y,int z,int d){
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D,tex[0]);
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
void RAM::skybox(float x,float y,float z,float d,float dz){

	glBindTexture(GL_TEXTURE_2D,tex[1]);
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

	glBindTexture(GL_TEXTURE_2D,tex[1]);
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
void RAM::drawAnt(float x, float y,float z){
	ant = Model_3DS();
	char* s = (char*)"assets/ant2.3ds";
	ant.Load(s);
	ant.pos.x = x;
	ant.pos.y = y;
	ant.pos.z = z;
	ant.Draw();
}
void RAM::checkAnt(float x, float y){
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
void RAM::theANTs(int n){
	for (Ant a: ants){
		a.randAnt(0.01);
	}
	for (Ant a: ants){
		drawAnt(a.getX(), a.getY(), 0.09);
	}
	//moveAnts(antNum);
}

void RAM::DrowRam(float x, float y, float z,boolean rout){
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(90,1,0,0);
	glTranslatef(-x,-y,-z);
	if (!rout){
		glTranslatef(x+2.4,y,z);
		glRotatef(180,0,1,0);
		glTranslatef(-x-2.4,-y,-z);
		glTranslatef(x+2.4,y+1,z);
		glRotatef(180,0,0,1);
		glTranslatef(-x-2.4,-y-1,-z);
	}
	if(rout){
	 glBindTexture(GL_TEXTURE_2D , tex[3]);
	}else{
	glBindTexture(GL_TEXTURE_2D , tex[2]);
	}
     glBegin(GL_QUADS);
     glColor3d(1,1,1);
     glTexCoord2f(1, 1);
     glVertex3d(x+4.8,y+2,z);
     glTexCoord2f(1, 0);
     glVertex3d(x,y+2,z);
     glTexCoord2f(0, 0);
     glVertex3d(x,y,z);
     glTexCoord2f(0, 1);
     glVertex3d(x+4.8,y,z);
     glEnd();
    
    if(rout){
	 glBindTexture(GL_TEXTURE_2D , tex[3]);
	}else{
	glBindTexture(GL_TEXTURE_2D , tex[2]);
	}
      glBegin(GL_QUADS);
     glColor3d(1,1,1);
      glTexCoord2f(1, 1);
     glVertex3d(x+4.8,y+2,z+0.1);
      glTexCoord2f(1, 0);
     glVertex3d(x,y+2,z+0.1);
      glTexCoord2f(0, 0);
     glVertex3d(x,y,z+0.1);
      glTexCoord2f(0, 1);
     glVertex3d(x+4.8,y,z+0.1);
     glEnd();
     
     glBegin(GL_QUADS);
     glColor3d(0,0.3,0);
     glVertex3d(x+4.8,y+2,z+0.1);
     glVertex3d(x+4.8,y+2,z);
     glVertex3d(x+4.8,y,z);
     glVertex3d(x+4.8,y,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0,0.3,0);
     glVertex3d(x,y+2,z+0.1);
     glVertex3d(x,y+2,z);
     glVertex3d(x,y,z);
     glVertex3d(x,y,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0,0.3,0);
     glVertex3d(x,y,z+0.1);
     glVertex3d(x,y,z);
     glVertex3d(x+4.8,y,z);
     glVertex3d(x+4.8,y,z+0.1);
     glEnd();

	//ICs
	  //**ic 1
     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+1.3,y+1.1,z+0.1);
     glVertex3d(x+1.3,y+1.1,z+0.35);
     glVertex3d(x+1.3,y+0.4,z+0.35);
     glVertex3d(x+1.3,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+1.9,y+1.1,z+0.1);
     glVertex3d(x+1.9,y+1.1,z+0.35);
     glVertex3d(x+1.9,y+0.4,z+0.35);
     glVertex3d(x+1.9,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+1.9,y+0.4,z+0.1);
     glVertex3d(x+1.9,y+0.4,z+0.35);
     glVertex3d(x+1.3,y+0.4,z+0.35);
     glVertex3d(x+1.3,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+1.9,y+1.1,z+0.1);
     glVertex3d(x+1.9,y+1.1,z+0.35);
     glVertex3d(x+1.3,y+1.1,z+0.35);
     glVertex3d(x+1.3,y+1.1,z+0.1);
     glEnd();

     glBindTexture(GL_TEXTURE_2D , tex[4]);
	 glEnable(GL_TEXTURE_2D);
     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glTexCoord2f(1, 0);
     glVertex3d(x+1.9,y+0.4,z+0.45);
     glTexCoord2f(0, 0);
     glVertex3d(x+1.9,y+1.1,z+0.45);
     glTexCoord2f(0,1);
     glVertex3d(x+1.3,y+1.1,z+0.45);
     glTexCoord2f(1, 1);
     glVertex3d(x+1.3,y+0.4,z+0.45);
     glEnd();

     //**ic2
     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+2.9,y+1.1,z+0.1);
     glVertex3d(x+2.9,y+1.1,z+0.35);
     glVertex3d(x+2.9,y+0.4,z+0.35);
     glVertex3d(x+2.9,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(1,0,0);
     glVertex3d(x+4.8,y+2,z);
     glVertex3d(x,y+2,z);
     glVertex3d(x,y,z);
     glVertex3d(x+4.8,y,z);
     glEnd();
     
	 glColor3d(0.1,0.1,0.1);
     glVertex3d(x+3.5,y+1.1,z+0.1);
     glVertex3d(x+3.5,y+1.1,z+0.35);
     glVertex3d(x+3.5,y+0.4,z+0.35);
     glVertex3d(x+3.5,y+0.4,z+0.1);
     glEnd();

       glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+3.5,y+0.4,z+0.1);
     glVertex3d(x+3.5,y+0.4,z+0.35);
     glVertex3d(x+2.9,y+0.4,z+0.35);
     glVertex3d(x+2.9,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+3.5,y+1.1,z+0.1);
     glVertex3d(x+3.5,y+1.1,z+0.35);
     glVertex3d(x+2.9,y+1.1,z+0.35);
     glVertex3d(x+2.9,y+1.1,z+0.1);
     glEnd();



     glBindTexture(GL_TEXTURE_2D , tex[4]);
     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glTexCoord2f(1, 0);
     glVertex3d(x+3.5,y+0.4,z+0.35);
     glTexCoord2f(0, 0);
     glVertex3d(x+3.5,y+1.1,z+0.35);
     glTexCoord2f(0,1);
     glVertex3d(x+2.9,y+1.1,z+0.35);
     glTexCoord2f(1, 1);
     glVertex3d(x+2.9,y+0.4,z+0.35);
     glEnd();

	 //**ic 3
     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+3.8,y+1.1,z+0.1);
     glVertex3d(x+3.8,y+1.1,z+0.45);
     glVertex3d(x+3.8,y+0.4,z+0.45);
     glVertex3d(x+3.8,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+4.4,y+1.1,z+0.1);
     glVertex3d(x+4.4,y+1.1,z+0.45);
     glVertex3d(x+4.4,y+0.4,z+0.45);
     glVertex3d(x+4.4,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+4.4,y+0.4,z+0.1);
     glVertex3d(x+4.4,y+0.4,z+0.45);
     glVertex3d(x+3.8,y+0.4,z+0.45);
     glVertex3d(x+3.8,y+0.4,z+0.1);
     glEnd();

     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glVertex3d(x+4.4,y+1.1,z+0.1);
     glVertex3d(x+4.4,y+1.1,z+0.45);
     glVertex3d(x+3.8,y+1.1,z+0.45);
     glVertex3d(x+3.8,y+1.1,z+0.1);
     glEnd();

     glBindTexture(GL_TEXTURE_2D , tex[4]);
     glBegin(GL_QUADS);
     glColor3d(0.1,0.1,0.1);
     glTexCoord2f(1, 0);
     glVertex3d(x+4.4,y+0.4,z+0.45);
     glTexCoord2f(0, 0);
     glVertex3d(x+4.4,y+1.1,z+0.45);
     glTexCoord2f(0,1);
     glVertex3d(x+3.8,y+1.1,z+0.45);
     glTexCoord2f(1, 1);
     glVertex3d(x+3.8,y+0.4,z+0.45);
     glEnd();
	 glPopMatrix();
}

void RAM::RAMroom(){
	drawGround(1000,1000,0,20);
	skybox(1000,1000,0,20,10);
	DrowRam(1003,1005,0);
	DrowRam(1013,1005,0);
	DrowRam(1003,1013,0,true);
	DrowRam(1013,1013,0,true);
	drawRoof(1000,1000,8,20);
	theANTs(antNum);
}
void RAM::addAnt(int i){
	ants.push_back(Ant(1001+rand()%17,1001+rand()%17,0.1,i));
}
RAM::RAM(int* t){
	kill=0;
	tex =t;
	antNum = 5;
	for (int i =0;i<antNum;i++){
		addAnt(i * 10);
	}
}
