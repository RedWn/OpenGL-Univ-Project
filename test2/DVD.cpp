#include "DVD.h"

float DVD::A = 0.1;
float DVD::rot = 81;


void DVD::drawGround(int x,int y,int z,int d){
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
void DVD::skybox(float x,float y,float z,float d,float dz){

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
void DVD::drawAnt(float x, float y,float z){
	ant = Model_3DS();
	char* s = (char*)"assets/ant2.3ds";
	ant.Load(s);
	ant.pos.x = x;
	ant.pos.y = y;
	ant.pos.z = z;
	ant.Draw();
}
void DVD::checkAnt(float x, float y){
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
void DVD::theANTs(int n){
	for (Ant a: ants){
		a.randAnt(0.01);
	}
	for (Ant a: ants){
		drawAnt(a.getX(), a.getY(), 0.09);
	}
}

void DVD::redQuad(float x, float y, float z, float d){
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, z);
	
	glVertex3f(x, y + (2 * d), z);
	
	glVertex3f(x, y + (2 * d), z + d);
	
	glVertex3f(x, y, z + d);
	glEnd();
}

void DVD::barCodeLines(){
	float barCodeLineThickness;
	for(int i = 0 ; i < 20 ; i++){
		barCodeLineThickness = rand() % 30;
		barCodeLineThickness += 2;
		bar_code_line_thickness_array[i] = barCodeLineThickness;
	}
}

void DVD::drawFrontDvd(int x,int y,int z,int d){
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x, y, z);
	
	glTexCoord2d(1, 0);
	glVertex3f(x , y + (5.35f * d), z);

	glTexCoord2d(1, 1);
	glVertex3f(x , y + (5.35f * d), z + (1.4f * d));
	
	glTexCoord2d(0, 1);
	glVertex3f(x, y, z + (1.4f * d));
	
	glEnd();
}
void DVD::drawSideDvd(int x,int y,int z,int d){
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x, y, z);
	
	glTexCoord2d(1, 0);
	glVertex3f(x + (6 * d), y, z);

	glTexCoord2d(1, 1);
	glVertex3f(x + (6 * d), y , z + (1.4f * d));
	
	glTexCoord2d(0, 1);
	glVertex3f(x, y, z + (1.4f * d));
	
	glEnd();
}
void DVD::drawBackDvd(int x,int y,int z,int d){
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x, y, z);
	
	glTexCoord2d(1, 0);
	glVertex3f(x , y + (5.35f * d), z);

	glTexCoord2d(1, 1);
	glVertex3f(x , y + (5.35f * d), z + (1.4f * d));
	
	glTexCoord2d(0, 1);
	glVertex3f(x, y, z + (1.4f * d));
	
	glEnd();
}


void DVD::drawDvdUp(float x,float y,float z,float d){
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2d(1, 0);
	glVertex3f(x + (1.15f * d), y, z);
	glTexCoord2d(1, 1);
	glVertex3f(x + (1.15f * d), y + d, z);
	glTexCoord2d(0, 1);
	glVertex3f(x, y + d , z);
	glEnd();
}
void DVD::drawDvdGround(float x,float y,float z,float d){
	glColor3f(0.2f, 0.2f, 0.2f);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2d(1, 0);
	glVertex3f(x + (1.15f * d), y, z);
	glTexCoord2d(1, 1);
	glVertex3f(x + (1.15f * d), y + d, z);
	glTexCoord2d(0, 1);
	glVertex3f(x, y + d , z);
	glEnd();
}
void DVD::drawDvdHole(float x, float y,float z, float r){
	glBegin(GL_TRIANGLES);
	float px = x, py = y;
	
	for (float i = 0 ; i < 2 * 3.15f ; i += 0.01){
		glColor3f (0, 0, 0);
		glVertex3f(x, y, z);
		glColor3f (0.6f, 0.6f, 0.6f);
		glVertex3f(px, py, z);
		px = x + r * cos(i);
		py = y + r * sin(i);
		glVertex3f(px ,py, z);
	}
	glEnd();
}


void DVD::drawRotatingDvd(float x, float y,float z, float r){
	glPushMatrix();
	glRotatef(ang, 0, 0, 1);
	ang += 1;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLES);
	float px = x, py = y;
	for (float i = 0 ; i < 2 * 3.14f * r ; i += 0.1){
		randomred = rand() % 150 ;
		randomred+=50;
		randomred/=255;

		randomgreen = rand() % 150 ;
		randomgreen+=50;
		randomgreen/=255;
		
		if(b == 0){
			glColor4f (randomred, randomgreen, 0.8f, 0.1f);
			b++;
		}
		else if(b == 1){
			glColor4f (randomred, randomgreen, 0.8f, 0.1f);
			b++;
		}
		else {
			glColor4f (randomred, randomgreen, 0.8f, 0.1f);
			b=0;
		}

		glVertex3f(px ,py,z);
		px = x + r * cos(i);
		py = y + r * sin(i);
		glVertex3f(px ,py, z);
		glColor4f (1, 1, 1, 0.1f);
		glVertex3f(x, y, z);
	}
	glEnd();
	glDisable(GL_BLEND);	
	drawDvdHole(0, 0, -1.95, 0.8);
	
	glPopMatrix();
}

