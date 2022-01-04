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

int bar_code_line_thickness_array[20];
void barCodeLines(){
	float barCodeLineThickness;
	for(int i = 0 ; i < 20 ; i++){
		barCodeLineThickness = rand() % 30;
		barCodeLineThickness += 2;
		bar_code_line_thickness_array[i] = barCodeLineThickness;
	}
}

int dvdFrontTexture, dvdUpTexture, dvdSideTexture;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	barCodeLines();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	dvdUpTexture = LoadTexture("dvdUp.bmp", 100);
	dvdFrontTexture = LoadTexture("dvdfront.bmp", 100);
	dvdSideTexture = LoadTexture("dvdSide.bmp", 100);
	return TRUE;										// Initialization Went OK
}

float Diff=0,Diff2=0,cameraX=0,cameraY=0,cameraZ=0;
//float playerX=1010,playerY=1010,playerZ=0.2,Diff=0,Diff2=0,cameraX=0,cameraY=0,cameraZ=0;
//float playerX=1010,playerY=1010,playerZ=0.2;

float playerX = -18, playerY = 0, playerZ = -0.5f;

void redQuad(float x, float y, float z, float d){
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, z);
	
	glVertex3f(x, y + (2 * d), z);
	
	glVertex3f(x, y + (2 * d), z + d);
	
	glVertex3f(x, y, z + d);
	glEnd();
}
bool redButton = false;
void cameraMovement(){
	if (keys['W']){
		playerX += 0.2f * cos(Diff * 3.1415 / 180); 
		playerY += 0.2f * sin(Diff * 3.1415 / 180);
	}
	if (keys['S']){
		playerX -= 0.2f * cos(Diff * 3.1415 / 180); 
		playerY -= 0.2f * sin(Diff * 3.1415 / 180);
	}
	if (keys['D']){
		playerX -= 0.2f * sin(Diff * 3.1415 / 180);
		playerY -= 0.2f * cos(Diff * 3.1415 / 180);
	}
	if (keys['A']){
		playerX += 0.2f * sin(Diff * 3.1415 / 180); 
		playerY += 0.2f * cos(Diff * 3.1415 / 180);
	}
	if (keys[VK_LEFT]){
		Diff += 2;
	}
	if (keys[VK_RIGHT]){
		Diff -= 2;
	}
	if (keys[VK_UP]){
		Diff2 += 2;
	}
	if (keys[VK_DOWN]){
		Diff2 -= 2;
	}
	if (keys['U']){
		playerZ += 0.1f;
	}
	if (keys['I']){
		playerZ -= 0.1f;
	}
	if (keys['R']){
		redButton = true;
	}

	cameraX = playerX + 5 * cos(Diff * 3.1415 / 180);
	cameraY = playerY + 5 * sin(Diff * 3.1415 / 180);
	cameraZ = playerZ + 5 * sin(Diff2 * 3.1415 / 180);
	gluLookAt(playerX,playerY,playerZ,cameraX,cameraY,cameraZ,0,0,1);
}

void drawFrontDvd(int x,int y,int z,int d){
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, dvdFrontTexture);
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
void drawSideDvd(int x,int y,int z,int d){
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, dvdSideTexture);
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
void drawBackDvd(int x,int y,int z,int d){
	
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, dvdSideTexture);
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


void drawDvdUp(float x,float y,float z,float d){
	glColor3f(0.6f, 0.6f, 0.6f);
	glBindTexture(GL_TEXTURE_2D, dvdUpTexture);
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
void drawDvdGround(float x,float y,float z,float d){
	glColor3f(0.2f, 0.2f, 0.2f);
	glBindTexture(GL_TEXTURE_2D, dvdUpTexture);
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
void drawDvdHole(float x, float y,float z, float r){
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

float ang = 0, randomred, randomgreen;
int b=0;
void drawRotatingDvd(float x, float y,float z, float r){
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

float laserAng  = 0;
void dvdLaser(float x, float y, float z){
	glEnable(GL_BLEND);	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	float alpha = 0.3f;
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

void dvdBarCode(float x, float y, float z, float width, float height, float padding){
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

void dvdCylinder(float x, float y, float z, float radius, float height){
	
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


void DVD(){
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
	
	}

void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glPushMatrix();

	cameraMovement();
	DVD();

	glClear(GL_DEPTH_BUFFER_BIT);
	glPopMatrix();

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
	if (!CreateGLWindow("DVD", 1280,720,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer=SetTimer(hWnd,0,2,(TIMERPROC) NULL);

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
	}

	return 0;

}
