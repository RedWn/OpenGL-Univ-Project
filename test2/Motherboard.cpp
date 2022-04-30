#include "Motherboard.h"

float Motherboard::A = 0.1;
float Motherboard::rot = 81;


void Motherboard::drawGround(int x,int y,int z,int d){
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
	glColor4f(0.5f,0.5f,0.5f,0.3f);
	glVertex3f(x,y,z);
	glVertex3f(x+d,y,z);
	glVertex3f(x+d,y+d,z);
	glVertex3f(x,y+d,z);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

}
void Motherboard::skybox(float x,float y,float z,float d,float dz){

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
void Motherboard::drawAnt(float x, float y,float z){
	ant = Model_3DS();
	char* s = (char*)"assets/ant2.3ds";
	ant.Load(s);
	ant.pos.x = x;
	ant.pos.y = y;
	ant.pos.z = z;
	ant.Draw();
}
void Motherboard::checkAnt(float x, float y){
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
void Motherboard::theANTs(int n){
	for (Ant a: ants){
		a.randAnt(0.01);
	}
	for (Ant a: ants){
		drawAnt(a.getX(), a.getY(), 0.09);
	}
}
void Motherboard::Motherboardroom(){
	motherboard.pos.x = 1000;
	motherboard.pos.y = 1000;
	motherboard.pos.z = 0;
	glPushMatrix();
	glTranslatef(1000,1000,-5);
	glRotatef(90,1,0,0);
	glTranslatef(-1000,-1000,5);
	motherboard.Draw();
	theANTs(antNum);
}
void Motherboard::addAnt(int i){
	ants.push_back(Ant(1001+rand()%17,1001+rand()%17,0.1,i));
}
Motherboard::Motherboard(int* t){
	kill=0;
	tex =t;
	motherboard.Load("assets/mainboard.3ds");
	motherboard.Materials[2].tex.LoadBMP("assets/p4sba-mb.bmp");
	motherboard.Materials[3].tex.LoadBMP("assets/mb-ps-2.bmp");
	antNum = 5;
	for (int i =0;i<antNum;i++){
		addAnt(i * 10);
	}
}