void DVD::dvdLaser(float x, float y, float z){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	float alpha = 0.3f;
	glPushMatrix();
	glRotatef(laserAng, 0, 0, 1);
	laserAng += 0.4f;
	float zHighCircle = z + 3.5f;
	glBegin(GL_TRIANGLES);
	float px3 = x, py3 = y;
	for (float i=0 ; i < 2 * 3.15f ; i += 0.01){
		glColor4f (1, 0, 0, alpha);
		glVertex3f(x,y,zHighCircle);
		glColor4f(0.5f, 0, 0, alpha);
		glVertex3f(px3 ,py3,zHighCircle);
		px3 = x + (0.1f) * cos(i);
		py3 = y + (0.1f) * sin(i);
		glVertex3f(px3 ,py3, zHighCircle);
	}
	glEnd();
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor4f(1, 0, 0, alpha);
	glVertex3f(x, y, z);
	glVertex3f(x, y, zHighCircle);
	glEnd();
	glBegin(GL_TRIANGLES);
	float px2 = x, py2 = y;
	for (float i = 0 ; i < 2 * 3.15f ; i += 0.01f){
		glColor4f (1, 0, 0, alpha);
		glVertex3f(x,y,z);
		glColor4f(0.5f, 0, 0, alpha);
		glVertex3f(px2 ,py2, z);
		px2 = x + (0.1f) * cos(i);
		py2 = y + (0.1f) * sin(i);
		glVertex3f(px2, py2, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

void DVD::dvdBarCode(float x, float y, float z, float width, float height, float padding){
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(x, y, z);
	glVertex3f(x, y + width, z);
	glVertex3f(x+ height, y + width, z );
	glVertex3f(x+ height, y , z );
	glEnd();
	float barCodeLineThickness;
	int j = 0;
	for(float i = 0 ; i < width - 0.3f ; i += 0.08f){
		if(j>=20)
			j=0;

		glLineWidth(bar_code_line_thickness_array[j]);
		
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(x + height - padding, y + i + padding, z );
		if(j%5 == 0){
			glVertex3f(x + 0.05f, y + i + padding, z);
		}
		else
			glVertex3f(x+ padding, y + i + padding, z );
		glEnd();
		j++;
	}
}


void DVD::dvdCylinder(float x, float y, float z, float radius, float height){
	
	float px, py;
	glBegin(GL_LINES);
	glLineWidth(20);
	for( float i = 0 ; i < 2 * 3.15f ; i+=0.01f){
		px = x + radius * cos(i);
		py = y + radius * sin(i);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(px, py, z);
		glVertex3f(px, py, z + height);
	}
	glEnd();
}


void DVD::DVDroom(){
	//drawGround(1000,1000,0,20);
	//skybox(1000,1000,0,20,10);
	glTranslatef(1010,1010,2);
	drawRotatingDvd(0, 0, -2, 7.8f);
	glEnable(GL_TEXTURE_2D);
	
	drawFrontDvd(-9, -8, -2, 3);
	drawDvdUp(-9, -8, 2.01f, 16);
	drawDvdGround(-9, -8, -2.1f, 16);
	drawSideDvd(-9, -8, -2, 3);
	drawSideDvd(-9, +8, -2, 3);
	drawBackDvd(+9, -8, -2, 3);
	glDisable(GL_TEXTURE_2D);

	if(redButton){
		redQuad(-9.01f, -3.5f, -1.45f, 0.24f);
	}

	dvdLaser(4, 4, -1.8);
	dvdBarCode(-2, +2, 2, 3, 1.6f, 0.2f);
	dvdCylinder(0, 0, -2, 7.8f, 4);
	glTranslatef(-1010,-1010,-2);
	
	theANTs(antNum);
}
void DVD::addAnt(int i){
	ants.push_back(Ant(1001+rand()%17,1001+rand()%17,0.1,i));
}
DVD::DVD(int* t){
	kill=0;
	tex = t;
	antNum = 5;
	for (int i =0;i<antNum;i++){
		addAnt(i * 10);
	}
	laserAng  = 0;
	redButton = false;
	ang = 0;
	b=0;
}
