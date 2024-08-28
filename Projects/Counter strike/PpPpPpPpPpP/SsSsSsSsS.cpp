#include <windows.h>		// Header File For Windows
#include <fstream>

#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include<texture.h>
#include <fstream>
#include <heightMap.h>
#include <Model_3ds.h>
#include <3DTexture.h>
#include <camera.h>
#include <TgaLoader.h>
//#include <sound.h>
//INIT initalie =INIT();
//Sound sound1;
//Sound sound2;
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default
int mouseX = 0, mouseY = 0;
bool isClicked = 0, isRClicked = 0;
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

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

float x=0,z=0,y=0;
GLfloat kk=-2;
GLfloat kkk=-2;
GLfloat C=0;
float Sx=0,Sz=0;

Model_3DS a,ant,mouse;
GLTexture m,m2,m3;
Camera MyCamera;
int i1,i2,i3,i4,i5,i6,i7,i8,table,wall,carpet,Roof,door,window,keyboard,monitor,lithium,p,uu,img;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.50f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	initalie.InitOpenAL();
/*
sound1=Sound("breakout.wav");
sound2=Sound("gun.wav");

sound2.Play();
*/


	glEnable(GL_TEXTURE_2D);
    carpet= LoadTexture("carpet.bmp");
	table=LoadTexture("table.bmp");
	wall=LoadTexture("wall.bmp");
	Roof=LoadTexture("Roof.bmp");
	door=LoadTexture("door.bmp");
	window=LoadTexture("window.bmp");
keyboard=LoadTexture("Keybaord.bmp");
monitor=LoadTexture("monitor.bmp");
	i1 = LoadTexture("Motherboard.bmp");
	i2 = LoadTexture("up.bmp");
	i3 = LoadTexture("r.bmp");
	i4 = LoadTexture("r2.bmp");
	i5 = LoadTexture("s.bmp");
	i6 = LoadTexture("cpu.bmp");
	i7 = LoadTexture("glass1.bmp");
	lithium =LoadTexture("lithium.bmp");
	img=LoadTexture("metal6.bmp");

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpec);

	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiff);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LightSpec);

	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);
	glEnable(GL_COLOR_MATERIAL);


    p =LoadTexture("p.bmp");
	uu=LoadTexture("uu.bmp");
	m.LoadBMP("tank.bmp");
	m2.LoadBMP("switch.bmp");


	a = Model_3DS();
	char ab[] = "M4a1.3ds";
	a.Load(ab);
	a.pos.x = 2.5;
	a.pos.y = -2.5;
    a.pos.z = 2.5;

	ant = Model_3DS();
	char abc[] = "Ant_3ds.3ds";
	ant.Load(abc);
	ant.pos.x = 0;
	ant.pos.y = -2;
    ant.pos.z = 0;
	ant.scale=0.005;
    ant.Materials[1].tex =m;
	mouse = Model_3DS();
	char aa[] = "uploads_files_2646883_Ice+Claw.3ds";
	mouse.Load(aa);
	mouse.pos.x = -250;
	mouse.pos.y = -4;
    mouse.pos.z = -50;
    mouse.Materials[0].tex =m2;
    mouse.scale=5;
	MyCamera = Camera();

	return TRUE;		// Initialization Went OK

}	GLfloat xx,yy,zz;
class S{
public:
	float x1,x2,z1,z2,kk1,kk2;
	void ffff(float x1,float z1,float x2,float z2,float kk1){
		this->x1=x1;
		this->z1=z1;
		this->x2=x2;
		this->z2=z2;
		this->kk1=kk1;

	}
		void ffff(float x1,float z1,float x2,float z2,float kk1,float kk2){
		this->x1=x1;
		this->z1=z1;
		this->x2=x2;
		this->z2=z2;
		this->kk1=kk1;
		this->kk2=kk2;

	}
	boolean fffb(float x,float z,float kk)
	{  if((kk>=kk1)&&(kk<=kk1+4))
		if (x1<=x && x<=x2)
			if(z1<=z && z<=z2)
		return false;
	   if((kk1==4)&&(kk>kk1))
		   if (x1<=x && x<=x2)
			if(z1<=z && z<=z2)
		return false;
	   	   if((kk>=kk1)&&(kk<=kk2)&&(0!=kk2))
		   if (x1<=x && x<=x2)
			if(z1<=z && z<=z2)
		return false;

		return true;
	}
};
	S s[200];
class Ant{
public :
	int nnn,sss,q;
	float xxxxx,yyyyy,zzzzz;
	void tr(float xxxxx,float yyyyy,float zzzzz,int nnn,int sss){
		this->xxxxx=xxxxx;
		this->zzzzz=zzzzz;
		this->yyyyy=yyyyy;
		this->nnn=nnn;
		this->sss=sss;
	
	}
	void tr(float xxxxx,float yyyyy,float zzzzz,int nnn,int sss,int q){
		this->xxxxx=xxxxx;
		this->zzzzz=zzzzz;
		this->yyyyy=yyyyy;
		this->nnn=nnn;
		this->sss=sss;
	    this->q=q;
	}


	void draw(){

		if(q==1)
		{if(nnn>0){
		glPushMatrix();
		glRotated(90,1,0,0);
		glTranslated(xxxxx,zzzzz,-yyyyy);
		glTranslated(0,-3,-5);
	    glScaled(0.2,0.2,0.2);
		ant.Draw();
		s[sss].ffff(xxxxx-2,-yyyyy-1,xxxxx+2,-yyyyy+1,zzzzz,zzzzz);
		glPopMatrix();
		}}
		else
		{
		if(nnn>0){
		glPushMatrix();
		glTranslated(xxxxx,yyyyy,zzzzz);
		ant.Draw();
		s[sss].ffff(xxxxx-5,zzzzz-3,xxxxx+5,zzzzz+3,-2+yyyyy);
		glPopMatrix();
				}}
	}
	void drawRotatedY90(){
				if(nnn>0){
		glPushMatrix();
		glTranslated(xxxxx,yyyyy,zzzzz);
		glRotated(90,0,1,0);
		ant.Draw();
		s[sss].ffff(xxxxx-5,zzzzz-3,xxxxx+5,zzzzz+3,-2+yyyyy);
		glPopMatrix();
				}
	}
	void drawRotatedY180(){
				if(nnn>0){
		glPushMatrix();
		glTranslated(xxxxx,yyyyy,zzzzz);
		glRotated(180,0,1,0);

		ant.Draw();
		s[sss].ffff(xxxxx-5,zzzzz-3,xxxxx+5,zzzzz+3,-2+yyyyy);
		glPopMatrix();
				}
	}
		void drawRotatedY270(){
				if(nnn>0){
		glPushMatrix();
		glTranslated(xxxxx,yyyyy,zzzzz);
		glRotated(270,0,1,0);
		ant.Draw();
		s[sss].ffff(xxxxx-5,zzzzz-3,xxxxx+5,zzzzz+3,-2+yyyyy);
		glPopMatrix();
				}
	}
	void kill(int hjk){
		     nnn=nnn-hjk;
			   if(nnn<=0)
		       s[sss].ffff(xxxxx-5,zzzzz-3,xxxxx+5,zzzzz+3,-20000);

	}

};
Ant an[40];
float X,Z;
GLfloat SP=1,spp=0;
void Key(bool* keys, float speed)
{    
	if(keys[VK_SPACE]&&kkk<2&&SP==1&&kk<2&&(!(x<-243&&x>-250&&z<-72&&z>-87)))
	  {  kkk+=0.025;
		 kk+=0.025;	  
		 if(kkk>=2)
		 SP=0;
   }
     if((!keys[VK_SPACE]&&kkk>-2)||SP==0)
	  { 
     kkk-=0.025;
	  kk-=0.025;
	  if(!keys[VK_SPACE]&&kkk<=-2)
		  SP=1;
   }

	 if(kkk<-2&&kk>-3)
		 {kk=-2;kkk=-2;}
	 else if(kkk<-2&&kk>-4001)
		 	 {kk=-4000;kkk=-2;}
    if(keys[VK_UP])
		C=-5;
	if(keys[VK_DOWN])
		C=0;

	boolean b=true;
	boolean bb=true;
	if ((-X+5>x || x>X-5 )&&(kk>=-2))
		b=false;
	else if((-Z+5>z || z>245 )&&(kk>=-2))
		b=false;
    else 
    for(int l=0;l<200;l++)//199
	{b=s[l].fffb(x,z,kk);
    if(b==false)break;}

	if(b){
	GLfloat i=speed;

	if (keys[VK_RIGHT]||mouseX>1100)
	{MyCamera.RotateY(-speed);y-=(speed);
	}
	if (keys[VK_LEFT]||mouseX<150)
	{MyCamera.RotateY(speed);y+=(speed);
	}
	if (keys['W'])
    {  
		if ((-X+5>x-sin(y*PIdiv180)*i || x-sin(y*PIdiv180)*i>X-5 )&&(kk>=-2))
		bb=false;
	    else if((-Z+5>z-cos(y*PIdiv180)*i || z-cos(y*PIdiv180)*i>245 )&&(kk>=-2))
		bb=false;
        else 
        for(int l=0;l<200;l++)//22
	    {bb=s[l].fffb(x-sin(y*PIdiv180)*i,z-cos(y*PIdiv180)*i,kk);
        if(bb==false)break;}
    if(bb){
	MyCamera.MoveForward(1 * speed);
	z-=cos(y*PIdiv180)*i;
    x-=sin(y*PIdiv180)*i;
	}}


	if (keys['S'])
	{if ((-X+5>x+sin(y*PIdiv180)*i || x+sin(y*PIdiv180)*i>X-5 )&&(kk>=-2))
		bb=false;
	    else if((-Z+5>z+cos(y*PIdiv180)*i || z+cos(y*PIdiv180)*i>245 )&&(kk>=-2))
		bb=false;
        else 
        for(int l=0;l<200;l++)//22
	    {bb=s[l].fffb(x+sin(y*PIdiv180)*i,z+cos(y*PIdiv180)*i,kk);
        if(bb==false)break;}
    if(bb){
		MyCamera.MoveForward(-1 * speed);
	z+=cos(y*PIdiv180)*i;
    x+=sin(y*PIdiv180)*i;
	}
	}
	if (keys['D'])
	{if ((-X+5>x+cos(y*PIdiv180)*i || x+cos(y*PIdiv180)*i>X-5 )&&(kk>=-2))
		bb=false;
	    else if((-Z+5>z-sin(y*PIdiv180)*i || z-sin(y*PIdiv180)*i>245 )&&(kk>=-2))
		bb=false;
        else 
        for(int l=0;l<200;l++)//22
	    {bb=s[l].fffb(x+cos(y*PIdiv180)*i,z-sin(y*PIdiv180)*i,kk);
        if(bb==false)break;}
    if(bb){
		MyCamera.MoveRight(1 * speed);
	z-=sin(y*PIdiv180)*i;
    x+=cos(y*PIdiv180)*i;	
	}}

	if(keys['A'])
	{if ((-X+5>x-cos(y*PIdiv180)*i || x-cos(y*PIdiv180)*i>X-5 )&&(kk>=-2))
		bb=false;
	    else if((-Z+5>z+sin(y*PIdiv180)*i || z+sin(y*PIdiv180)*i>245 )&&(kk>=-2))
		bb=false;
        else 
        for(int l=0;l<200;l++)//22
	    {bb=s[l].fffb(x-cos(y*PIdiv180)*i,z+sin(y*PIdiv180)*i,kk);
        if(bb==false)break;}
    if(bb){
	MyCamera.MoveRight(-1 * speed);
	z+=sin(y*PIdiv180)*i;
    x-=cos(y*PIdiv180)*i;
	
	}}
	}
	
	/*
	if(!b)
	{
    	if (keys['S'])
    {MyCamera.MoveForward(1 * 2);
	z-=cos(y*PIdiv180)*2;
    x-=sin(y*PIdiv180)*2;
	}
	if (keys['W'])
	{MyCamera.MoveForward(-1 * 2);
	z+=cos(y*PIdiv180)*2;
    x+=sin(y*PIdiv180)*2;
	
	}
	if (keys['A'])
	{MyCamera.MoveRight(1 * 2);
	z-=sin(y*PIdiv180)*2;
    x+=cos(y*PIdiv180)*2;	
	}
	if
		(keys['D'])
	{MyCamera.MoveRight(-1 * 2);
	z+=sin(y*PIdiv180)*2;
    x-=cos(y*PIdiv180)*2;
	
	}
	}*/
}
void DrawCpu(){
  glBindTexture(GL_TEXTURE_2D, i6);
  glPushMatrix();
  glBegin(GL_QUADS);
  
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(0, -2, 5);

  glTexCoord2f(0.0f, 1.0f);
  glVertex3d(0, -2, -5);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(10, -2, -5);

  glTexCoord2f(1.0f, 0.0f);
  glVertex3d(10, -2, 5);
  
  glEnd();

  glBegin(GL_QUADS);
  
  
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(0, 2, 5);

  glTexCoord2f(0.0f, 1.0f);
  glVertex3d(0, 2, -5);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(10, 2, -5);

  glTexCoord2f(1.0f, 0.0f);
  glVertex3d(10, 2, 5);
  
  glEnd();

  glBegin(GL_QUAD_STRIP);
  

  glVertex3d(0, 2, 5);

  glVertex3d(0, -2, 5);

  glVertex3d(10, 2, 5);

  glVertex3d(10, -2, 5);
  //

  glVertex3d(10, 2, -5);

  glVertex3d(10, -2, -5);
  //
  

  glVertex3d(0, 2, -5);

  glVertex3d(0, -2, -5);
  //
  
  glVertex3d(0, 2, 5);

  glVertex3d(0, -2, 5);

  glEnd();
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D,-1);

}

