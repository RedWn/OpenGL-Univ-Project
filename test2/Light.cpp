#include "Light.h"

void Light::ResetLightPosition(float x, float y, float z)
{
	GLfloat position[] = {x, y, z, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position); // Position The Light
}

void Light::ResetLightColor(float r, float g, float b)
{
	GLfloat color[] = {r, g, b, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color); // Light color
}

void Light::SetupSceneLight()
{
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1};
	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat direction[] = { 0, 0, -1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	ResetLightColor(1.0f, 1.0f, 1.0f);
	ResetLightPosition(0, 0, 10);
	glEnable(GL_LIGHT0);
}

void Light::lightManager(float x, float y, float z){
	GLfloat light_diffuseH[] = { 1, 1, 1, 1 };
	GLfloat light_diffuseL[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat light_diffuseR[] = { 0.8, 0, 0, 1 };
	glTranslatef(x,y,z);
	ResetLightPosition(0,0,0);
	glTranslatef(-x,-y,-z);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	ResetLightColor(1,1,1);
	if ((int)CPU::getRot()%60 < 20 && level == 1){
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseL);
	}else{
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseH);
	}
	if (CPU::getA() < 0.1){
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseR);
	}
}

Light::Light(){
	level = 1;
	SetupSceneLight();
}