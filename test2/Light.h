#pragma once
#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>	
#include "CPU.h"

class Light

{
public:
	void lightManager(float x, float y, float z);
	void ResetLightPosition(float x, float y, float z);
	void ResetLightColor(float r, float g, float b);
	void SetupSceneLight();
	Light();

private:

};