void SkyBoxm(float xxx,float yyy,float zzz){
	glPushMatrix();
	glTranslated(0,-4000,40);
	glColor3d(1,1,1);
	glBindTexture(GL_TEXTURE_2D, i1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz+150);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz+150);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz-150);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz-150);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,-4,-zzz+10);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz+10);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	/*if((x>200)&&(kk==-4000))
		kk=-2;*/
	glPopMatrix();
}
void SkyBoxmo(float xxx,float yyy,float zzz){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, i1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
     glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glPopMatrix();
}
void SkyBoxmoo(float xxx,float yyy,float zzz){
	xxx/=4;
	zzz/=4;
	glBegin(GL_QUADS);
	glVertex3f(-xxx,yyy,-zzz);
    glVertex3f(-xxx,yyy,+zzz);
	glVertex3f(-xxx,yyy+2,+zzz);
	glVertex3f(-xxx,yyy+2,-zzz);

	glVertex3f(+xxx,yyy,-zzz);
    glVertex3f(+xxx,yyy,+zzz);
	glVertex3f(+xxx,yyy+2,+zzz);
	glVertex3f(+xxx,yyy+2,-zzz);

	glVertex3f(-xxx,yyy,+zzz);
    glVertex3f(-xxx,yyy+2,+zzz);
	glVertex3f(+xxx,yyy+2,+zzz);
	glVertex3f(+xxx,yyy,+zzz);

	glVertex3f(-xxx,yyy,-zzz);
    glVertex3f(-xxx,yyy+2,-zzz);
	glVertex3f(+xxx,yyy+2,-zzz);
	glVertex3f(+xxx,yyy,-zzz);

	glVertex3f(-xxx,yyy+2,-zzz);
    glVertex3f(-xxx,yyy+2,+zzz);
	glVertex3f(+xxx,yyy+2,+zzz);
	glVertex3f(+xxx,yyy+2,-zzz);
	glEnd();
}
void A(){
glColor3f(1,1,1);

float m,n;
glBegin(GL_QUADS);
for (float i=0;i<3.14*2;i+=0.4)
{  m=0.75*cos(i);
   n=0.75*sin(i);

   glVertex3f(m,-4,n);
   glVertex3f(m,2,n);
   m=0.75*cos(i+0.4);
   n=0.75*sin(i+0.4);
   glVertex3f(m,2,n);
   glVertex3f(m,-4,n);
}
glEnd();
}

void SkyBoxmm(float xxx,float yyy,float zzz){
	s[90].ffff(-600.1,-160.1,-199.9,-159.9,-4000);
	s[91].ffff(-600.1,239.9,-449.9,240.1,-4000);
	s[92].ffff(-350.1,239.9,-199.9,240.1,-4000);
	s[93].ffff(-600.1,-159.9,-599.9,239.9,-4000);

	glPushMatrix();
	glTranslated(-400.1,-4000,40);
	glColor3f(1,1,0.3);
	glBindTexture(GL_TEXTURE_2D, i1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx+150,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx+150,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glEnd();
	//
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx-150,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx-150,yyy,+zzz);
	glEnd();


	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);

	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	if((x>200)&&(kk==-4000))
		kk=-2; 
	glPopMatrix();
}
void SkyBoxmmm(float xxx,float yyy,float zzz){
	
	s[163].ffff(-200.1,240,-199.9,640,-4000);
	s[164].ffff(-600.1,639.9,-199.9,640.1,-4000);
	s[165].ffff(-600.1,240,-599.9,640.1,-4000);
	glPushMatrix();
	glTranslated(-400.1,-4000,440.1);
	glColor3f(0,0,1);
	glBindTexture(GL_TEXTURE_2D, i1);//ÓØÍ
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glEnd();
	//
	glBindTexture(GL_TEXTURE_2D,-1);


	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);

	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

		glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i2);//ÓØÍ
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	if((x>200)&&(kk==-4000))
		kk=-2; 
	glPopMatrix();
}

