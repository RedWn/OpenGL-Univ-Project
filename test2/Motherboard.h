#pragma once
#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <vector>
#include "ant.h"
#include "Model_3DS.h"
#include "3DTexture.h"

class Motherboard
{
private:
	std::vector<Ant> ants;
	Model_3DS ant;
	Model_3DS motherboard;
	int* tex;

public:
	int antNum,kill;
	static float rot;
	static float A;
	Motherboard(int tex[]);
	static int getRot() {return rot;}
	static float getA() {return A;}
	static void dA(float a) {A += a;}
	void drawGround(int x,int y,int z,int d);
	void drawCube(float x,float y,float z,float dx,float dy,float dz);
	void skybox(float x,float y,float z,float d,float dz);
	void addAnt(int i);
	void drawAnt(float x, float y,float z);
	void theANTs(int n);
	void moveAnts(int n);
	void checkAnt(float px, float py);
	void Motherboardroom();
};