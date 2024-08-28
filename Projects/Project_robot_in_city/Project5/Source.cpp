

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include <texture.h>

//#include <tchar.h>
//#define _CRT_NONSTDC_NO_DEPRECATE
//#define _CRT_SECURE_NO_WARNINGS

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
GLfloat LightDir[] = { 0.0f,0.0f,-60.0f,1.0f };
GLfloat LightPos[] = { 0.0f,0.0f,-20.0f,1.0f };
GLfloat LightAmb[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat LightDiff[] = { 0.9f,0.9f,0.9f,1.0f };
GLfloat LightSpec[] = { 0.9f,0.9f,0.9f,1.0f };


GLfloat MatAmb[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat MatDif[] = { 0.6f,0.6f,0.6f,1.0f };
GLfloat MatSpec[] = { 0.2f,0.2f,0.2f,1.0f };

GLfloat MatShn[] = { 128.0f };
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 2000.0f);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity();									// Reset The Modelview Matrix
}
int Image,Im2,Im3,Im4;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.50f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	glEnable(GL_TEXTURE_2D);
	Image= LoadTexture("R.bmp");
	Im2= LoadTexture("gg.bmp");
    Im3= LoadTexture("hh.bmp");
	Im4= LoadTexture("ddddd.bmp");
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);



	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpec);


	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);
	glEnable(GL_COLOR_MATERIAL);

	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

float angle = 0;
float cameraAngle = 0.0f;
GLfloat xRotated = 0, yRotated = 0, zRotated = 0;