void w()//weapon & +
{

	glPushMatrix();	//weapon
	glScaled(0.5,0.5,0.5);
	glRotated(10,1,1,0);
    a.Draw();
	glBindTexture(GL_TEXTURE_2D,-1);
		if(isClicked)
	{ 	
    glTranslated(xx,yy,zz);
				//sound2.Play();

	glBegin(GL_LINES);
	glVertex3f(2.5,-1.0,2.5);
	glVertex3f(2,-0.7,2.5);
		glEnd();
		if(xx>-2&&yy<0.7&&zz>-2.5){
		xx-=0.05;
		 yy+=0.014; 
		 zz-=0.05;}
		}

		if(!isClicked)
	{		//sound2.Stop();
		xx=0;yy=0;zz=0;
		}
	glPopMatrix();

	glColor3f(1,1,1);
	glPushMatrix();//+
	glTranslated(0,0,4.0);
	glScaled(0.15,0.15,0);
	glBegin(GL_LINES);
	glVertex3f(0,0.01,0);
	glVertex3f(0,0.10,0);
	glVertex3f(0,-0.10,0);
	glVertex3f(0,-0.01,0);
	glVertex3f(-0.10,0,0);
	glVertex3f(-0.01,0,0);
	glVertex3f(0.10,0,0);
	glVertex3f(0.01,0,0);
	glEnd();
	glPopMatrix();
}
void Room(float xxx,float yyy,float zzz)
{
	glColor3d(1,1,1);
	glBindTexture(GL_TEXTURE_2D, carpet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-100,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-100,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-100,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-100,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-100,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-100,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-100,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-100,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, door);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-500,-100,-zzz+0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-100,-100,-zzz+0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-100,yyy-100,-zzz+0.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-500,yyy-100,-zzz+0.1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, window);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(200,100,-zzz+0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(500,100,-zzz+0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(500,yyy-150,-zzz+0.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(200,yyy-150,-zzz+0.1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-100,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-100,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,-100,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-100,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,Roof);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

}
void Table(float xxx,float zzz){
	X=xxx;
	Z=zzz;
	glBindTexture(GL_TEXTURE_2D, table);
	glPushMatrix();
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,250);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,250);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,-1);

}
void f1(){

glColor3f(1,1,1);
glBindTexture(GL_TEXTURE_2D, p);

float m,n,nn,mm;
glBegin(GL_TRIANGLES);
for (float i=0;i<3.14*2;i+=0.4)
{  m=0.75*cos(i);
   n=0.75*sin(i);
   glTexCoord2d(0.55, 0.52); 
   glVertex3f(0,0,0);
  		nn=0.55-(n/2);
		mm=0.52-(m/2);
  	glTexCoord2d(nn, mm); 
   glVertex3f(n,0,m);
   m=0.75*cos(i+0.4);
   n=0.75*sin(i+0.4);
     	nn=0.55-(n/2);
		mm=0.52-(m/2);
   	glTexCoord2d(nn, mm); 
    glVertex3f(n,0,m);
}
glEnd();
glBegin(GL_QUADS);
for (float i=0;i<3.14*2;i+=0.4)
{  m=0.75*cos(i);
   n=0.75*sin(i);

   glVertex3f(m,-2,n);
   glVertex3f(m,0,n);
   m=0.75*cos(i+0.4);
   n=0.75*sin(i+0.4);
   glVertex3f(m,0,n);
   glVertex3f(m,-2,n);
}
glEnd();
	glBindTexture(GL_TEXTURE_2D, -1);

}
void ff1(){
	glBindTexture(GL_TEXTURE_2D, -1);
	glPushMatrix();
	glTranslated(0,-4003,0);
	glPushMatrix();

	int oo=0;
	for(int o=58;o<63;o++)
{	glPushMatrix();
	glScaled(4,1,4);
	s[o].ffff(-3,-3+oo,3,3+oo,-4000);
	f1();
	glPopMatrix();
	oo+=10;
	glTranslated(0,0,10);
	}
	glPopMatrix();
	glTranslated(50,0,0);
	oo=0;
	for(int o=63;o<68;o++)
{	glPushMatrix();
	glScaled(4,1,4);
	s[o].ffff(47,-3+oo,53,3+oo,-4000);
	f1();
	glPopMatrix();
	oo+=10;
	glTranslated(0,0,10);
	}
	glPopMatrix();
}
void f2(){
	
glColor3f(1,1,1);
float m,n,nn,mm;
glBindTexture(GL_TEXTURE_2D, lithium);
glBegin(GL_TRIANGLES);
for (float i=0;i<3.14*2;i+=0.4)
{  m=0.75*cos(i);
   n=0.75*sin(i);
   glTexCoord2d(0.55, 0.52); 
   glVertex3f(0,0,0);
  		nn=0.55-(n/2);
		mm=0.52-(m/2);
  	glTexCoord2d(nn, mm); 
   glVertex3f(n,0,m);
   m=0.75*cos(i+0.4);
   n=0.75*sin(i+0.4);
     	nn=0.55-(n/2);
		mm=0.52-(m/2);
   	glTexCoord2d(nn, mm); 
    glVertex3f(n,0,m);
}
glEnd();
glColor3f(0.5,0.5,0.5);
glBegin(GL_QUADS);
for (float i=0;i<3.14*2;i+=0.4)
{  m=0.75*cos(i);
   n=0.75*sin(i);

   glVertex3f(m,-2,n);
   glVertex3f(m,0,n);
   m=0.75*cos(i+0.4);
   n=0.75*sin(i+0.4);
   glVertex3f(m,0,n);
   glVertex3f(m,-2,n);
}
glEnd();

	glBindTexture(GL_TEXTURE_2D, -1);

}
void ff2(){
	glPushMatrix();
	glTranslated(-100,-4000,-50);
	glScaled(3,2,3);
	s[74].ffff(-103,-53,-97,-47,-4000);
	f2();
	glPopMatrix();

}
void f3(){
		glEnable(GL_BLEND);
	    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
glColor3f(0.1,0.1,0.1);

	glBegin(GL_QUADS);
	glVertex3f(-5,-2,-5);
	glVertex3f(-5,0,-5);
	glVertex3f(5,0,-5);
	glVertex3f(5,-2,-5);

	glVertex3f(-5,-2,5);
	glVertex3f(-5,0,5);
	glVertex3f(5,0,5);
	glVertex3f(5,-2,5);

	glVertex3f(5,-2,5);
	glVertex3f(5,0,5);
	glVertex3f(5,0,-5);
	glVertex3f(5,-2,-5);

	glVertex3f(-5,-2,5);
	glVertex3f(-5,0,5);
	glVertex3f(-5,0,-5);
	glVertex3f(-5,-2,-5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); 
	glVertex3f(-5,0,5);
	glTexCoord2d(0, 0); 
	glVertex3f(-5,0,-5);
	glTexCoord2d(1, 0); 
	glVertex3f(5,0,-5);
	glTexCoord2d(1, 1); 
	glVertex3f(5,0,5);
	glEnd();
	glColor3f(0.5,0.5,0);
	glPushMatrix();
	glScaled(0.8,0.8,0.8);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); 
	glVertex3f(-5,0,5);
	glTexCoord2d(0, 0); 
	glVertex3f(-5,0,-5);
	glTexCoord2d(1, 0); 
	glVertex3f(5,0,-5);
	glTexCoord2d(1, 1); 
	glVertex3f(5,0,5);
	glEnd();
	glPopMatrix();

		glColor4f(0.8,0.8,0.8,0.2);
	glPushMatrix();
	for(int i=0;i<9;i++){
    if(i==4)
		{glTranslated(-1,0,0); continue;}
	glBegin(GL_QUADS);
	glVertex3f(4,-2,5);
	glVertex3f(4,-0.5,5);
	glVertex3f(4,-0.5,6);
	glVertex3f(4,-2,6);
	glEnd();
	glTranslated(-1,0,0);
}
	glPopMatrix();
	glPushMatrix();
	for(int i=0;i<9;i++){
    if(i==4)
		{glTranslated(-1,0,0); continue;}
	glBegin(GL_QUADS);
	glVertex3f(4,-2,-5);
	glVertex3f(4,-0.5,-5);
	glVertex3f(4,-0.5,-6);
	glVertex3f(4,-2,-6);
	glEnd();
	glTranslated(-1,0,0);
}
	glPopMatrix();
		glPushMatrix();
	for(int i=0;i<9;i++){
    if(i==4)
		{glTranslated(0,0,-1); continue;}
	glBegin(GL_QUADS);
	glVertex3f(5,-2,4);
	glVertex3f(5,-0.5,4);
	glVertex3f(6,-0.5,4);
	glVertex3f(6,-2,4);
	glEnd();
	glTranslated(0,0,-1);
}
	glPopMatrix();
			glPushMatrix();
	for(int i=0;i<9;i++){
    if(i==4)
		{glTranslated(0,0,-1); continue;}
	glBegin(GL_QUADS);
	glVertex3f(-5,-2,4);
	glVertex3f(-5,-0.5,4);
	glVertex3f(-6,-0.5,4);
	glVertex3f(-6,-2,4);
	glEnd();
	glTranslated(0,0,-1);
}
	glColor3f(1,1,1);
	glPopMatrix();



}
void ff3(){
	
	glPushMatrix();
	glTranslated(-20,-4002,20);
	int oo=0;
	for(int o=68;o<74;o++){
	s[o].ffff(-25-oo,15,-15-oo,25,-4000);
	f3();
	oo+=30;
	glTranslated(-30,0,0);
	}
	glPopMatrix();

}
void f4(){
	glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.1,0.1,0.1,0.5);

	glBegin(GL_QUADS);
	glVertex3f(-5,-2,-2);
	glVertex3f(-5,0,-2);
	glVertex3f(5,0,-2);
	glVertex3f(5,-2,-2);

	glVertex3f(-5,-2,2);
	glVertex3f(-5,0,2);
	glVertex3f(5,0,2);
	glVertex3f(5,-2,2);

	glVertex3f(5,-2,2);
	glVertex3f(5,0,2);
	glVertex3f(5,0,-2);
	glVertex3f(5,-2,-2);

	glVertex3f(-5,-2,2);
	glVertex3f(-5,0,2);
	glVertex3f(-5,0,-2);
	glVertex3f(-5,-2,-2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); 
	glVertex3f(-5,0,2);
	glTexCoord2d(0, 0); 
	glVertex3f(-5,0,-2);
	glTexCoord2d(1, 0); 
	glVertex3f(5,0,-2);
	glTexCoord2d(1, 1); 
	glVertex3f(5,0,2);
	glEnd();

		glColor4f(0.8,0.8,0,0.2);
	glPushMatrix();
	for(int i=0;i<9;i++){
    if(i==4)
		{glTranslated(-1,0,0); continue;}
	glBegin(GL_QUADS);
	glVertex3f(4,-2,2);
	glVertex3f(4,-0.5,2);
	glVertex3f(4,-0.5,3);
	glVertex3f(4,-2,3);
	glEnd();
	glTranslated(-1,0,0);
}
	glPopMatrix();
	glPushMatrix();
	for(int i=0;i<9;i++){
    if(i==4)
		{glTranslated(-1,0,0); continue;}
	glBegin(GL_QUADS);
	glVertex3f(4,-2,-2);
	glVertex3f(4,-0.5,-2);
	glVertex3f(4,-0.5,-3);
	glVertex3f(4,-2,-3);
	glEnd();
	glTranslated(-1,0,0);
}
	glColor3f(1,1,1);
	glPopMatrix();



}
void ff4(){
	
	glPushMatrix();
	glTranslated(-20,-4002,120);
	int oo=0;
	for(int o=75;o<81;o++){
	s[o].ffff(-25-oo,115,-15-oo,125,-4000);
	f4();
	oo+=30;
	glTranslated(-30,0,0);
	}
	glPopMatrix();
}
void f5(){
	glColor3f(1,1,1);
	  glBindTexture(GL_TEXTURE_2D, uu);

	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); 
	glVertex3f(-5,-2,-2);
	glTexCoord2d(0, 5); 
	glVertex3f(-5,0,-2);
	glTexCoord2d(5, 5); 
	glVertex3f(5,0,-2);
	glTexCoord2d(5, 0); 
	glVertex3f(5,-2,-2);
	glTexCoord2d(0, 0); 
	glVertex3f(-5,-2,2);
	glTexCoord2d(0, 5); 
	glVertex3f(-5,0,2);
    glTexCoord2d(5, 5); 
	glVertex3f(5,0,2);
	glTexCoord2d(5, 0); 
	glVertex3f(5,-2,2);

	glTexCoord2d(0, 0); 
	glVertex3f(5,-2,2);
    glTexCoord2d(0, 5); 
	glVertex3f(5,0,2);
	glTexCoord2d(5, 5); 
	glVertex3f(5,0,-2);
	glTexCoord2d(5, 0);
	glVertex3f(5,-2,-2);

	glTexCoord2d(0, 0);
	glVertex3f(-5,-2,2);
	glTexCoord2d(0, 5);
	glVertex3f(-5,0,2);
	glTexCoord2d(5, 5);
	glVertex3f(-5,0,-2);
	glTexCoord2d(5, 0);
	glVertex3f(-5,-2,-2);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); 
	glVertex3f(-5,0,2);
	glTexCoord2d(0, 5); 
	glVertex3f(-5,0,-2);
	glTexCoord2d(5, 5); 
	glVertex3f(5,0,-2);
	glTexCoord2d(5, 0); 
	glVertex3f(5,0,2);
	glEnd();	

}
void ff5(){
		glPushMatrix();
		s[88].ffff(-10,145,50,155,-4000);
		glTranslated(20,-3994,150);	
		glPushMatrix();
		glScaled(6,5,2);
		f5();
		glPopMatrix();
	    glTranslated(0,0,-250);	
		glScaled(6,5,2);
	    s[89].ffff(-10,-105,50,-95,-4000);
	    f5();
	    glPopMatrix();

}
void l1(){
	float zzzz,zzzz2,yyyy,yyyy2;
	glBegin(GL_QUADS);
	for(float a=0;a<3.14*2;a+=0.4)
	{
     zzzz = 0.7*cos(a)-246;
     zzzz2= 0.7*cos(a+0.4)-246;
     yyyy = 0.7*sin(a)-1;
     yyyy2=0.7*sin(a+0.4)-1;
glColor3f(1,0.3,0);
glVertex3f(-120,yyyy,zzzz);
glVertex3f(-120, yyyy2, zzzz2);
glVertex3f(120,yyyy2,zzzz2);
glVertex3f(120,yyyy, zzzz);
     yyyy+=0.5;
     yyyy2+=0.5;
     zzzz = 0.7*cos(a)-248;
     zzzz2= 0.7*cos(a+0.4)-248;
glColor3f(0.2,0.8,0.2);
glVertex3f(-120,yyyy,zzzz);
glVertex3f(-120, yyyy2, zzzz2);
glVertex3f(120,yyyy2,zzzz2);
glVertex3f(120,yyyy, zzzz);
	}
	glEnd();
}
void l2(){

		glColor3f(1,0.549,0);
		s[2].ffff(-120,-245.1,120,-244.9,-2);
		glColor3f(0.502,0,0);
	glBegin(GL_QUADS);
	glVertex3f(-120,-4,-245);
		glVertex3f(-120,2,-245);
			glVertex3f(120,2,-245);
				glVertex3f(120,-4,-245);

    glVertex3f(-120,-4,-249.9);
		glVertex3f(-120,2,-249.9);
			glVertex3f(120,2,-249.9);
				glVertex3f(120,-4,-249.9);

     glVertex3f(-120,2,-249.9);
		glVertex3f(120,2,-249.9);
			glVertex3f(120,2,-245);
				glVertex3f(-120,2,-245);
    
	  glVertex3f(-120,-3.9,-249.9);
		glVertex3f(120,-3.9,-249.9);
			glVertex3f(120,-3.9,-245);
				glVertex3f(-120,-3.9,-245);
	glEnd();
	
}
void m1(){
	    glPushMatrix();
		glEnable(GL_BLEND);
	    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		s[153].ffff(-99.9,-260.1,200.1,-254.9,5,60);
		glColor4f(1,1,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-100,4,-255.1);
		glVertex3f(-100,60,-255.1);
		glVertex3f(200,60,-255.1);
		glVertex3f(200,4,-255.1);

		glVertex3f(-100,4,-259.9);
		glVertex3f(-100,60,-259.9);
		glVertex3f(200,60,-259.9);
		glVertex3f(200,4,-259.9);

		glVertex3f(-100,4,-255.1);
		glVertex3f(-100,4,-259.9);
		glVertex3f(-100,60,-259.9);
		glVertex3f(-100,60,-255.1);

		glVertex3f(200,4,-255.1);
		glVertex3f(200,4,-259.9);
		glVertex3f(200,60,-259.9);
		glVertex3f(200,60,-255.1);

		glVertex3f(-100,4,-255.1);
		glVertex3f(-100,4,-259.9);
		glVertex3f(200,4,-259.9);
		glVertex3f(200,4,-255.1);

		glVertex3f(-100,60,-255.1);
		glVertex3f(-100,60,-259.9);
		glVertex3f(200,60,-259.9);
		glVertex3f(200,60,-255.1);
		glEnd();
		glPopMatrix();
}
void m22(){
    glPushMatrix();
		glEnable(GL_BLEND);
	    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		s[154].ffff(-99.9,-260.1,200.1,-254.9,120,190);
		glColor4f(1,0,0,0);
		glBegin(GL_QUADS);
		glVertex3f(-100,120,-255.1);
		glVertex3f(-100,190,-255.1);
		glVertex3f(200,190,-255.1);
		glVertex3f(200,120,-255.1);

		glVertex3f(-100,120,-259.9);
		glVertex3f(-100,190,-259.9);
		glVertex3f(200,190,-259.9);
		glVertex3f(200,120,-259.9);

		glVertex3f(-100,120,-255.1);
		glVertex3f(-100,120,-259.9);
		glVertex3f(-100,190,-259.9);
		glVertex3f(-100,190,-255.1);

		glVertex3f(200,120,-255.1);
		glVertex3f(200,120,-259.9);
		glVertex3f(200,190,-259.9);
		glVertex3f(200,190,-255.1);

		glVertex3f(-100,120,-255.1);
		glVertex3f(-100,120,-259.9);
		glVertex3f(200,120,-259.9);
		glVertex3f(200,120,-255.1);

		glVertex3f(-100,190,-255.1);
		glVertex3f(-100,190,-259.9);
		glVertex3f(200,190,-259.9);
		glVertex3f(200,190,-255.1);
		glEnd();
		glPopMatrix();

}
void m33(){
    glPushMatrix();
		glEnable(GL_BLEND);
	    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		s[155].ffff(-50.1,-260.1,-39.9,-254.9,110,120);
		glColor4f(0,0,1,0.4);
		glBegin(GL_QUADS);
		glVertex3f(-50,120,-255.1);
		glVertex3f(-50,110,-255.1);
		glVertex3f(-40,110,-255.1);
		glVertex3f(-40,120,-255.1);

		glVertex3f(-50,120,-259.9);
		glVertex3f(-50,110,-259.9);
		glVertex3f(-40,110,-259.9);
		glVertex3f(-40,120,-259.9);

		glVertex3f(-50,120,-255.1);
		glVertex3f(-50,120,-259.9);
		glVertex3f(-50,110,-259.9);
		glVertex3f(-50,110,-255.1);

		glVertex3f(-40,120,-255.1);
		glVertex3f(-40,120,-259.9);
		glVertex3f(-40,110,-259.9);
		glVertex3f(-40,110,-255.1);

		glVertex3f(-50,120,-255.1);
		glVertex3f(-50,120,-259.9);
		glVertex3f(-40,120,-259.9);
		glVertex3f(-40,120,-255.1);

		glVertex3f(-50,110,-255.1);
		glVertex3f(-50,110,-259.9);
		glVertex3f(-40,110,-259.9);
		glVertex3f(-40,110,-255.1);
		glEnd();
		glPopMatrix();

}
void l3(){
	
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, keyboard);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-200,2,-50);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(200,2,-50);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(200,2,-250);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-200,2,-250);
    glEnd();


	glBindTexture(GL_TEXTURE_2D,-1);
	glColor3f(0.312,0.312,0.312);
	s[23].ffff(-200,-50.2,200,-49.8,-2);
	s[1].ffff(-200,-250.2,200,-249.8,-2);

	glBegin(GL_QUADS);
	glVertex3f(-200,-4,-50);
	glVertex3f(200,-4,-50);
	glVertex3f(200,2,-50);
	glVertex3f(-200,2,-50);
	
	glVertex3f(-200,-4,-250);
	glVertex3f(200,-4,-250);
	glVertex3f(200,2,-250);
	glVertex3f(-200,2,-250);

	glColor3f(0.412,0.412,0.412);
	glVertex3f(-200,-3.99,-50);
	glVertex3f(200,-3.99,-50);
	glVertex3f(200,-3.99,-250);
	glVertex3f(-200,-3.99,-250);
	glEnd();

	glColor3f(0,0,0);//m


	glBegin(GL_QUADS);
	glVertex3f(-150,-2,-245);
	glVertex3f(-120,-2,-245);
	glVertex3f(-120,2,-260);
	glVertex3f(-150,2,-260);

	glVertex3f(-150,1,-245);
	glVertex3f(-120,1,-245);
	glVertex3f(-120,5,-260);
	glVertex3f(-150,5,-260);

	glVertex3f(-150,-2,-245);
	glVertex3f(-120,-2,-245);
	glVertex3f(-120,1,-245);
	glVertex3f(-150,1,-245);

	glVertex3f(-150,2,-260);
	glVertex3f(-120,2,-260);
	glVertex3f(-120,5,-260);
	glVertex3f(-150,5,-260);

	glVertex3f(-150,2,-260);
	glVertex3f(-150,5,-260);
	glVertex3f(-150,1,-245);
	glVertex3f(-150,-2,-245);

	glVertex3f(-120,2,-260);
	glVertex3f(-120,5,-260);
	glVertex3f(-120,1,-245);
	glVertex3f(-120,-2,-245);
	////////
	glVertex3f(150,-2,-245);
	glVertex3f(120,-2,-245);
	glVertex3f(120,2,-260);
	glVertex3f(150,2,-260);

	glVertex3f(150,1,-245);
	glVertex3f(120,1,-245);
	glVertex3f(120,5,-260);
	glVertex3f(150,5,-260);

	glVertex3f(150,-2,-245);
	glVertex3f(120,-2,-245);
	glVertex3f(120,1,-245);
	glVertex3f(150,1,-245);

	glVertex3f(150,2,-260);
	glVertex3f(120,2,-260);
	glVertex3f(120,5,-260);
	glVertex3f(150,5,-260);

	glVertex3f(150,2,-260);
	glVertex3f(150,5,-260);
	glVertex3f(150,1,-245);
	glVertex3f(150,-2,-245);

	glVertex3f(120,2,-260);
	glVertex3f(120,5,-260);
	glVertex3f(120,1,-245);
	glVertex3f(120,-2,-245);
	glEnd();
	s[24].ffff(-205,-255.1,201,-254.9,4);
	s[25].ffff(-205,-260.1,201,-259.9,4);
	glBegin(GL_QUADS);//M
	glVertex3f(-200,2,-260);
	glVertex3f(-200,200,-260);
	glVertex3f(200,200,-260);
	glVertex3f(200,2,-260);

	glVertex3f(-200,2,-255);
	glVertex3f(-200,200,-255);
	glVertex3f(200,200,-255);
	glVertex3f(200,2,-255);

	glVertex3f(-200,2,-255);
	glVertex3f(200,2,-255);
	glVertex3f(200,2,-260);
	glVertex3f(-200,2,-260);

		glVertex3f(-200,200,-255);
	glVertex3f(200,200,-255);
	glVertex3f(200,200,-260);
	glVertex3f(-200,200,-260);
	glEnd();
	if(z>-254.9){
	glBindTexture(GL_TEXTURE_2D,monitor);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-190,20,-254.9);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-190,180,-254.9);		
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(190,180,-254.9);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(190,20,-254.9);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);}
}
void drawcube(double w , double h , double l , int pp, int ppp , int pppp){
	glPushMatrix();
	glTranslated(pp,ppp,pppp);
	glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,img);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(-w/2, 0, l/2);
	glTexCoord2d(1,0);
    glVertex3d(w/2, 0, l/2);
	glTexCoord2d(1,1);
    glVertex3d(w/2 , 0, -l/2 );
	glTexCoord2d(0,1);
    glVertex3d(-w/2 , 0 , -l/2 );
	glEnd(); //down
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(w /2, 0 , l/2);
	glTexCoord2d(1,0);
	glVertex3d( w/2 , 0 , -l/2);
	glTexCoord2d(1,1);
	glVertex3d(w/2 , h/2 , -l/2);
	glTexCoord2d(0,1);
	glVertex3d(w/2 , h/2 , l/2);
	glEnd(); //left
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
    glVertex3d(-w/2,0,l/2);
	glTexCoord2d(1,0);
	glVertex3d(-w/2,0,-l/2);
	glTexCoord2d(1,1);
	glVertex3d(-w/2 ,h/2 , -l/2);
	glTexCoord2d(0,1);
	glVertex3d(-w/2, h/2, l/2);
	glEnd(); //righttt
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
    glVertex3d(-w/2, 0 , -l/2);
	glTexCoord2d(1,0);
    glVertex3d(w/2, 0, -l/2);
	glTexCoord2d(1,1);
	glVertex3d(w/2 ,h/2, -l/2);
	glTexCoord2d(0,1);
	glVertex3d(-w/2,h/2,-l/2);
	glEnd(); //backk
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(-w/2,0, l/2);
	glTexCoord2d(1,0);
	glVertex3d(w/2 ,0 , l/2);
	glTexCoord2d(1,1);
    glVertex3d(w/2,h/2, l/2);
	glTexCoord2d(0,1);
	glVertex3d(-w/2, h/2, l/2);
	glEnd(); //frontt
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(-w/2, h/2 , l/2);
	glTexCoord2d(1,0);
	glVertex3d(w/2, h/2 , l/2);
	glTexCoord2d(1,1);
	glVertex3d(w/2 , h/2 , -l/2);
	glTexCoord2d(0,1);
	glVertex3d(-w/2 , h/2 , -l/2);
	
	glEnd(); ///up

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,-1);
	glColor3f(1,1,1);

}
void drawcubee(){
int oo=0;
	for(int o=166;o<176;o++)
	{
	s[o].ffff(-9-595,-17+260+oo,9-595,-3+260+oo,-4000);
	glPushMatrix();
	glTranslated(-593,-4000,280+oo);
	glTranslated(0,-4,3);
	glScaled(10,10,10);
	glPushMatrix();
	glTranslated(0,0,-3);
	drawcube(1,1.8,1,0,0,0);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.5,0,-3);
	drawcube(0.1,2,1.4,-1,0,0);
	glPopMatrix();
	glPopMatrix();
	oo+=40;
	}
}
	GLfloat aa=-4;
	GLfloat f=0;
    GLfloat kkkk=-2;
