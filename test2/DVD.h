#pragma once
#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <vector>
#include "ant.h"
#include "Model_3DS.h"

class DVD
{
private:
	std::vector<Ant> ants;
	Model_3DS ant;
	int* tex;
	float laserAng;
	bool redButton;
	int bar_code_line_thickness_array[20];
	float ang, randomred, randomgreen;
	int b;

public:
	int antNum,kill;
	static float rot;
	static float A;
	DVD(int tex[]);
	static int getRot() {return rot;}
	static float getA() {return A;}
	static void dA(float a) {A += a;}
	void redQuad(float x, float y, float z, float d);
	void barCodeLines();
	void drawFrontDvd(int x,int y,int z,int d);
	void drawSideDvd(int x,int y,int z,int d);
	void drawBackDvd(int x,int y,int z,int d);
	void drawDvdUp(float x,float y,float z,float d);
	void drawDvdGround(float x,float y,float z,float d);
	void drawDvdHole(float x, float y,float z, float r);
	void drawRotatingDvd(float x, float y,float z, float r);
	void dvdLaser(float x, float y, float z);
	void dvdBarCode(float x, float y, float z, float width, float height, float padding);
	void dvdCylinder(float x, float y, float z, float radius, float height);
	void drawGround(int x,int y,int z,int d);
	void skybox(float x,float y,float z,float d,float dz);
	void cameraMovement();
	void addAnt(int i);
	void drawAnt(float x, float y,float z);
	void theANTs(int n);
	void checkAnt(float px, float py);
	void DVDroom();
};