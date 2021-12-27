#include <windows.h>	// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>


HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
int num_texture=-1;
int LoadTexture(const char *filename,int alpha) 
{
    int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture
     
    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading
    
    fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader
    
    fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {            
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, l_file); 

            // And store it
            l_texture[j+0] = rgb.rgbtRed; // Red component
            l_texture[j+1] = rgb.rgbtGreen; // Green component
            l_texture[j+2] = rgb.rgbtBlue; // Blue component
            l_texture[j+3] = alpha; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream
     
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECR );

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}
int test,ground,wall;
//<<<<<<< Updated upstream

void ResetLightPosition(float x, float y, float z)
{
	GLfloat position[] = {x, y, z, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position); // Position The Light
}

void ResetLightColor(float r, float g, float b)
{
	GLfloat color[] = {r, g, b, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color); // Light color
}

void SetupSceneLight()
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
	ResetLightColor(1.0f, 1.0f, 1.0f); // white light
	ResetLightPosition(0, 0, 10); // in front of the scene
	glEnable(GL_LIGHT0);
}

//=======
int dvdFrontTexture, dvdUpTexture;
//>>>>>>> Stashed changes
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	test = LoadTexture("rxr.bmp",100);
	ground = LoadTexture("down.bmp",100);
	wall = LoadTexture("wall.bmp",100);
//<<<<<<< Updated upstream


	SetupSceneLight();
//=======
	dvdUpTexture = LoadTexture("dvdUp.bmp", 100);
	dvdFrontTexture = LoadTexture("dvdFront.bmp", 100);
//>>>>>>> Stashed changes
	return TRUE;										// Initialization Went OK
}

float angle=0;
	
int dx=0,dy=0,dz=0;
void drawGround(int x,int y,int z,int d){
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D,ground);
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


void skybox(float x,float y,float z,float d,float dz){

	glBindTexture(GL_TEXTURE_2D,wall);
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

	glBindTexture(GL_TEXTURE_2D,wall);
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

	glBindTexture(GL_TEXTURE_2D,wall);
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

	glBindTexture(GL_TEXTURE_2D,wall);
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
//float playerX=1010,playerY=1010,playerZ=0.2;
float playerX=0, playerY=0, playerZ=0.2;

float Diff=0,Diff2=0,cameraX=0,cameraY=0,cameraZ=0;
void cameraMovement(){
	if (keys['W']){
		playerX += 1;
	}
	if (keys['S']){
		playerX -= 1;
	}
	if (keys['D']){
		playerY -= 1;
	}
	if (keys['A']){
		playerY += 1;
	}
	if (keys[VK_LEFT]){
		Diff += 5;
	}
	if (keys[VK_RIGHT]){
		Diff -= 5;
	}
	if (keys[VK_UP]){
		Diff2 += 5;
	}
	if (keys[VK_DOWN]){
		Diff2 -= 5;
	}
	if (keys['I']){
		playerZ = 10;
	}
	if (keys['U']){
		playerZ += 10;
	}
	cameraX = playerX + 5 * cos(Diff * 3.1415 / 180);
	cameraY = playerY + 5 * sin(Diff * 3.1415 / 180);
	cameraZ = playerZ + 5 * sin(Diff2 * 3.1415 / 180);
	gluLookAt(playerX,playerY,playerZ,cameraX,cameraY,cameraZ,0,0,1);
}
float rot=0,A=0.1;
auto quadr=gluNewQuadric();

void drawCircle(float x, float y, float z, float r){
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
void drawFan(float x, float y, float z){
	glTranslatef(1010,1010,9);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.5,0.5,0.5);
	for (float i=0;i<2;i+=0.01){
	drawCircle(0,0,i,2);
	}
	//gluCylinder(quadr,2,2,2,100,100);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(-1010,-1010,-9);
	for (int i = 0; i < 360; i += 60){
		glPushMatrix();
		glTranslatef(x,y,z);
		glRotatef(rot+i,0,0,1);
		glTranslatef(-x,-y,-z);
		if(keys['E']){
			A += 0.1;
		}
		if(keys['Q']){
			A -= 0.1;
		}
		if (A<0)
			A=0;
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
}

void drawBlades(float x,float y,float z){
	for (int i=0;i<360;i+=18){
		glPushMatrix();
		glTranslatef(x,y,z);
		glRotatef(i,0,0,1);
		glTranslatef(-x,-y,-z);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glVertex3f(x,y+5,z);
		glVertex3f(x,y+9,z);
		glVertex3f(x,y+9,z-10);
		glVertex3f(x,y+5,z-10);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}
void lightManager(float x, float y, float z){
	GLfloat light_diffuseH[] = { 1, 1, 1, 1 };
	GLfloat light_diffuseL[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat light_diffuseR[] = { 0.8, 0, 0, 1 };
	glTranslatef(x,y,z);
	ResetLightPosition(0,0,0);
	glTranslatef(-x,-y,-z);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	ResetLightColor(1,1,1);
	if ((int)rot%60 < 20){
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseL);
	}else{
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseH);
	}
	if (keys['B']){
		glDisable(GL_LIGHTING);
	}
	if (A < 0.1){
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuseR);
	}
}
void CPUroom(){
	lightManager(1010,1010,10);
	drawGround(1000,1000,0,20);
	skybox(1000,1000,0,20,10);
//<<<<<<< Updated upstream
	drawFan(1010,1010,10);
	drawBlades(1010,1010,5);
//=======
	drawFan(1010,1010,10);

}
/////////////////////////////////////

void drawFrontDvd(int x,int y,int z,int d){
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D,dvdFrontTexture);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+(3*d),y,z);
	glTexCoord2d(1, 1);
	glVertex3f(x+(3*d),y+d,z);
	glTexCoord2d(0, 1);
	glVertex3f(x,y+d,z);
	glEnd();
}