void DrawBuilding()
{ 
  glBindTexture(GL_TEXTURE_2D, i7);
  	glColor3f(1,0.843,0);

  glBegin(GL_QUAD_STRIP);
  
  glNormal3d(0, 0, 1);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(1, 1, 1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(1, -1, 1);
  
  glNormal3d(0, 0, -1);    

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(-1, 1, 1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(-1, -1, 1);
  
  glNormal3d(1, 0, 0);  

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(-1, 1, -1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(-1, -1, -1);
  //
  
  glNormal3d(0, 0, -1);    

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(1, 1, -1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(1, -1, -1);
  
  
  glNormal3d(-1, 0, 0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(1, 1, 1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(1, -1, 1);
  
  glEnd();
  
  glBegin(GL_QUADS);
  
  glNormal3d(0, -1, 0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(-1, -1, 1);

  glTexCoord2f(0.0f, 1.0f);
  glVertex3d(-1, -1, -1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(1, -1, -1);

  glTexCoord2f(1.0f, 0.0f);
  glVertex3d(1, -1, 1);
  
  
  glNormal3d(0, 1, 0);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(-1, 1, 1);

  glTexCoord2f(0.0f, 1.0f);
  glVertex3d(-1, 1, -1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(1, 1, -1);

  glTexCoord2f(1.0f, 0.0f);
  glVertex3d(1, 1, 1);

  glEnd();
}
void DrawPin(){
	glPushMatrix();
	glTranslated(0,4,0);
	glScaled(1,3,1);
	DrawBuilding();
	glScaled(1,0.25,1);
	glTranslated(0,-6,0);
	glScaled(5,5,5);
    DrawBuilding();
	glPopMatrix();
}
void d(){
		glPushMatrix();
	glTranslated(-180,-4000,200);
	int oo=0;
	glPushMatrix();
	for(int o=28;o<38;o++)
{	s[o].ffff(-185+oo,195,-175+oo,205,-4000);
	DrawPin();
	glTranslated(40,0,0);
	oo+=40;
}
	glPopMatrix();
	glTranslated(0,0,-330);
	oo=0;
	for(int o=38;o<48;o++)
{	s[o].ffff(-185+oo,-135,-175+oo,-125,-4000);
	DrawPin();
	glTranslated(40,0,0);
	oo+=40;
}
	glPopMatrix();
	}
void l4(){
	glColor3f(1,0,0);
	glBegin(GL_QUADS);//ÇáÕãÚÏ
	glVertex3f(-201,aa,-255);
	glVertex3f(-201,aa,-260);
	glVertex3f(-210,aa,-260);
	glVertex3f(-210,aa,-255);

	glVertex3f(-201,aa+0.5,-255);
	glVertex3f(-201,aa+0.5,-260);
	glVertex3f(-210,aa+0.5,-260);
	glVertex3f(-210,aa+0.5,-255);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	glVertex3f(-201,aa,-260);
	glVertex3f(-201,aa+0.5,-260);
	glVertex3f(-210,aa+0.5,-260);
	glVertex3f(-210,aa,-260);

	glVertex3f(-201,aa,-255);
	glVertex3f(-201,aa+0.5,-255);
	glVertex3f(-210,aa+0.5,-255);
	glVertex3f(-210,aa,-255);

	glVertex3f(-201,aa,-255);
	glVertex3f(-201,aa+0.5,-255);
	glVertex3f(-201,aa+0.5,-260);
	glVertex3f(-201,aa,-260);

	glVertex3f(-210,aa,-255);
	glVertex3f(-210,aa+0.5,-255);
	glVertex3f(-210,aa+0.5,-260);
	glVertex3f(-210,aa,-260);
	glEnd();
	
	if((-202>x)&&(x>-209)&&(-256>z)&&(z>-259)&&(aa<200)&&(f==0)&&(!keys['L']))
		{aa+=0.05;kk+=0.05;kkkk+=0.05;}
	else if (aa>=200)
		   f=1;

	
	if((-202>x)&&(x>-209)&&(-256>z)&&(z>-259)&&(aa>-4)&&(f==1))
		{aa-=0.05;kk-=0.05;kkkk-=0.05;}
	else if (aa<=-4)
		   f=0;
	

     if(!((202>x)&&(x>-211)&&(-254>z)&&(z>-261))&&kkkk>-2)
	  { 
     kkkk-=0.2;
	  kk-=0.2;
	  aa-=0.2;
      }

	 if(((202>x)&&(x>-211)&&(-254>z)&&(z>-261))&&kkkk>-2&&keys['H']&&kkkk<=204)
	  {  float b;
	 int l;
		  for(l=153;l<156;l++)
	      { b=s[l].fffb(x,z,kk);
		  if(!b)
     { kkkk-=0.3;
	  kk-=0.3;
	  aa-=0.3;
	  break;}}
		  if(l==156){
     kkkk+=0.1;
	  kk+=0.1;
	  aa+=0.1;
		  }
	 }
	 if(((202>x)&&(x>-211)&&(-254>z)&&(z>-261))&&kkkk>4&&keys['I']&&kkkk<=204)
	  {     float b;int l;
		  for(l=153;l<156;l++)
	      { b=s[l].fffb(x,z,kk);
		  if(!b){
	  kkkk+=0.3;
	  kk+=0.3;
	  aa+=0.3;
	  break;}}
		  if(l==156){
     kkkk-=0.1;
	  kk-=0.1;
	  aa-=0.1;
		  }}
	 if(kkkk<-2&&kk>-3)
		 {kk=-2;kkkk=-2;aa=-4;}
		 
}
void l5tomotherboard(){
	SkyBoxmm(200,30,200);
	if(z>200)
	{SkyBoxmmm(200,30,200);
	drawcubee();}
	glColor3f(0.312,0.312,0.312);
	s[3].ffff(199,-150,201,-50,-2);
	s[4].ffff(199,-250,201,-160,-2);
	s[5].ffff(178,-160,182,-150,-2);
	s[6].ffff(178,-152,200,-148,-2);
    s[7].ffff(178,-162,200,-158,-2);

	if((x<200)&&(x>190)&&(z<-150)&&(-160<z))
		kk=-4000;

	glBegin(GL_QUADS);
	glVertex3f(200,2,-50);
	glVertex3f(200,-4,-50);
	glVertex3f(200,-4,-150);
	glVertex3f(200,2,-150);

	glVertex3f(200,2,-160);
	glVertex3f(200,-4,-160);
	glVertex3f(200,-4,-250);
	glVertex3f(200,2,-250);

	glVertex3f(200,2,-160);
	glVertex3f(200,1,-160);
	glVertex3f(200,1,-150);
	glVertex3f(200,2,-150);

	glVertex3f(200,-4,-160);
	glVertex3f(200,-3,-160);
	glVertex3f(200,-3,-150);
	glVertex3f(200,-4,-150);
    glEnd();
	if(kk<2){
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	glVertex3f(180,-3,-160);
	glVertex3f(180,2,-160);
	glVertex3f(180,2,-150);
	glVertex3f(180,-3,-150);

	glVertex3f(180,-3,-160);
	glVertex3f(180,2,-160);
	glVertex3f(200,2,-160);
	glVertex3f(200,-3,-160);

	glVertex3f(180,-3,-150);
	glVertex3f(180,2,-150);
	glVertex3f(200,2,-150);
	glVertex3f(200,-3,-150);
	
	glVertex3f(180,2,-150);
	glVertex3f(180,2,-160);
	glVertex3f(200,2,-160);
	glVertex3f(200,2,-150);

	glVertex3f(180,-3,-150);
	glVertex3f(180,-3,-160);
	glVertex3f(200,-3,-160);
	glVertex3f(200,-3,-150);
	glEnd();
	}
	if(kk<=-4000+4&&kk>=-4000){
	SkyBoxm(200,30,200);

	s[8].ffff(199,-150,201,240,-4000);
	s[9].ffff(-201,-160,-199,-10,-4000);
	s[12].ffff(199,-160,201,-158,-4000);
	s[10].ffff(-199,-161,201,-159,-4000);
	s[11].ffff(-199,239,201,241,-4000);
	s[13].ffff(-201,90,-199,240,-4000);


	glPushMatrix();
	glTranslated(5,-4002,20);
	glScaled(4,0.5,4);
	glTranslated(0,-1,0);
    DrawCpu();
    glPopMatrix();
	s[14].ffff(4.9,0,45.1,40,-4000);
	if(x>-180)
	{d();ff1();ff2();ff3();ff4();ff5();}
	}
	glColor3f(1,1,1);
}
int hjk[40],jh=1;
void killant(){
	for(int oo=6;oo<66;oo++)
	for(int o=0;o<40;o++)
	if(isClicked&&!s[an[o].sss].fffb(x-sin(y*PIdiv180)*oo,z-cos(y*PIdiv180)*oo,kk)&&jh==1)
	{ hjk[o]+=1;jh=0;}
	if(!isClicked)
		jh=1;
	for(int o=0;o<40;o++)
		an[o].kill(hjk[o]);
}
void l6(){

	s[15].ffff(-201,-150,-199,-140,-2);
	s[16].ffff(-201,-130,-199,-50,-2);
	s[17].ffff(-201,-250,-199,-160,-2);
	s[18].ffff(-182,-160,-178,-150,-2);
	s[19].ffff(-200,-152,-178,-148,-2);
    s[20].ffff(-200,-162,-178,-158,-2);

	
	glColor3f(0.312,0.312,0.312);
   glBegin(GL_QUADS);
    glVertex3f(-200,2,-50);
	glVertex3f(-200,-4,-50);
	glVertex3f(-200,-4,-130);
	glVertex3f(-200,2,-130);

	glVertex3f(-200,2,-140);
	glVertex3f(-200,-4,-140);
	glVertex3f(-200,-4,-150);
	glVertex3f(-200,2,-150);

	glVertex3f(-200,2,-160);
	glVertex3f(-200,-4,-160);
	glVertex3f(-200,-4,-250);
	glVertex3f(-200,2,-250);

	glVertex3f(-200,2,-160);
	glVertex3f(-200,1,-160);
	glVertex3f(-200,1,-150);
	glVertex3f(-200,2,-150);

	glVertex3f(-200,2,-140);
	glVertex3f(-200,1,-140);
	glVertex3f(-200,1,-130);
	glVertex3f(-200,2,-130);

	glVertex3f(-200,-4,-160);
	glVertex3f(-200,-3,-160);
	glVertex3f(-200,-3,-150);
	glVertex3f(-200,-4,-150);


    glEnd();
	if(kk<2){
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	glVertex3f(-180,-3,-160);
	glVertex3f(-180,2,-160);
	glVertex3f(-180,2,-150);
	glVertex3f(-180,-3,-150);

	glVertex3f(-180,-3,-160);
	glVertex3f(-180,2,-160);
	glVertex3f(-200,2,-160);
	glVertex3f(-200,-3,-160);

	glVertex3f(-180,-3,-150);
	glVertex3f(-180,2,-150);
	glVertex3f(-200,2,-150);
	glVertex3f(-200,-3,-150);
	
	glVertex3f(-180,1.99,-150);
	glVertex3f(-180,1.99,-160);
	glVertex3f(-200,1.99,-160);
	glVertex3f(-200,1.99,-150);

	glVertex3f(-180,-3,-150);
	glVertex3f(-180,-3,-160);
	glVertex3f(-200,-3,-160);
	glVertex3f(-200,-3,-150);
	glEnd();}
}
void SkyBoxp(float xxx,float yyy,float zzz){
	
	glColor3d(1,1,1);
	glBindTexture(GL_TEXTURE_2D, i5);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, -1);

}

void l7insideKey(){
	glPushMatrix();
	s[26].ffff(-60.1,-78.1,60.1,-61.9,-2);
	s[94].ffff(-80.1,-235.1,80.1,-194.9,-2);

	glTranslated(0,0,-70);
    SkyBoxp(60,0,8);
	glTranslated(0,0,-145);
	glColor3f(0.5,0.5,0.5);
    SkyBoxmo(80,-3,20);
	glTranslated(0,0,10);
	SkyBoxmoo(80,-3,20);
	glTranslated(0,0,-20);
	SkyBoxmoo(80,-3,20);
	glColor3f(1,1,0);
	glTranslated(-60,0,10);
	glScaled(0.25,1,1);
	SkyBoxmoo(80,-3,30);
	glScaled(4,1,1);
	glTranslated(120,0,0);
	glScaled(0.25,1,1);
	SkyBoxmoo(80,-3,30);
    glScaled(4,1,1);
	glTranslated(120,0,50);
	glPushMatrix();
	float oo=0;
	for(int o=96;o<111;o++){
	glScaled(4,1,4);
	s[o].ffff(177.5-oo,-169,182.5-oo,-161,-2);
	A();
	glScaled(0.25,1,0.25);
	glTranslated(-25,0,0);
	oo+=25;
	}
	glPopMatrix();
	glPushMatrix();
	glTranslated(18,0,-20);
	glPushMatrix();
	oo=0;
	for(int o=111;o<127;o++){
	glScaled(4,1,4);
	s[o].ffff(195.5-oo,-189,200.5-oo,-181,-2);
	A();
	glScaled(0.25,1,0.25);
	glTranslated(-25,0,0);
	oo+=25;
	}
	glPopMatrix();
	glPopMatrix();
	glTranslated(0,0,-40);
	glPushMatrix();
	oo=0;
	for(int o=127;o<136;o++){
	glScaled(4,1,4);
	s[o].ffff(177.5-oo,-209,182.5-oo,-201,-2);
	A();
	glScaled(0.25,1,0.25);
	if(o==130){glTranslated(-200,0,0);oo+=200;}else
	{glTranslated(-25,0,0);
	oo+=25;}
	}
	glPopMatrix();
    glTranslated(0,0,-20);
	oo=0;
	for(int o=136;o<145;o++){
	glScaled(4,1,4);
	s[o].ffff(177.5-oo,-229,182.5-oo,-221,-2);
	A();
	glScaled(0.25,1,0.25);
	if(o==139){glTranslated(-200,0,0);oo+=200;}else
	{glTranslated(-25,0,0);
	oo+=25;}
	}
	glPopMatrix();

	glColor3f(1,1,1);
    glPopMatrix();

}
void l8(){
	m1();
    m22();
	m33();
}
void SkyBoxmou(float xxx,float yyy,float zzz){
	glPushMatrix();
	glTranslated(0,-8000,0);
	glColor3d(1,1,0);
	glBindTexture(GL_TEXTURE_2D, i1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);
	glColor3d(0.05,0.05,0.05);
	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx+77.5,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx+77.5,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx-77.5,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx-77.5,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glEnd();

		glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx-82,6,-zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx-77.5,6,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx-77.5,yyy,-zzz);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx-82,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(+xxx,-4,-zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,-4,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glBindTexture(GL_TEXTURE_2D, i2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+xxx,yyy,+zzz);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+xxx,yyy,-zzz);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-xxx,yyy,-zzz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,-1);

	glPopMatrix();
}
void DrawDonate()
{   float u,uu;
glColor3f(1,1,0);
glBegin(GL_QUADS);
	for(float o=0;o<3.14*2;o+=0.4)
	{ u=cos(o);uu=sin(o);
	glVertex3f(-2,u*4,uu*4);
    glVertex3f(0,u*4,uu*4); 
	 u=cos(o+0.4);uu=sin(o+0.4);
	glVertex3f(0,u*4,uu*4);
    glVertex3f(-2,u*4,uu*4); 
	}
  glEnd();
  glBegin(GL_TRIANGLES);
	for(float o=0;o<3.14*2;o+=0.4)
	{ u=cos(o);uu=sin(o);
	glVertex3f(-2,0,0);
    glVertex3f(-2,u*4,uu*4); 
	 u=cos(o+0.4);uu=sin(o+0.4);
	glVertex3f(-2,u*4,uu*4);
	}
  glEnd();
    glBegin(GL_TRIANGLES);
	for(float o=0;o<3.14*2;o+=0.4)
	{ u=cos(o);uu=sin(o);
	glVertex3f(0,0,0);
    glVertex3f(0,u*4,uu*4); 
	 u=cos(o+0.4);uu=sin(o+0.4);
	glVertex3f(0,u*4,uu*4);
	}
  glEnd();
}
void DrawDonatee(){
	
     glPushMatrix();
    glRotatef(90,0,0,1);
    glTranslated(-3,6.5,0);
    glScalef(0.8,0.8,0.8);
    glBegin(GL_QUADS);
    

    glColor3f(0.7,0,1);
  glVertex3f(-3,0,2);
  glVertex3f(0,0,2);
  glVertex3f(3,0,-2);
  glVertex3f(0,0,-2);

    
   glVertex3f(-3,3,2);
  glVertex3f(0,3,2);
  glVertex3f(3,3,-2);
  glVertex3f(0,3,-2);

  glVertex3f(-3,0,2);
  glVertex3f(0,0,-2);
  glVertex3f(0,3,-2);
  glVertex3f(-3,3,2);

  glVertex3f(0,0,2);
  glVertex3f(3,0,-2);
  glVertex3f(3,3,-2);
  glVertex3f(0,3,2);

  glVertex3f(-3,0,2);
  glVertex3f(0,0,2);
  glVertex3f(0,3,2);
  glVertex3f(-3,3,2);

  glVertex3f(0,0,-2);
  glVertex3f(3,0,-2);
  glVertex3f(3,3,-2);
  glVertex3f(0,3,-2);
  glEnd();
  
  glBegin(GL_QUADS);
    glColor3f(1,1,1);
  glVertex3f(-3,0,2);
  glVertex3f(-5,0,2);
  glVertex3f(-3,0,-2);
  glVertex3f(0,0,-2);

    
   glVertex3f(-3,3,2);
  glVertex3f(-5,3,2);
  glVertex3f(-3,3,-2);
  glVertex3f(0,3,-2);

  glVertex3f(-3,0,2);
  glVertex3f(-5,0,2);
  glVertex3f(-5,3,2);
  glVertex3f(-3,3,2);

  glVertex3f(-3,0,-2);
  glVertex3f(0,0,-2);
  glVertex3f(0,3,-2);
  glVertex3f(-3,3,-2);

  glVertex3f(-3,0,2);
  glVertex3f(-3,0,-2);
  glVertex3f(-3,3,-2);
  glVertex3f(-3,3,2);

  glVertex3f(-5,0,2);
  glVertex3f(-3,0,-2);
  glVertex3f(-3,3,-2);
  glVertex3f(-5,3,2);
  glEnd();
  
  glColor3f(0,1,0);
  glTranslated(2,0.5,0);
   for(float i=0;i<(2*3.14);i+=0.4)
  {
    glBegin(GL_QUADS);
  float x=cos(i)*0.5;
  float y=sin(i)*-0.5;
  glVertex3f(x,0,y);
  glVertex3f(x,2,y);
  
  float z=cos(i+0.4);
  float h=sin(i+0.4);
  glVertex3f(h*0.5,2,z*(0.5));
  glVertex3f(h*0.5,0,z*(0.5));
  glEnd();
  }
  
   glTranslated(-2,-0.5,0);
   //ÇáÒÑ ÇáÊÇäí
   glPopMatrix();
   glPushMatrix();
    glRotatef(90,0,0,1);
    glTranslated(-3,-5.5,0);
    glScalef(0.8,0.8,0.8);
    glBegin(GL_QUADS);
    

    glColor3f(0.7,0,1);
  glVertex3f(-3,0,2);
  glVertex3f(0,0,2);
  glVertex3f(3,0,-2);
  glVertex3f(0,0,-2);

    
   glVertex3f(-3,3,2);
  glVertex3f(0,3,2);
  glVertex3f(3,3,-2);
  glVertex3f(0,3,-2);

  glVertex3f(-3,0,2);
  glVertex3f(0,0,-2);
  glVertex3f(0,3,-2);
  glVertex3f(-3,3,2);

  glVertex3f(0,0,2);
  glVertex3f(3,0,-2);
  glVertex3f(3,3,-2);
  glVertex3f(0,3,2);

  glVertex3f(-3,0,2);
  glVertex3f(0,0,2);
  glVertex3f(0,3,2);
  glVertex3f(-3,3,2);

  glVertex3f(0,0,-2);
  glVertex3f(3,0,-2);
  glVertex3f(3,3,-2);
  glVertex3f(0,3,-2);
  glEnd();

  glBegin(GL_QUADS);
    glColor3f(1,1,1);
  glVertex3f(-3,0,2);
  glVertex3f(-5,0,2);
  glVertex3f(-3,0,-2);
  glVertex3f(0,0,-2);

    
   glVertex3f(-3,3,2);
  glVertex3f(-5,3,2);
  glVertex3f(-3,3,-2);
  glVertex3f(0,3,-2);

  glVertex3f(-3,0,2);
  glVertex3f(-5,0,2);
  glVertex3f(-5,3,2);
  glVertex3f(-3,3,2);

  glVertex3f(-3,0,-2);
  glVertex3f(0,0,-2);
  glVertex3f(0,3,-2);
  glVertex3f(-3,3,-2);

  glVertex3f(-3,0,2);
  glVertex3f(-3,0,-2);
  glVertex3f(-3,3,-2);
  glVertex3f(-3,3,2);

  glVertex3f(-5,0,2);
  glVertex3f(-3,0,-2);
  glVertex3f(-3,3,-2);
  glVertex3f(-5,3,2);
  glEnd();

  glColor3f(0,1,0);
  
  glTranslated(2,0.5,0);
   for(float i=0;i<(2*3.14);i+=0.4)
  {
    glBegin(GL_QUADS);
  float x=cos(i)*0.5;
  float y=sin(i)*-0.5;
  glVertex3f(x,0,y);
  glVertex3f(x,2,y);
  
  float z=cos(i+0.4);
  float h=sin(i+0.4);
  glVertex3f(h*0.5,2,z*(0.5));
  glVertex3f(h*0.5,0,z*(0.5));
  glEnd();
  }
   glTranslated(-2,-0.5,0);
   glPopMatrix();
  glTranslated(-5,0,0);
  glColor3f(1,1,0);
  
  for(float i=0;i<(2*3.14);i+=0.4)
  {
    glBegin(GL_QUADS);
  float x=cos(i)*0.2;
  float y=sin(i)*-0.2;
  glVertex3f(-3,x,y);
  glVertex3f(11,x,y);
  
  float z=cos(i+0.4);
  float h=sin(i+0.4);
  glVertex3f(11,h*0.2,z*(0.2));
  glVertex3f(-3,h*0.2,z*(0.2));
  glEnd();
  }
  glTranslated(5,0,0);

  glTranslated(-3,0,0);
  glColor3f(0,1,1);
  
  for(float i=0;i<(2*3.14);i+=0.4)
  {
    glBegin(GL_QUADS);
  float x=cos(i)*0.4;
  float y=sin(i)*-0.4;
  glVertex3f(0,x,y);
  glVertex3f(4,x,y);
  
  float z=cos(i+0.4);
  float h=sin(i+0.4);
  glVertex3f(4,h*0.3,z*(0.4));
  glVertex3f(0,h*0.3,z*(0.4));
  glEnd();
  }
  glTranslated(3,0,0);

  DrawDonate();
  glColor3f(1,1,1);

}
void l9mouse(){
	s[156].ffff(-243.1,-87.1,-242.9,-71.9,-2);
	s[157].ffff(-250.1,-87.1,-249.9,-71.9,-2);
    s[158].ffff(-326.5,-80.1,-249.1,-79.9,-8000);
    s[159].ffff(-243.9,-80.1,-166.5,-79.9,-8000);
	s[160].ffff(-326.5,79.9,-166.5,80.1,-8000);
    s[161].ffff(-326.6,-80.1,-326.4,80.1,-8000);
    s[162].ffff(-166.6,-80.1,-166.4,80.1,-8000);


	if(x<-244&&x>-249&&z<-72&&z>-80&&kk==-2)
       kk=-8000;
	if(x<-244&&x>-249&&z<-80&&z>-88&&kk==-8000)
       kk=-2;
	glPushMatrix();
	glTranslated(-246.5,0,0);
	SkyBoxmou(80,30,80);
	glPopMatrix();
	glPushMatrix();
	s[176].ffff(-18-246.5,-20,18-246.5,20,-8000);
		s[177].ffff(-35-246.5,-20,-27-246.5,20,-8000);
			s[178].ffff(27-246.5,-20,30-246.5,20,-8000);

	glTranslated(-246.5,-7990,0);
	glScaled(5,5,5);
	 DrawDonatee();
	 glPopMatrix();

	glColor3f(1,1,1);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-243,-3.99,-72);
	glVertex3f(-250,-3.99,-72);
	glVertex3f(-250,-3.99,-87);
	glVertex3f(-243,-3.99,-87);
		glColor3f(0,0,0);

	glVertex3f(-243,0,-72);
	glVertex3f(-250,0,-72);
	glVertex3f(-250,0,-87);
	glVertex3f(-243,0,-87);

	glVertex3f(-243,-3.99,-72);
	glVertex3f(-243,0,-72);
	glVertex3f(-243,0,-87);
	glVertex3f(-243,-3.99,-87);

	glVertex3f(-250,-3.99,-72);
	glVertex3f(-250,0,-72);
	glVertex3f(-250,0,-87);
	glVertex3f(-250,-3.99,-87);

	glVertex3f(-243,-3.99,-75);
	glVertex3f(-243,0,-75);
	glVertex3f(-250,0,-75);
	glVertex3f(-250,-3.99,-75);
	glEnd();
	glColor3f(1,1,1);
	glPopMatrix();
}
float speedkey=0.2;
void laptop(){

	glPushMatrix();
		if(x<200&&x>-200&&z>-250&&z<-50&&kk>-5)
	  { speedkey=0.1;
		l1();
		l2();  		
		} else if(kk==-4000)
			speedkey=0.2; else if(kk==-8000)speedkey=0.1;else speedkey=0.2;
	l3();//skybox laptop
	l4(); 
	l5tomotherboard();
	l6();

	if(x<200&&x>-200&&z>-250&&-50>z&&kk>-5)
	l7insideKey();
	if(z<-255&&z>-260&&kk>-5)
	l8();
	
	l9mouse();


	glPopMatrix();
	glColor3f(1,1,1);
}

GLfloat tran=0,t=0;
GLfloat light=0,light1=0;
int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLfloat LightPos2[] = { 0.0f,400.0f,0.0f,1.0f};
	GLfloat LightAmb[] = { 0.5f,0.5f,0.5f,1.0f };

	GLfloat LightPos3[] = { 0.0f,20.0f,-120.0f,1.0f};
	GLfloat LightAmb2[] = { 0.2f,0.2f,0.2f,1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, LightPos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);

    glLightfv(GL_LIGHT2, GL_POSITION, LightPos3);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmb2);

	    glLightfv(GL_LIGHT3, GL_POSITION, LightPos3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmb2);
	if(keys['O'])
		light=1;
	if(keys['N'])
		light=0;
	if(light==1&&kk>-4)
	glEnable(GL_LIGHT1);
	if(light==0||kk<-4||(x<200&&x>-200&&z>-250&&z<-50&&kk>-5))
	glDisable(GL_LIGHT1);
	if((x<200&&x>-200&&z>-250&&z<-50&&kk>-5)||kk<-7000)
		glEnable(GL_LIGHT2);else glDisable(GL_LIGHT2);

	if(keys['R'])
		light1=1;
	if(keys['F'])
		light1=0;
	if((light1==1)&&(-5000>kk)&&(kk<-400))
	glEnable(GL_LIGHT3);
	if(light1==0||kk>-400)
	glDisable(GL_LIGHT3);

	//	sound2.Stop();
/*************************
	    if(keys['0'])
					sound1.Stop();

		if(keys['9'])
			sound1.Play();
*********************************/

	glColor3f(1,1,1);
	gluLookAt(0, kk, 0, 0, kk, -25, 0, 1, 0);

	glTranslated(0,0,-5+C);
	if(keys['8'])
		kk=-2;
	if(keys['2'])
		kk=-4000;
	if(keys['3'])
		kk=-3000;
    MyCamera.Render();

	    if(t==0)
		tran+=0.1;
	    if (tran>=400)
	    t=1;
	    if(t==1)
        tran-=0.1;
	    if (tran<=0)
	    t=0;



		an[0].tr(0,0,-55,2,21);
	    an[1].tr(100,0,-100,2,22);
	    an[2].tr(100,-4000,-100,2,48);///3333333333333333333333333333333
        an[3].tr(-40,0,-90,2,95);
		an[4].tr(140,-4000,20,2,50);
	    an[5].tr(100,0,0,2,51);
		an[6].tr(200-tran,0,-10,2,52);
		an[7].tr(200-tran,0,-20,2,53);
		an[8].tr(0,0,-240,2,54);
		an[9].tr(210,0,-80,2,55);
		an[10].tr(220,0,-80,2,56);
		an[11].tr(-205,0,-250,2,57);
		an[12].tr(20-(tran/2),-4000,-40,2,81);
		an[13].tr(30-(tran/2),-4000,-40,2,82);
		an[14].tr(40-(tran/2),-4000,-40,2,83);
	    an[15].tr(10-(tran/2),-4000,-40,2,49);
		an[16].tr(-100,-4000,-40+(tran/2),2,84);
		an[17].tr(-100,-4000,-30+(tran/2),2,85);
		an[18].tr(-100,-4000,-20+(tran/2),2,86);
	    an[19].tr(-100,-4000,-10+(tran/2),2,87);
	    an[20].tr(100-(tran/5),0,-85,2,145);
		an[21].tr(100-(tran/5),0,-95,2,146);
		an[22].tr(100-(tran/5),0,-105,2,147);
        an[23].tr(100-(tran/5),0,-115,2,148);
		an[24].tr(100-(tran/5),0,-125,2,149);
		an[25].tr(100-(tran/5),0,-135,2,150);
		an[26].tr(100-(tran/5),0,-145,2,151);
		an[27].tr(100-(tran/5),0,-155,2,152);

		an[28].tr(-245+(tran/5),-8000,-25,5,178);
		an[29].tr(-245+(tran/5),-8000,-30,5,179);
		an[30].tr(-245+(tran/5),-8000,-35,5,180);
		an[31].tr(-245+(tran/5),-8000,-40,5,181);
		an[32].tr(-245+(tran/5),-8000,-45,5,182);
		an[33].tr(-245+(tran/5),-8000,-50,5,183);
	    an[34].tr(-245+(tran/5),-8000,-55,5,184);
	    an[35].tr(-245+(tran/5),-8000,-60,5,185);

	 //   an[36].tr(-5,5,5,5,186,1);


	    killant();
	

    glPushMatrix();
    a.Materials[0].tex =m;
    Key(keys, speedkey);//0.05
    glTranslated(x,kk,z);
    glRotated(y,0,1,0);	
    w();
	glPopMatrix();
	if(!(x<200&&x>-200&&z>-250&&-50>z)&&kk>-3)
	{Room(1000,500,1000);
	Table(350,500);
	glColor3f(0.312,0.312,0.312);
	s[27].ffff(-265,-75,-228,-18,-2);
	mouse.Draw();}
	
	glColor3f(1,1,1);
	laptop();
	

	for(int o=0;o<6;o++)
		an[o].draw();
	for(int o=20;o<28;o++)
	if(t==1)
	an[o].drawRotatedY180();
	else 
	an[o].draw();

	for(int o=6;o<8;o++)
	if(t==1)
	an[o].drawRotatedY180();
	else 
	an[o].draw();

	an[8].draw();
	for(int o=9;o<12;o++)
	an[o].drawRotatedY90();
	for(int o=12;o<16;o++)
		if(t==1)
	an[o].drawRotatedY180();
		else an[o].draw();

for(int o=16;o<20;o++)
		if(t==1)
	an[o].drawRotatedY270();
	else an[o].drawRotatedY90();

	for(int o=28;o<36;o++)
	if(t==0)
	an[o].drawRotatedY180();
	else 
		an[o].draw();

			//an[36].draw();


	glFlush();											// Done Drawing The Quad
	
	return TRUE;
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
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
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
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_MOUSEMOVE:
	{
		mouseX = (int)LOWORD(lParam);
		mouseY = (int)HIWORD(lParam);
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
	if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
														// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
