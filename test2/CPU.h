#pragma once
#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <vector>
#include "ant.h"
#include "Model_3DS.h"

class CPU
{
private:
	std::vector<Ant> ants;
	std::vector<float> antsX;
	std::vector<float> antsY;
	Model_3DS ant;
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
	int antNum;
	static float rot;
	static float A;
	CPU(float x, float y, float z, float d, float d2, float cx, float cy, float cz,int tex[]);
	static int getRot() {return rot;}
	static float getA() {return A;}
	static void dA(float a) {A += a;}
	void drawGround(int x,int y,int z,int d);
	void drawCube(float x,float y,float z,float dx,float dy,float dz);
	void skybox(float x,float y,float z,float d,float dz);
	void cameraMovement();
	void addAnt();
	void drawCircle(float x, float y, float z, float r);
	void drawFan(float x, float y, float z);
	void drawBlades(float x,float y,float z);
	void drawAnt(float x, float y,float z);
	void drawAnts(int n);
	void theANTs(int n);
	void moveAnts(int n);
	void checkAnt(float px, float py);
	void CPUroom();
};