//float iyadrot=0;

void iyaddrawUp(int x,int y,int z,int d){
	glColor3f(0.5,0.5,0.5);
	glBindTexture(GL_TEXTURE_2D, dvdUpTexture);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(x,y,z);
	glTexCoord2d(1, 0);
	glVertex3f(x+d,y,z);
	glTexCoord2d(1, 6);
	glVertex3f(x+d,y+d,z);
	glTexCoord2d(0, 1);
	glVertex3f(x,y+d,z);
	glEnd();
}
void drawDvdHole(float x, float y,float z, float r){
	glBegin(GL_TRIANGLES);
	float px=x,py=y;
	glColor3f (0, 0, 0);
	for (float i=0;i<2*3.15;i+=0.01){
		glVertex3f(x,y,z);
		glVertex3f(px ,py,z);
		px=x+r* cos(i);
		py=y+r*sin(i);
		glVertex3f(px ,py, z);
	}
	glEnd();

//>>>>>>> Stashed changes
}

float ang = 0, randomred, randomgreen;
int b=0;
void drawRotatingFilledCircleusingTriangles(float x, float y,float z, float r){
	glPushMatrix();
	glRotatef(ang, 0, 0, 1);
	ang+=1;
	//int b = 0;
	glBegin(GL_TRIANGLES);
	float px=x,py=y;
	for (float i=0;i<2*3.14*r;i+=0.1){
		randomred = rand() % 150 ;
		randomred+=50;
		randomred/=255;

		randomgreen = rand() % 150 ;
		randomgreen+=50;
		randomgreen/=255;
		
		if(b == 0){
			glColor3f (randomred, randomgreen, 0.8);
			b++;
		}
		else if(b == 1){
			glColor3f (randomred, randomgreen, 0.8);
			b++;
		}
		else {
			glColor3f (randomred, randomgreen, 0.8);
			b=0;
		}
		glVertex3f(px ,py,z);
		px=x+r* cos(i);
		py=y+r*sin(i);
		glVertex3f(px ,py, z);
		glColor3f (1, 1, 1);
		glVertex3f(x,y,z);
	}
	glEnd();
	drawDvdHole(0, 0, -1.95, 0.8);
	
	glPopMatrix();
}
void Iyad(){
	drawRotatingFilledCircleusingTriangles(0, 0, -2, 8);
	drawFrontDvd(0, 1, 5, 5);
	iyaddrawUp(0,0,3,10);
}

////////////////////////////////
void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	glPushMatrix();

	cameraMovement();
//<<<<<<< Updated upstream
//=======
	
	gluLookAt(playerX,playerY,playerZ,cameraX,cameraY,cameraZ,0,0,1);
//>>>>>>> Stashed changes

	Iyad();
	//CPUroom();
	
	glClear(GL_DEPTH_BUFFER_BIT);

	//glPopMatrix();
	

    //DO NOT REMOVE THIS
	SwapBuffers(hDC);			
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
		case WM_PAINT: 
			DrawGLScene();
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return 0;
	
		case WM_TIMER:
			DrawGLScene();
			return 0;

		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("RedWn's Window",1280,720,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer=SetTimer(hWnd,0,50,(TIMERPROC) NULL);

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
	}

	return 0;

}