int mouseX = 0, mouseY = 0;
bool isClicked = 0, isRClicked = 0;
int tran = 0;
void mouse(int mouseX, int mouseY, bool isClicked, bool isRClicked)
{
	//do something here
	if (isClicked)
	{
		glTranslatef(0, 0.0, -10);

	}

}
float xx = 10;
void cude(void)
{
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);    // Color Red
	glVertex3f(1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
	glColor3f(0.50f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
	glColor3f(0.7f, 1.0f, 0.4f);
	glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
	glColor3f(1.0f, 1.0f, 0.0f);    // Color Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);    // Top Right Of The Quad (Back)
	glColor3f(1.0f, 0.3f, 0.5f);
	glVertex3f(-1.0f, -1.0f, -1.0f);    // Top Left Of The Quad (Back)
	glColor3f(1.0f, 0.2f, 0.8f);
	glVertex3f(-1.0f, 1.0f, -1.0f);    // Bottom Left Of The Quad (Back)
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(1.0f, 1.0f, -1.0f);    // Bottom Right Of The Quad (Back)
	glColor3f(0.0f, 0.0f, 1.0f);    // Color Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
	glColor3f(0.6f, 0.0f, 0.3f);
	glVertex3f(-1.0f, 1.0f, -1.0f);    // Top Left Of The Quad (Left)
	glColor3f(0.3f, 0.2f, 0.1f);
	glVertex3f(-1.0f, -1.0f, -1.0f);    // Bottom Left Of The Quad (Left)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
	glColor3f(1.0f, 0.0f, 1.0f);    // Color Violet
	glVertex3f(1.0f, 1.0f, -1.0f);    // Top Right Of The Quad (Right)
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
	glVertex3f(1.0f, -1.0f, -1.0f);    // Bottom Right Of The Quad (Right)
	glEnd();            // End Drawing The Cube

}
void sun(){
	glPushMatrix();
glRotated(angle*2,1,0,0);
	angle++;
	glTranslated(0,400,0);
	glScaled(20,20,20);
	float aa,r=1;
	GLfloat LightPos2[] = { 0.0f,400.0f,400.0f,1.0f };


	GLfloat LightAmb[] = { 1.0f,1.f,1.f,1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, LightPos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);
	glEnable(GL_LIGHT1);
	
    glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 1.0f, 0.0f);
	
	float a=0.0f;
	for (float a = 0.0f; a <= (2.0f*3.14f); a += 0.1f)
	for (aa = 0.0f; aa <= (2.0f*3.14f); aa += 0.1f)
	{
	float x =  r*cos(aa)*cos(a);
	float y =  r*sin(aa);
	float z = r*cos(aa)*sin(a);
	
	glVertex3f(x, y, z);
	glVertex3f(r*cos(aa)*cos(a+0.1), y, r*cos(aa)*sin(a+0.1));
	}
	glEnd();
	GLfloat Li[] = { 0.0f,0.f,0.2f,1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, Li);
		glEnable(GL_LIGHT1);

	
	glPopMatrix();	



}
void a()//«·«—÷
{
	glBindTexture(GL_TEXTURE_2D,Im2);
	glColor3f(0,0.5,0);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); 
	glVertex3f(-400,0,400);
	glTexCoord2d(1, 0); 
	glVertex3f(400,0,400);
	glTexCoord2d(1, 20); 
	glVertex3f(400,0,-400);
	glTexCoord2d(0,20); 
	glVertex3f(-400,0,-400);
	
	glVertex3f(-400,-20,400);
	glVertex3f(400,-20,400);
	glVertex3f(400,-20,-400);
	glVertex3f(-400,-20,-400);

	glVertex3f(-400,-20,400);
	glVertex3f(400,-20,400);
	glVertex3f(400,0,400);
	glVertex3f(-400,0,400);

	glVertex3f(-400,-20,-400);
	glVertex3f(400,-20,-400);
	glVertex3f(400,0,-400);
	glVertex3f(-400,0,-400);

	glVertex3f(400,-20,400);
	glVertex3f(400,-20,-400);
	glVertex3f(400,0,-400);
	glVertex3f(400,0,400);

		glVertex3f(-400,-20,400);
	glVertex3f(-400,-20,-400);
	glVertex3f(-400,0,-400);
	glVertex3f(-400,0,400);

	
	glEnd();
}
void house(){
		glBindTexture(GL_TEXTURE_2D,Im3);

	glBegin(GL_QUADS);
    glTexCoord2d(0, 0); 
	glVertex3f(0,0,0);
    glTexCoord2d(1, 0); 
    glVertex3f(40,0,0);
	glTexCoord2d(1, 1); 
	glVertex3f(40,40,0);
	glTexCoord2d(0, 1); 
	glVertex3f(0,40,0);

	 glTexCoord2d(0, 0); 
	glVertex3f(0,0,-40);
    glTexCoord2d(1, 0); 
    glVertex3f(40,0,-40);
	glTexCoord2d(1, 1); 
	glVertex3f(40,40,-40);
	glTexCoord2d(0, 1); 
	glVertex3f(0,40,-40);

	 glTexCoord2d(0, 0); 
	glVertex3f(0,0,-40);
    glTexCoord2d(0, 1); 
    glVertex3f(0,40,-40);
	glTexCoord2d(1, 1); 
	glVertex3f(0,40,0);
	glTexCoord2d(1, 0); 
	glVertex3f(0,0,0);

	 glTexCoord2d(0, 0); 
	glVertex3f(40,0,-40);
    glTexCoord2d(0, 1); 
    glVertex3f(40,40,-40);
	glTexCoord2d(1, 1); 
	glVertex3f(40,40,0);
	glTexCoord2d(1, 0); 
	glVertex3f(40,0,0);


	glVertex3f(0,40,0);
	glVertex3f(40,40,0);
	glVertex3f(40,40,-40);
	glVertex3f(0,40,-40);
	glEnd();


}
void aaa(){//«·‘«—⁄
	glBindTexture(GL_TEXTURE_2D,Image);
	glBegin(GL_QUADS);
			glTexCoord2d(0, 0); 
	glVertex3f(-10,0,400);
			glTexCoord2d(1, 0); 
	glVertex3f(10,0,400);
	     	glTexCoord2d(1, 20); 
	glVertex3f(10,0,-400);
	glTexCoord2d(0, 20); 
	glVertex3f(-10,0,-400);
	glEnd();


}
void face(){
		glBindTexture(GL_TEXTURE_2D,Im4);

	glPushMatrix();
	glColor3f(1,1,1);
	glTranslated(0,0,0.1);
			glBegin(GL_QUADS);
				glTexCoord2d(0, 0); 
	glVertex3f(0,0,0);
				glTexCoord2d(0, 1); 
	glVertex3f(0,4,0);
				glTexCoord2d(1, 1); 
	glVertex3f(2,4,0);
				glTexCoord2d(1, 0); 
	glVertex3f(2,0,0);
	glEnd();
	glPopMatrix();
	glColor3f(0,1,0);

}
void aa(float yy,float zz,float b,float y,float z){

		glBegin(GL_QUADS);
	glVertex3f(0,0+y+b+yy,0+z+zz);//«·ÊÃÂ
	glVertex3f(0,4+b,0);
	glVertex3f(2,4+b,0);
	glVertex3f(2,0+y+b+yy,0+z+zz);

	glVertex3f(2,0+y+b+yy,0+z+zz);//«·Ì„Ì‰
	glVertex3f(2,4+b,0);
    glVertex3f(2,4+b,-2);
	glVertex3f(2,0+y+b+yy,-2+z+zz);

	glVertex3f(2,0+y+b+yy,-2+z+zz);//«·Œ·›Ì
    glVertex3f(2,4+b,-2);
	glVertex3f(0,4+b,-2);
    glVertex3f(0,0+y+b+yy,-2+z+zz);

    glVertex3f(0,0+y+b+yy,-2+z+zz);//«·Ì”«—
    glVertex3f(0,4+b,-2);
	glVertex3f(0,4+b,0);
	glVertex3f(0,0+y+b+yy,0+z+zz);

    glVertex3f(0,4+b,0);//«·⁄·Ì«
	glVertex3f(2,4+b,0);
	glVertex3f(2,4+b,-2);
	glVertex3f(0,4+b,-2);

	glVertex3f(0,0+y+b+yy,0+z+zz);//«·”›·Ì
	glVertex3f(2,0+y+b+yy,0+z+zz);
	glVertex3f(2,0+y+b+yy,-2+z+zz);
	glVertex3f(0,0+y+b+yy,-2+z+zz);

	

glEnd();
}

