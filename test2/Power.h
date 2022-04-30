#pragma once
#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <vector>
#include "ant.h"
#include "Model_3DS.h"

class Power
{
private:
	Model_3DS ant;
	std::vector<Ant> ants;
	float playerX;
	float playerY;
	float playerZ;
	float Diff;
	float Diff2;
	float cameraX;
	float cameraY;
	float cameraZ;
	int* tex;
	

public:
	int antNum,kill;
	static float rot;
	static float A;
	Power(int tex[]);
	Power();
	static int getRot() {return rot;}
	static float getA() {return A;}
	static void dA(float a) {A += a;}
	void drawGround(int x,int y,int z,int d);
	void skybox(float x,float y,float z,float d,float dz);
	void checkAnt(float x, float y);
	void addAnt(int i);
	void drawCircle(float x, float y, float z, float r);
	void drawFan(float x, float y, float z);
	void drawWires(int n);
	void drawAnt(float x, float y,float z);
	void drawAnts(int n);
	void theANTs(int n);
	void moveAnts(int n);
	void Powerroom();
};