GLfloat y,z,yy,zz,yyy,zzz,yyyy,zzzz,h,k,hh,movZ,movY,movX;
void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();		// Reset The Current Modelview Matri
	gluLookAt(movX, movY, movZ, 0, 0, -5, 0, 1, 0);
		if (keys['T'])
		movX += 0.1;
	if (keys['Y'])
		movX -= 0.1;
	if (keys['U'])
		movY += 0.1;
	if (keys['I'])
		movY -= 0.1;
	if (keys['O'])
		movZ += 0.1;
	if (keys['P'])
		movZ -= 0.1;

	glRotated(180,0,1,0);
	glTranslated(0,0,30+k);
		
	
	
	glRotated(hh,0,1,0);
	sun();
	glPushMatrix();
	glTranslated(2,-8,0);
    a();
	glColor3f(1,1,1);
	glTranslated(0,0.1,0);
	aaa();
	glTranslated(40,0,300);

	for(int i=0;i<10;i++)
	{house();
	glTranslated(0,0,-60);
	}
	glTranslated(-120,0,60);
	for(int i=0;i<10;i++)
	{house();
	glTranslated(0,0,60);
	}
	glPopMatrix();
	if (keys['Q']&&z<3)//«·Ìœ «·⁄·Ì«
	  {	z++;
	if(z<=0)y-=0.3; else  y+=0.3;}
		if(keys['W']&&z>-2)
      { z--;
		if(z>=0)y-=0.3; else  y+=0.3;}

		if (keys['A']&&zz<3)// «·Ìœ «·”›·Ì
	  {	zz++;
	if(zz<=0)yy-=0.3; else  yy+=0.3;}
		if(keys['S']&&zz>0)
      { zz--;
		if(zz>=0)yy-=0.3; else  yy+=0.3;}

		if (keys['Z']&&zzz<=3)// «·ﬁœ„ «·Ì„Ì‰
	  {	zzz++;
	if(zzz<=0)yyy-=0.3; else  yyy+=0.3;}
		if(keys['X']&&zzz>0)
      { zzz--;
		if(zzz>=0)yyy-=0.3; else  yyy+=0.3;}

			if (keys['N']&&zzzz<=3)//«·Ì”«— «·«ﬁœ«„
	  {	zzzz++;
	if(zzzz<=0)yyyy-=0.3; else  yyyy+=0.3;}
		if(keys['M']&&zzzz>0)
      { zzzz--;
		if(zzzz>=0)yyyy-=0.3; else  yyyy+=0.3;}

		if(zzzz==3){
			do{
			h++;
		    zzzz--;
			yyyy-=0.3;}while(zzzz>0);
		}
		if(zzz==3){
			do{
			h++;
		    zzz--;
			yyy-=0.3;}while(zzz>0);
		}
		if (keys[VK_RIGHT])
		   hh-=20;
		if (keys[VK_LEFT])
		   hh+=20;
		if (keys[VK_SUBTRACT])
			 k+=10;
		if (keys[VK_ADD])
			 k-=10;
		glTranslated(0,0,h);
		glTranslated(1,8,0);
		glScaled(1,0.5,1);
		glColor3f(0,1,0);
		aa(0,0,0,0,0);//—√”
		face();
		glScaled(1,2,1);
		glTranslated(-1,-8,0);
	glScaled(2,2,1);
	glColor3f(1,0,0);
	aa(0,0,0,0,0);//»ÿ‰
	glScaled(0.5,0.50,1);
	glTranslated(4,4,0);
	glColor3f(0,1,0);
    aa(0,0,0,y,z);//⁄·Ì« Ìœ
	glTranslated(-6,0,0);
	aa(0,0,0,y,z);//⁄·Ì« Ìœ

    glTranslated(0,-4,0+z);
	aa(yy,zz,y,y,z);//”›·Ì Ìœ
	glTranslated(6,0,0);
	aa(yy,zz,y,y,z);//”›·Ì Ìœ
	glTranslated(-4,-8,0-z);
	glScaled(0.9,2,1);
	glColor3f(1,0,0);
	aa(0,0,0,yyy,zzz);//«·ﬁœ„ 
	glTranslated(2.4,0,0);
	aa(0,0,0,yyyy,zzzz);// «·ﬁœ„
	

	glFlush();

	//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
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

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
		////////////////////////////Mouse/////////////////
	case WM_MOUSEMOVE:
	{
		mouseX = (int)LOWORD(lParam);   mouseY = (int)HIWORD(lParam);
		isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
		isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
		break;
	}
	case WM_LBUTTONUP:
		isClicked = false; 	 break;
	case WM_RBUTTONUP:
		isRClicked = false;   break;
	case WM_LBUTTONDOWN:
		isClicked = true; 	break;
	case WM_RBUTTONDOWN:
		isRClicked = true;	break;
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
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
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
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
														//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	//(LPCWSTR)
	if (!CreateGLWindow("NeHe Template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}



