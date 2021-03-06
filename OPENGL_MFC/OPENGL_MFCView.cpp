
// OPENGL_MFCView.cpp: COPENGLMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OPENGL_MFC.h"
#endif

#include "OPENGL_MFCDoc.h"
#include "OPENGL_MFCView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/core/core.hpp>    
#include "opencv2/imgproc.hpp"
#include "math.h"
//#include <windows.h>

using namespace cv;

#include <stdlib.h>
#include <tchar.h>
#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>			// Header File For Standard Input/Output
#include <time.h>
#include <string.h>

#include "GLTexture.h"
#include "3DMath.h"

HINSTANCE hIns;
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	makedLight = false;
bool	radiositybool = false;
//GLuint	texIndex[16];

RayLightMap	myLightmap[100];
RayLightMap	myLightmapTmp[100];

struct	srtFaceQUADS {
	vertex3		v1;
	vertex3		v2;
	vertex3		v3;
	vertex3		v4;
};
srtFaceQUADS	faceQs[100];
float lightPH = 29.0f;			// 光源高度
int quadnum = 6;
long RadW;
long RadH;
float formFactor[256][256];


unsigned char *RadiosityPointer = NULL;



// COPENGLMFCView
int deg = 1;
double youx = 0;
double youy = -20;
double youz = 0;
double lookx = 0;
double looky = -19;
double lookz = 0;
double lookix, lookiy, lookiz, upix, upiy, upiz;
double upx = 0;
double upy = 0;
double upz = 1;
bool thirdpersonview = false;
bool mousedown = false;
bool cvwindow = false;
int pointx = 0;
int pointy = 0;
Mat frame2;
int shiftctrlalt = 0;
int findarea[480][640] = { -1 };
int numbers[480][640] = { -1 };
Mat frame;
Mat imageROI;
bool fx = false;
char str[100];
int strl = 0;
float item[100][100] = { -1 };
int itemnum = 0;
double  prevideo[3] = { 0,0,0 };
double videoxx = 0, videoyy = 0, videozz = 0;
int nowmode = -1;
int selectt = -1;
int lightnum = 0x4001;              //light id标号
const GLfloat PI = 3.1415926535898;
GLfloat shadow_matrix[4][4];
GLfloat li[100][4];
int linum = 0;              //light 个数
const GLfloat ground[4] = { 0, 0, 1, 5.51 };
bool shadow = false;
float lyjx=0;
float lyjy=0;
float lyjz=0;
bool iii = true;
bool iiii = false;
double changeR = 2;
double changeG=2;
double changeB=2;
/*
QueryPerformanceCounter(&t2);
//_cprintf("Begin Time: %u\n", t1.QuadPart);
//_cprintf("End Time: %u\n", t2.QuadPart);
//_cprintf("Lasting Time: %u\n", (t2.QuadPart - t1.QuadPart));



LARGE_INTEGER t1, t2, tc;
QueryPerformanceFrequency(&tc);
//_cprintf("Frequency: %u\n", tc.QuadPart);
QueryPerformanceCounter(&t1);*/








void makeRoom()
{
	vertex3 wall[8];
	vertex3 obj[8];

	// --------------------------

	wall[0] = vertex3(-50, -30, 50);
	wall[1] = vertex3(50, -30, 50);
	wall[2] = vertex3(50, -30, -50);
	wall[3] = vertex3(-50, -30, -50);

	wall[4] = vertex3(-50, 30, 50);
	wall[5] = vertex3(50, 30, 50);
	wall[6] = vertex3(50, 30, -50);
	wall[7] = vertex3(-50, 30, -50);

	// --------------------------

	faceQs[0].v1 = wall[0];
	faceQs[0].v2 = wall[1];
	faceQs[0].v3 = wall[2];
	faceQs[0].v4 = wall[3];

	faceQs[1].v1 = wall[4];
	faceQs[1].v2 = wall[7];
	faceQs[1].v3 = wall[6];
	faceQs[1].v4 = wall[5];

	faceQs[2].v1 = wall[0];
	faceQs[2].v2 = wall[3];
	faceQs[2].v3 = wall[7];
	faceQs[2].v4 = wall[4];

	faceQs[3].v1 = wall[2];
	faceQs[3].v2 = wall[1];
	faceQs[3].v3 = wall[5];
	faceQs[3].v4 = wall[6];

	faceQs[4].v1 = wall[0];
	faceQs[4].v2 = wall[4];
	faceQs[4].v3 = wall[5];
	faceQs[4].v4 = wall[1];

	faceQs[5].v1 = wall[3];
	faceQs[5].v2 = wall[2];
	faceQs[5].v3 = wall[6];
	faceQs[5].v4 = wall[7];
int j=0;
	// --------------------------
for(int i=0;i<itemnum;i++)
{
	if(item[i][0]==1)
	{
		float x=item[i][2];
		float y=item[i][3];
		float z=item[i][1];
		float r=item[i][4]*4;
	obj[0] = vertex3((x-r)*2, (y-4-r)*2, (z+r)*2);
	obj[1] = vertex3((x+r)*2, (y-4-r)*2, (z+r)*2);
	obj[2] = vertex3((x+r)*2, (y-4-r)*2, (z-r)*2);
	obj[3] = vertex3((x-r)*2, (y-4-r)*2, (z-r)*2);

	obj[4] = vertex3((x-r)*2, (y-4+r)*2, (z+r)*2);
	obj[5] = vertex3((x+r)*2, (y-4+r)*2, (z+r)*2);
	obj[6] = vertex3((x+r)*2, (y-4+r)*2, (z-r)*2);
	obj[7] = vertex3((x-r)*2, (y-4+r)*2, (z-r)*2);
	faceQs[6+j].v1 = obj[4];
	faceQs[6+j].v2 = obj[5];
	faceQs[6+j].v3 = obj[6];
	faceQs[6+j].v4 = obj[7];

	faceQs[7+j].v1 = obj[0];
	faceQs[7+j].v2 = obj[4];
	faceQs[7+j].v3 = obj[7];
	faceQs[7+j].v4 = obj[3];

	faceQs[8+j].v1 = obj[2];
	faceQs[8+j].v2 = obj[6];
	faceQs[8+j].v3 = obj[5];
	faceQs[8+j].v4 = obj[1];

	faceQs[9+j].v1 = obj[0];
	faceQs[9+j].v2 = obj[1];
	faceQs[9+j].v3 = obj[5];
	faceQs[9+j].v4 = obj[4];

	faceQs[10+j].v1 = obj[3];
	faceQs[10+j].v2 = obj[7];
	faceQs[10+j].v3 = obj[6];
	faceQs[10+j].v4 = obj[2];

	faceQs[11+j].v1 = obj[0];
	faceQs[11+j].v2 = obj[1];
	faceQs[11+j].v3 = obj[2];
	faceQs[11+j].v4 = obj[3];
	j+=6;
	quadnum+=6;
	}
}
}

void RadiosityMode(int xw, int xh)
{
	RadW = xw;
	RadH = xh;

	srand((unsigned)time(NULL));

	glViewport(0, 0, RadW, RadH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)RadW / (float)RadH, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CreateRadiosityMem()
{
	if (RadiosityPointer == NULL) {
		RadiosityPointer = new unsigned char[RadW*RadH * 3];
	}
}

void calculateFormFactor()
{
	long i, j;
	for (i = 0; i<RadW; i++) {
		for (j = 0; j<RadH; j++) {
			formFactor[i][j] = (float)(0.5f + 0.5f*sin(i* M_PI / (RadW - 1))*sin(j* M_PI / (RadH - 1)));
		}
	}
}

void RenderQuad()
{
	long i;

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	for (i = 0; i<quadnum; i++) {
		glBindTexture(GL_TEXTURE_2D, myLightmapTmp[i].TexIndex);
		//	glBindTexture(GL_TEXTURE_2D, texture[0]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(faceQs[i].v1.x, faceQs[i].v1.y, faceQs[i].v1.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(faceQs[i].v2.x, faceQs[i].v2.y, faceQs[i].v2.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(faceQs[i].v3.x, faceQs[i].v3.y, faceQs[i].v3.z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(faceQs[i].v4.x, faceQs[i].v4.y, faceQs[i].v4.z);
		glEnd();
	}


	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1, 1);

	for (i = 0; i<quadnum; i++) {
		glBindTexture(GL_TEXTURE_2D, myLightmap[i].TexIndex);
		//	glBindTexture(GL_TEXTURE_2D, texture[0]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(faceQs[i].v1.x, faceQs[i].v1.y, faceQs[i].v1.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(faceQs[i].v2.x, faceQs[i].v2.y, faceQs[i].v2.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(faceQs[i].v3.x, faceQs[i].v3.y, faceQs[i].v3.z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(faceQs[i].v4.x, faceQs[i].v4.y, faceQs[i].v4.z);
		glEnd();
	}

	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);


	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, lightPH, 0);
	for (int i = 0; i < 361; i++)
	{
		glColor3f((255.0 - abs(i / 2 - 90)) / 256, (255.0 - abs(i / 2 - 90)) / 256, (255.0 - abs(i / 2 - 90)) / 256);
		glVertex3f(5.0f*sin(i*PI / 180), lightPH, 5.0f*cos(i*PI / 180));
	}
	glEnd();

	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
}

strColorRGB RadiosityColor()
{
	strColorRGB tmpRGB;
	long i, j;
	strColorRGB *pt;

	float	R = 0,
		G = 0,
		B = 0;

	for (i = 0; i<RadW; i++) {
		for (j = 0; j<RadH; j++) {
			pt = (strColorRGB *)(RadiosityPointer + 3 * (i*RadW + j));

			R = R + pt->R * formFactor[i][j];
			G = G + pt->G * formFactor[i][j];
			B = B + pt->B * formFactor[i][j];
		}
	}

	R = R / ((float)RadW*(float)RadH*255.0f);
	G = G / ((float)RadW*(float)RadH*255.0f);
	B = B / ((float)RadW*(float)RadH*255.0f);

	tmpRGB.R = (unsigned char)(R *255.0f);
	tmpRGB.G = (unsigned char)(G *255.0f);
	tmpRGB.B = (unsigned char)(B *255.0f);

	return tmpRGB;
}







strColorRGB xrender(vertex3 v_eye,
	vertex3 v_dir,
	vertex3 v_up)
{
	glClearColor(0.0, 0.0, 0.0, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(v_eye.x + v_dir.x / 1000.0f, v_eye.y + v_dir.y / 1000.0f, v_eye.z + v_dir.z / 1000.0f,
		v_eye.x + v_dir.x, v_eye.y + v_dir.y, v_eye.z + v_dir.z,
		v_up.x, v_up.y, v_up.z);

	RenderQuad();

	glReadPixels(0, 0, RadW, RadH,
		GL_RGB, GL_UNSIGNED_BYTE,
		RadiosityPointer);

	return RadiosityColor();
}







void RadiosityStep()
{
	long i, u, v;

	//	vertex3	BasevectorTmp;
	vertex3	Basevector;

	vertex3 UVector;
	vertex3 VVector;

	float ulen;
	float vlen;

	float udx;
	float vdx;

	vertex3 randvec;
	vertex3 perpvec;

	vertex3 FaceNormal;

	vertex3 v_eye,
		v_dir,
		v_up;

	strColorRGB	TempRGB;



	for (i = 0; i<quadnum; i++) {
		Basevector = faceQs[i].v1;

		UVector = faceQs[i].v2 - faceQs[i].v1;
		VVector = faceQs[i].v4 - faceQs[i].v1;


		ulen = UVector.length();
		vlen = VVector.length();

		UVector.UnitNormal();
		VVector.UnitNormal();

		udx = ulen / (float)myLightmap[i].mapWidth;
		vdx = vlen / (float)myLightmap[i].mapHeight;

		Basevector += UVector * (udx / 2.0f) + VVector * (vdx / 2.0f);

		for (u = 0; u<myLightmap[i].mapWidth; u++) {
			for (v = 0; v<myLightmap[i].mapHeight; v++) {


				randvec.x = (float)(127 - rand() % 255);
				randvec.y = (float)(127 - rand() % 255);
				randvec.z = (float)(127 - rand() % 255);
				randvec.UnitNormal();


				FaceNormal = GetNormal(faceQs[i].v1, faceQs[i].v2, faceQs[i].v3);
				perpvec = crossProduct(FaceNormal, randvec);


				v_eye = Basevector +
					(UVector*(udx*u) + VVector * (vdx*v));

				v_dir = FaceNormal;

				v_up = perpvec;

				TempRGB = xrender(v_eye, v_dir, v_up);

				myLightmap[i].SetPixel(u, v,
					TempRGB.R*(changeR+1),
					TempRGB.G*(changeG+1),
					TempRGB.B*(changeB+1));
			}
		}
	}

	for (i = 0; i<100; i++) {
		myLightmap[i].UpdateTextrue();
	}
}










LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
														/*
														AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
														{
														FILE *File=NULL;									// File Handle

														if (!Filename)										// Make Sure A Filename Was Given
														{
														return NULL;									// If Not Return NULL
														}

														File=fopen(Filename,"r");							// Check To See If The File Exists

														if (File)											// Does The File Exist?
														{
														fclose(File);									// Close The Handle
														return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
														}

														return NULL;										// If Load Failed Return NULL
														}

														int LoadGLTextures()									// Load Bitmaps And Convert To Textures
														{
														int Status=FALSE;									// Status Indicator

														AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

														memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

														// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
														if (TextureImage[0]=LoadBMP("Data/NeHe.bmp"))
														{
														Status=TRUE;									// Set The Status To TRUE

														glGenTextures(1, &texture[0]);					// Create The Texture

														// Typical Texture Generation Using Data From The Bitmap
														glBindTexture(GL_TEXTURE_2D, texture[0]);
														glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
														glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
														glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
														}

														if (TextureImage[0])									// If Texture Exists
														{
														if (TextureImage[0]->data)							// If Texture Image Exists
														{
														free(TextureImage[0]->data);					// Free The Texture Image Memory
														}

														free(TextureImage[0]);								// Free The Image Structure
														}

														return Status;										// Return The Status
														}
														*/
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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	long i;
	for (i = 0; i<100; i++) {

		myLightmap[i].makeBMP(8, 8,					// 图片的宽和高
													//60+ i*12,i*13,50+i*10);	// 图片颜色
			0, 0 ,0 );

		//	LoadBMP("white.bmp", &texIndex[i]);
	}
	for (i = 0; i<100; i++) {
		if (i == 3) {
			myLightmapTmp[i].makeBMP(8, 8,					// 图片的宽和高
				0, 255, 255);
		}
		else if (i == 2) {

			myLightmapTmp[i].makeBMP(8, 8,					// 图片的宽和高
				0, 0, 255);
		}
		else if (i == 4) {

			myLightmapTmp[i].makeBMP(8, 8,					// 图片的宽和高
				255, 0, 0);
		}
		else if (i == 5) {

			myLightmapTmp[i].makeBMP(8, 8,					// 图片的宽和高
				0, 255, 0);
		}
		else if (i == 1) {

			myLightmapTmp[i].makeBMP(8, 8,					// 图片的宽和高
				232 , 139 , 0);
		}
		else {
			myLightmapTmp[i].makeBMP(64, 64,					// 图片的宽和高
				255,255, 255);
		}
	}




	makeRoom();

	/*
	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
	return FALSE;									// If Texture Didn't Load Return FALSE
	}
	*/

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}



void RadiosityEnd(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	static int redraw = 0;
	int redraww = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
														/*
														glTranslatef(0.0f,0.0f,-5.0f);

														glRotatef(xrot,1.0f,0.0f,0.0f);
														glRotatef(yrot,0.0f,1.0f,0.0f);
														glRotatef(zrot,0.0f,0.0f,1.0f);
														*/
	gluLookAt(0, 0, -80,
		0, 0, 0,
		0, 1, 0);
	static float xrott=0;
	static float yrott=0;
	static float zrott=0;
	static float xrot=0;
	static float yrot=0;
	static float zrot=0;
	static double xt=GetTickCount();
	static double yt=GetTickCount();
	static double zt=GetTickCount();
    static int sc=1;
    //_cprintf("%f ",xrot);
	if ((GetKeyState('A') & 0x80)&& yrot<100 )
    {
	   yrot++;
       yt=GetTickCount()-((yrot-1)/yrot)*(GetTickCount()-yt);
    }
	if ((GetKeyState('D') & 0x80) &&yrot>-100  )
    {
		  yrot--;
       yt=GetTickCount()-((yrot+1)/yrot)*(GetTickCount()-yt);
    }
    if ((GetKeyState(' ') & 0x80) )
    {
        sc=100;
    }
    else
    {
        sc=1;
    }

        xrott+=(GetTickCount()-xt)*xrot/500;
		xrot > 0.05*sc ? xrot -= 0.02*sc :xrot<-0.05*sc?  xrot += 0.02*sc:xrot=0;
        yrott+=(GetTickCount()-yt)*yrot/500;
		yrot > 0.05*sc ? yrot -= 0.02*sc :yrot<-0.05*sc?  yrot += 0.02*sc: yrot = 0;
		//_cprintf("%d  %f  %f  %f  %f  %f aa \n", GetTickCount(), zt, zrot, xrott, yrott, zrott);
        zrott+=(GetTickCount()-zt)*zrot/500.0;
		zrot > 0.05*sc ? zrot -= 0.02*sc : zrot<-0.05*sc? zrot += 0.02*sc:zrot = 0;
        //_cprintf("%d  %f  %f  %f  %f  %f  \n",xrot,yrot,zrot,xrott,yrott,zrott);
		glRotatef(xrott/1000,1 , 0, 0);
		glRotatef(yrott/1000, 0,1, 0);
		glRotatef(zrott/1000, 0, 0, 1);

	glColor3f(1, 1, 1);
	
	long i;
	if ((GetKeyState('C') & 0x80))
	{
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraw = 0;
	}
	if ((GetKeyState('P') & 0x80))
	{
		changeR *= 1.05;
		changeG /= 1.1;
		changeB *= 1.05;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The View
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
	}
	if ((GetKeyState('O') & 0x80))
	{
		changeG *= 1.05;
		changeR *= 1.05;
		changeB /= 1.1;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The View
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
	}
	if ((GetKeyState('I') & 0x80))
	{
		changeG *= 1.05;
		changeR /= 1.1;
		changeB *= 1.05;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The View
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
	}
	if ((GetKeyState('E') & 0x80))
	{
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = (redraw<3) ? 0 : redraw - 3;
		redraw = redraww;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
	}

	if ((GetKeyState('K') & 0x80))
	{
		changeR *= 1.1;
		changeG /= 1.05;
		changeB /= 1.05;
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
	}
	if ((GetKeyState('J') & 0x80))
	{
		changeR /= 1.05;
		changeG *= 1.1;
		changeB /= 1.05;
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
	}
	if ((GetKeyState('M') & 0x80))
	{
		changeR /= 1.45;
		changeG /= 1.45;
		changeB *= 1.9;
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
	}
	if ((GetKeyState('N') & 0x80))
	{
		changeR = 2;
		changeG = 2;
		changeB = 2;
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
	}
	if ((GetKeyState('R') & 0x80))
	{
		for (int i = 0; i < 100; i++)
			myLightmap[i].makeBMP(8, 8, 0, 0, 0);
		redraww = redraw;
		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();
		for (int ii = 0; ii<redraww; ii++)
			RadiosityStep();
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
		_cprintf("%f %f %f\n", changeR, changeG, changeB);
	}

	if ((GetKeyState('P') & 0x80))
	{
		myLightmap[2].getcolor(2, 2, 0);/*
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 8; i++)
				for (int k = 0; k < 8; i++)
			_cprintf("%d %d %d %d\n", myLightmap[i].getcolor(j, k, 0), myLightmap[i].getcolor(j, k, 1), myLightmap[i].getcolor(j, k, 2),myLightmap[i].mapWidth);*/
	}
	if (!(GetKeyState('L') & 0x80))
		makedLight = false;
	if ((GetKeyState('L') & 0x80) && makedLight == false) {
		makedLight = true;

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算中请稍后...]"));


		// --------------------------------------------------

		RadiosityMode(32, 32);

		CreateRadiosityMem();

		calculateFormFactor();

			RadiosityStep();
			redraw++;
		RadiosityEnd(640, 480);

		// -------------------------------------------------

		SetWindowText(hWnd, _T("Radiosity 光能传递  [计算完成]"));
	}



	RenderQuad();

	return TRUE;										// Keep Going
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
			MessageBoxA(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBoxA(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBoxA(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBoxA(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(_T("OpenGL"), hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, _T("Could Not Unregister Class."), _T("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
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
	wc.lpszClassName = _T("OpenGL");								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBoxA(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
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
			if (MessageBoxA(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBoxA(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
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
		_T("OpenGL"),							// Class Name
		_T("opengl"),								// Window Title
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
		MessageBox(NULL, _T("Window Creation Error."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
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
		32,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
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

int showr()			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
	if (MessageBoxA(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow('\0', 640, 480, 32, fullscreen))
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
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done = TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
														// Recreate Our OpenGL Window
				if (!CreateGLWindow('\0', 640, 480, 32, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}
	//_cprintf("hahadsfadsfasdfasdfaa");
	// Shutdown
	KillGLWindow();									// Kill The Window
	//_cprintf("hahadsfadsfasdfasdfaa");
	return (msg.wParam);							// Exit The Program
}











IMPLEMENT_DYNCREATE(COPENGLMFCView, CView)

BEGIN_MESSAGE_MAP(COPENGLMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//ON_COMMAND(ID_VIDEO, &COPENGLMFCView::OnVideo)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	//  ON_WM_MOUSEHWHEEL()



	ON_COMMAND(ID_32776, &COPENGLMFCView::OnVideoo)
END_MESSAGE_MAP()

// COPENGLMFCView 构造/析构
//float colorfunc(int x)
//{

//  return x > 128 ? 256 - sqrt((256 - x) * 128) : sqrt(x * 128);
//}

COPENGLMFCView::COPENGLMFCView()
{
	// TODO: 在此处添加构造代码

}

COPENGLMFCView::~COPENGLMFCView()
{
}

BOOL COPENGLMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COPENGLMFCView 绘图

void COPENGLMFCView::OnDraw(CDC* /*pDC*/)
{
	COPENGLMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here  

	// 清除颜色  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 绘制场景  
	glMatrixMode(GL_MODELVIEW);
}

// COPENGLMFCView 打印

BOOL COPENGLMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COPENGLMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COPENGLMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// COPENGLMFCView 诊断

#ifdef _DEBUG
void COPENGLMFCView::AssertValid() const
{
	CView::AssertValid();
}

void COPENGLMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COPENGLMFCDoc* COPENGLMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPENGLMFCDoc)));
	return (COPENGLMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COPENGLMFCView 消息处理程序


int COPENGLMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	AllocConsole();
	//  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  Add your specialized creation code here  

	// 创建DC  
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	// 选择像素格式  
	if (!bSetDCPixelFormat()) return -1;
	// 创建渲染环境, 并使它成为当前渲染环境  
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	return 0;
}


void COPENGLMFCView::OnSize(UINT nType, int cx, int cy)
{
	static int x = 1;
	SetTimer(1, 40, NULL);
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here  
	// 设置视口  
	//glutSpecialFunc(keyboardgl);
	glViewport(0, 0, cx, cy);
	// 设置投影矩阵(透视投影)  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)cx / (GLfloat)cy, 1.0, 1000.0);
	// 设置模型视图矩阵  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(youx*0.25, youy*0.25, youz*0.25, lookx*0.25, looky*0.25, lookz*0.25, upx, upy, upz);
}

void COPENGLMFCView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here  
	// 释放资源  
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	delete m_pDC; FreeConsole();
}
bool COPENGLMFCView::bSetDCPixelFormat()
{
	// 设置像素格式  
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // 结构的大小  
		1, // 结构的版本  
		PFD_DRAW_TO_WINDOW | // 在窗口(而不是位图)中绘图  
		PFD_SUPPORT_OPENGL | // 支持在窗口中进行OpenGL调用  
		PFD_DOUBLEBUFFER, // 双缓冲模式  
		PFD_TYPE_RGBA, // RGBA颜色模式  
		32, // 需要32位颜色  
		0, 0, 0, 0, 0, 0, // 不用于选择模式  
		0, 0, // 不用于选择模式  
		0, 0, 0, 0, 0, // 不用于选择模式  
		16, // 深度缓冲区的大小  
		0, // 在此不使用  
		0, // 在此不使用  
		0, // 在此不使用  
		0, // 在此不使用  
		0, 0, 0 // 在此不使用  
	};
	// 选择一种与pfd所描述的最匹配的像素格式  
	int nPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (0 == nPixelFormat) return false;
	// 为设备环境设置像素格式  
	return SetPixelFormat(m_pDC->GetSafeHdc(), nPixelFormat, &pfd);
}



void generate_shadow_matrix(GLfloat matrix[4][4], const GLfloat ground[4], const GLfloat light[4])
{
	GLfloat dot = 0;
	int i, j;

	for (i = 0; i < 4; i++) {
		dot += ground[i] * light[i];
	}



	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i == j) {
				matrix[i][j] = dot - ground[i] * light[j];
			}
			else {
				matrix[i][j] = -ground[i] * light[j];
			}
		}
	}
}




static void onMousecv(int event, int x, int y, int, void*)
{
	////_cprintf("x:%d    y: %d\n",x,y);
	switch (event)
	{

	case CV_EVENT_LBUTTONDOWN:
		mousedown = true;
		//_cprintf("(%d,%d)", frame2.cols, frame2.rows);
		//_cprintf("(%d,%d)\tr:%d\tg:%d\tb:%d\n", x, y, frame2.at<Vec3b>(y, x)(2), frame2.at<Vec3b>(y, x)(1), frame2.at<Vec3b>(y, x)(0));
		break;
	case CV_EVENT_MOUSEMOVE:
		break;
	case CV_EVENT_LBUTTONUP:
		mousedown = false;
		break;
	}
}
inline int number(int sx, int sy, int lx, int ly) {
	////_cprintf("%d %d %d %d \n",sx,sy,lx,ly);
	if (sy > 0 && sx > 0)
		return numbers[sy + ly - 1][lx - 1 + sx] - numbers[sy + ly - 1][sx - 1] - numbers[sy - 1][sx + lx - 1] + numbers[sy - 1][sx - 1];
	else if (sy > 0)
		return numbers[sy + ly - 1][lx - 1 + sx] - numbers[sy - 1][sx + lx - 1];
	else if (sx > 0)
		return  numbers[sy + ly - 1][lx - 1 + sx] - numbers[sy + ly - 1][sx - 1];
	else
		return  numbers[sy + ly - 1][lx - 1 + sx];
}
int* findblue()
{
	int sum = 0, sumx = 0, sumy = 0;
	{
		int b, r, g, m, mm;
		for (int i = 0; i < frame.rows; i++)
			for (int j = 0; j < frame.cols; j++)
				findarea[i][j] = -1;
		//for (m = 0; m < 12; m++)
		//{
			//for (int k = 0; k < 8; k++)
			//{


				for (int i = 0; i < frame.rows; i++)
					for (int j = 0; j < frame.cols; j++)
					{
						r = frame2.at<Vec3b>(i, j)(2);
						if (r > 160)
							continue;
						b = frame2.at<Vec3b>(i, j)(0);
						//mm = 0;
						//if (i > 0 && findarea[i - 1][j] >= 0)
						//	mm += 3;
						//if (j > 0 && findarea[i][j - 1] >= 0)
						//	mm += 3;
						//if (i + 1 < frame2.rows && findarea[i + 1][j] >= 0)
						//	mm += 3;
						//if (j + 1 < frame2.cols && findarea[i][j + 1] >= 0)
						//	mm += 3;
						//if (mm < m)
						//	break;
						g = frame2.at<Vec3b>(i, j)(1);
						if (b*30 > 36*r + g * 3 + 300)//rgb
						{
							if(iiii)
							frame2.at<Vec3b>(i, j) = Vec3b(0, 255, 255);
							findarea[i][j] = 0;
							////_cprintf("%d %dha\n", i, j);
						}
					}
				//if (i > 0 && (r - frame2.at<Vec3b>(i-1, j)(2))*(r -frame2.at<Vec3b>(i-1, j)(2))+ (g -frame2.at<Vec3b>(i-1, j)(1))*(g-frame2.at<Vec3b>(i-1, j)(1))+(b- frame2.at<Vec3b>(i-1, j)(0))*(b -frame2.at<Vec3b>(i-1, j)(0))<6)

				//if (j > 0 && (r - frame2.at<Vec3b>(i, j-1)(2))*(r -frame2.at<Vec3b>(i, j-1)(2))+ (g -frame2.at<Vec3b>(i, j-1)(1))*(g-frame2.at<Vec3b>(i, j-1)(1))+(b- frame2.at<Vec3b>(i, j-1)(0))*(b -frame2.at<Vec3b>(i, j-1)(0))<6)

				//if (i+1<frame2.rows && (r - frame2.at<Vec3b>(i+1, j)(2))*(r -frame2.at<Vec3b>(i+1, j)(2))+ (g -frame2.at<Vec3b>(i+1, j)(1))*(g-frame2.at<Vec3b>(i+1, j)(1))+(b- frame2.at<Vec3b>(i+1, j)(0))*(b -frame2.at<Vec3b>(i+1, j)(0))<6)

				//if (j+1<frame2.cols && (r - frame2.at<Vec3b>(i, j+1)(2))*(r -frame2.at<Vec3b>(i, j+1)(2))+ (g -frame2.at<Vec3b>(i, j+1)(1))*(g-frame2.at<Vec3b>(i, j+1)(1))+(b- frame2.at<Vec3b>(i, j+1)(0))*(b -frame2.at<Vec3b>(i, j+1)(0))<6)
			//}
		//}

	}

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++)
		{
			if (findarea[i][j] >= 0)
			{
				numbers[i][j] = i == 0 ? j == 0 ? 1 : numbers[i][j - 1] + 1 : j == 0 ? numbers[i - 1][j] + 1 : numbers[i][j - 1] - numbers[i - 1][j - 1] + numbers[i - 1][j] + 1;
				//  //_cprintf("haha%d %d %d\n",i,j,numbers[i][j]);
			}
			else
			{
				////_cprintf("haha%d %d %d\n", i, j, numbers[i][j]);
				numbers[i][j] = i == 0 ? j == 0 ? 0 : numbers[i][j - 1] : j == 0 ? numbers[i - 1][j] : numbers[i][j - 1] - numbers[i - 1][j - 1] + numbers[i - 1][j];
				//if(i>475 && j>635)
				////_cprintf("hehe%d %d %d\n", i, j, numbers[i][j]);
			}
		}
	}
	int* ret = new int[3];
	if (numbers[frame.rows - 1][frame.cols - 1] == 0)
	{
		////_cprintf("qwerwerqewrqwerqwer\n");
		ret[0] = ret[1] = ret[2] = 0;
		return ret;

	}

	////_cprintf("%d   sd\n",sumx);
	{
		int sizex = frame.cols, sizey = frame.rows, startx = frame.cols - frame.rows, starty = 0, max, a, premax = 0, presizex, presizey, prestartx, prestarty;

		if (frame.cols > frame.rows)
		{
			sizex = sizey;
			max = number(frame.cols - frame.rows, 0, frame.rows, frame.rows);
			//  //_cprintf("%d  %d is s",a,max);
			for (int i = 0;; i++)
			{
				if (frame.cols < i*frame.rows)
				{
					for (int j = 0; j < i; j++)
					{
						if ((a = number(j*(frame.cols - frame.rows) / i, 0, frame.rows, frame.rows))>max)
						{
							////_cprintf("%d  %d is s",a,max);
							max = a; startx = j * (frame.cols - frame.rows) / i;
						}
					}
					break;

				}
			}
		}
		else
		{
			sizey = sizex;
			max = number(0, frame.rows - frame.cols, frame.cols, frame.cols);
			for (int i = 0;; i++)
			{
				if (frame.rows < i*frame.cols)
				{
					for (int j = 0; j < i; j++)
					{
						if ((a = number(0, j*(frame.rows - frame.cols) / i, frame.cols, frame.cols))>max)
						{
							max = a; starty = j * (frame.rows - frame.cols) / i;
						}
					}
					break;
				}
			}

		}
		{
			int colorwindow[3][3], a;
			presizey = sizey + 1;
			premax = -2;
			while (premax*0.99<max && presizey >sizey)
			{
				if (sizex == 1)
					break;

				premax = max;
				prestartx = startx;
				prestarty = starty;
				presizex = sizex;
				presizey = sizey;
				////_cprintf("pre:%d %d %d %d %d now:%d %d %d %d %d ", premax, prestartx, prestarty, presizex, presizey, max, startx, starty, sizex, sizey);
				//      //_cprintf("%d %d %d \n",prestartx,prestarty,presizex);
				max = 0;
				for (int i = 0; i<3; i++)
					for (int j = 0; j<3; j++)
					{
						//              //_cprintf("haha");
						a = colorwindow[i][j] = number(prestartx + i * presizex / 16, prestarty + j * presizey / 16, (i + 14)*presizex / 16 - i * presizex / 16, (j + 14)*presizey / 16 - j * presizey / 16);
						////_cprintf("%d colorwindow[%d][%d] pre:%d %d %d %d\n",colorwindow[i][j],i,j, prestartx + i * presizex / 16, prestarty + j * presizey / 16, (i + 14)*presizex / 16 - i * presizex / 16, (j + 14)*presizey / 16 - j * presizey / 16);
						if (max<a)
						{
							////_cprintf("hahabigger");
							////_cprintf("%d colorwindow[%d][%d]\n", colorwindow[i][j], i, j);
							max = a;
							startx = prestartx + i * presizex / 16;
							starty = prestarty + j * presizey / 16;
							sizex = (i + 14)*presizex / 16 - i * presizex / 16;
							sizey = (j + 14)*presizey / 16 - j * presizey / 16;
						}


					}
			}
		}
		//  //_cprintf("prre%d %d %d %d\n", prestarty,presizey,prestartx,presizex);
		//if (presizex > 300)
		//{

		//  for (int i = 0; i < frame.rows; i++)
		//for (int j = 0; j < frame.cols; j++)
		////_cprintf("num[%d][ %d]= %d\n", i, j, numbers[i][j]);
		//      //_cprintf("a");
		//}
		prestartx -= presizex / 16;
		prestarty -= presizey / 16;
		presizex = 1.125*presizex + prestartx;
		presizey = 1.125*presizey + prestarty;
		if (prestartx < 0)
			prestartx = 0;
		if (prestarty < 0)
			prestarty = 0;
		if (presizex >frame.cols)
			presizex = frame.cols;
		if (presizey > frame.rows)
			presizey = frame.rows;
		////_cprintf("pre%d %d %d %d\n", prestarty,presizey,prestartx,presizex);
		if (iiii)
		rectangle(frame2, Rect(prestartx,prestarty,presizex-prestartx,presizey - prestarty), Scalar(0, 0, 255), 3, 4, 0);
		for (int i = prestarty; i < presizey; i++)
			for (int j = prestartx; j < presizex; j++)
			{
				////_cprintf("%d %d\n", i, j);
				if (findarea[i][j] >= 0)
				{
					sum++;
					sumx += j;
					sumy += i;

				}
			}
		////_cprintf("pre%d %d %d %d\n", prestarty,presizey,prestartx,presizex);


	}
	if (sum == 0)
	{
		////_cprintf("%d", numbers[frame.rows - 1][frame.cols - 1]);
		ret[0] = ret[1] = ret[2] = 0;
	}
	ret[0] = sumx / sum;
	ret[1] = sumy / sum;
	ret[2] = sum;
	return  ret;
}


void COPENGLMFCView::createlight(float* it, bool sel)
{
	float cx = it[1] * 0.25;
	float cy = it[2] * 0.25;
	float cz = it[3] * 0.25;
	{
		GLfloat sun_light_position[] = { cx, cy, cz, 1.0f };
		GLfloat sun_light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat sun_light_diffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat sun_light_specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		glLightfv(it[4], GL_POSITION, sun_light_position);
		glLightfv(it[4], GL_AMBIENT, sun_light_ambient);
		glLightfv(it[4], GL_DIFFUSE, sun_light_diffuse);
		glLightfv(it[4], GL_SPECULAR, sun_light_specular);
		glLightf(it[4], GL_SPOT_CUTOFF, 180);
		glEnable(it[4]);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(400 / sqrt((cx - youx)*(cx - youx) + (cy - youy)*(cy - youy) + (cz - youz)*(cz - youz)));
		glBegin(GL_TRIANGLE_STRIP);
		if (sel)
			glColor3f(1.0, 1.0, 0.0);






		else
			glColor3f(1.0, 1.0, 1.0);
		for (int i = 0; i<40; i++)
			for (int j = 0; j < 32; j++)
			{
				if (i%19 == 0 && j % 8 == 0) {
					glVertex3f(cx + 0.05 * sin(i*PI / 20), cy + 0.05 * cos(i*PI / 20)*sin(j*PI / 15), cz + 0.05 * cos(i*PI / 20)*cos(j*PI / 15));
					glVertex3f(cx +  sin(i*PI / 20), cy + cos(i*PI / 20)*sin(j*PI / 15), cz + cos(i*PI / 20)*cos(j*PI / 15));
					glVertex3f(cx + 0.05 * sin((i + 1)*PI / 20), cy + 0.05 * cos((i + 1)*PI / 20)*sin(j*PI / 15), cz + 0.05 * cos((i + 1)*PI / 20)*cos(j*PI / 15));

				}
				else {
				glVertex3f(cx + 0.05 * sin(i*PI / 20), cy + 0.05 * cos(i*PI / 20)*sin(j*PI / 15), cz + 0.05 * cos(i*PI / 20)*cos(j*PI / 15));
				glVertex3f(cx + 0.05 * sin((i + 1)*PI / 20), cy + 0.05 * cos((i + 1)*PI / 20)*sin(j*PI / 15), cz + 0.05 * cos((i + 1)*PI / 20)*cos(j*PI / 15));
				}

			}
		glEnd();
	}

}

void COPENGLMFCView::createsphere(float* it, bool sel)
{

	//CCreate CreateCubeeee;
	//CreateCubeeee.OnEnChangeEdit1();
	//CreateCubeeee.OnEnChangeEdit2();
	//CreateCubeeee.OnEnChangeEdit3();
	float cx = it[1] * 0.25;
	float cy = it[2] * 0.25;
	float cz = it[3] * 0.25;
	float r = it[4] * 0.25;



	if (!shadow)
	{
		GLfloat sun_mat_ambient[] = { 0.8f, 0.3f, 0.3f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.8f, 0.3f, 0.3f, 1.0f };
		GLfloat sun_mat_specular[] = { 1.0f, 0.5f, 0.5f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glBegin(GL_TRIANGLE_STRIP);
		if (sel) {
			glColor3f(1.0, 1.0, 0.0);
			for (int i = 0; i<40; i++)
				for (int j = 0; j < 32; j++)
				{
					glVertex3f(cx + r * sin(i*PI / 20), cy + r * cos(i*PI / 20)*sin(j*PI / 15), cz + r * cos(i*PI / 20)*cos(j*PI / 15));
					glVertex3f(cx + r * sin((i + 1)*PI / 20), cy + r * cos((i + 1)*PI / 20)*sin(j*PI / 15), cz + r * cos((i + 1)*PI / 20)*cos(j*PI / 15));
				}

		}
		else
			for (int i = 0; i<40; i++)
				for (int j = 0; j < 32; j++)
				{
					glColor3f(1.0, abs(i - 20) / 100.0 + 0.8, abs(j - 18) / 100.0 + 0.82);
					glVertex3f(cx + r * sin(i*PI / 20), cy + r * cos(i*PI / 20)*sin(j*PI / 15), cz + r * cos(i*PI / 20)*cos(j*PI / 15));
					glVertex3f(cx + r * sin((i + 1)*PI / 20), cy + r * cos((i + 1)*PI / 20)*sin(j*PI / 15), cz + r * cos((i + 1)*PI / 20)*cos(j*PI / 15));
				}
		glEnd();
	}
	else
	{

		GLfloat sun_mat_ambient[] = { 0,0,0, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0,0,0, 1.0f };
		GLfloat sun_mat_specular[] = { 0,0,0, 1.0f };
		GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i<40; i++)
			for (int j = 0; j < 32; j++)
			{
				glColor3f(0, 0, 0);
				glVertex3f(cx + r * sin(i*PI / 20), cy + r * cos(i*PI / 20)*sin(j*PI / 15), cz + r * cos(i*PI / 20)*cos(j*PI / 15));
				glVertex3f(cx + r * sin((i + 1)*PI / 20), cy + r * cos((i + 1)*PI / 20)*sin(j*PI / 15), cz + r * cos((i + 1)*PI / 20)*cos(j*PI / 15));
			}
		glEnd();
	}

}
void COPENGLMFCView::createcube(float* it, bool sel)
{


	float cx = it[1] * 0.25;
	float cy = it[2] * 0.25;
	float cz = it[3] * 0.25;
	float r = it[4];
	////_cprintf("pos %f %f %f\n", cx,cy,cz);

	if (!shadow)

	{
		{
			GLfloat sun_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			GLfloat sun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
			GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat sun_mat_shininess = 0.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
			glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
			if (sel)
			{
				glBegin(GL_QUADS);




				glColor3f(1.0, 1.0, 0.0);
				glVertex3f(cx + r, cy + r, cz - r);
				glVertex3f(cx - r, cy + r, cz - r);
				glVertex3f(cx - r, cy - r, cz - r);
				glVertex3f(cx + r, cy - r, cz - +r);
				glEnd();


				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz + r);
				glVertex3f(cx - r, cy - r, cz + r);
				glVertex3f(cx + r, cy - r, cz + r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy - r, cz + r);
				glVertex3f(cx - r, cy - r, cz + r);
				glVertex3f(cx - r, cy - r, cz - r);
				glVertex3f(cx + r, cy - r, cz - r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz - r);
				glVertex3f(cx + r, cy + r, cz - r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx - r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz - r);
				glVertex3f(cx - r, cy - r, cz - r);
				glVertex3f(cx - r, cy - r, cz + r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy + r, cz + r);
				glVertex3f(cx + r, cy + r, cz - r);
				glVertex3f(cx + r, cy - r, cz - r);
				glVertex3f(cx + r, cy - r, cz + r);
				glEnd();

			}
			else
			{
				glBegin(GL_QUADS);
				glColor3f(0.5, 0.5, 1.0);
				glVertex3f(cx + r, cy + r, cz - r);
				glColor3f(0.7, 0.7, 1.0);
				glVertex3f(cx - r, cy + r, cz - r);
				glColor3f(0.9, 0.9, 1.0);
				glVertex3f(cx - r, cy - r, cz - r);
				glColor3f(0.7, 0.7, 1.0);
				glVertex3f(cx + r, cy - r, cz - +r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz + r);
				glVertex3f(cx - r, cy - r, cz + r);
				glVertex3f(cx + r, cy - r, cz + r);
				glEnd();
				glBegin(GL_QUADS);
				glColor3f(0.55, 0.55, 1.0);
				glVertex3f(cx + r, cy - r, cz + r);
				glColor3f(0.75, 0.75, 1.0);
				glVertex3f(cx - r, cy - r, cz + r);
				glColor3f(0.95, 0.95, 1.0);
				glVertex3f(cx - r, cy - r, cz - r);
				glColor3f(0.75, 0.75, 1.0);
				glVertex3f(cx + r, cy - r, cz - r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz + r);
				glVertex3f(cx - r, cy + r, cz - r);
				glVertex3f(cx + r, cy + r, cz - r);
				glEnd();
				glBegin(GL_QUADS);
				glColor3f(0.5, 0.5, 1.0);
				glVertex3f(cx - r, cy + r, cz + r);
				glColor3f(0.75, 0.75, 1.0);
				glVertex3f(cx - r, cy + r, cz - r);
				glColor3f(0.9, 0.9, 1.0);
				glVertex3f(cx - r, cy - r, cz - r);
				glColor3f(0.75, 0.75, 1.0);
				glVertex3f(cx - r, cy - r, cz + r);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(cx + r, cy + r, cz + r);
				glVertex3f(cx + r, cy + r, cz - r);
				glVertex3f(cx + r, cy - r, cz - r);
				glVertex3f(cx + r, cy - r, cz + r);
				glEnd();

			}

		}
	}
	else
	{
		{

			GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat sun_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat sun_mat_shininess = 0.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
			glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
			glBegin(GL_QUADS);
			glVertex3f(cx + r, cy + r, cz - r);
			glVertex3f(cx - r, cy + r, cz - r);
			glVertex3f(cx - r, cy - r, cz - r);
			glVertex3f(cx + r, cy - r, cz - +r);




			glEnd();








			glBegin(GL_QUADS);
			glVertex3f(cx + r, cy + r, cz + r);
			glVertex3f(cx - r, cy + r, cz + r);
			glVertex3f(cx - r, cy - r, cz + r);
			glVertex3f(cx + r, cy - r, cz + r);




			glEnd();








			glBegin(GL_QUADS);
			glVertex3f(cx + r, cy - r, cz + r);
			glVertex3f(cx - r, cy - r, cz + r);
			glVertex3f(cx - r, cy - r, cz - r);
			glVertex3f(cx + r, cy - r, cz - r);




			glEnd();








			glBegin(GL_QUADS);
			glVertex3f(cx + r, cy + r, cz + r);
			glVertex3f(cx - r, cy + r, cz + r);
			glVertex3f(cx - r, cy + r, cz - r);
			glVertex3f(cx + r, cy + r, cz - r);




			glEnd();








			glBegin(GL_QUADS);
			glVertex3f(cx - r, cy + r, cz + r);
			glVertex3f(cx - r, cy + r, cz - r);
			glVertex3f(cx - r, cy - r, cz - r);
			glVertex3f(cx - r, cy - r, cz + r);

			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(cx + r, cy + r, cz + r);
			glVertex3f(cx + r, cy + r, cz - r);
			glVertex3f(cx + r, cy - r, cz - r);
			glVertex3f(cx + r, cy - r, cz + r);
			glEnd();
		}
	}
}








void COPENGLMFCView::myDisPlay(void)
{
	const GLfloat max = (GLfloat)10.0f;//INT_MAX;  
	shadow = false;
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);




	glPushMatrix();
	//glutSolidSphere(10.0f, 10, 10);
	if (thirdpersonview)//thirdman
	{


	}

	glEnd();
	glPopMatrix();//thirdman
	if (iii)
	{
	glPushMatrix();
	{
		////_cprintf("%f\n",max);
		glLineWidth(9.0);
		glBegin(GL_LINES);
		// x  
		glColor3f(deg / 6.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(max, 0.0, 0.0);
		// y  
		glColor3f(0.0, deg / 6.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, max, 0.0);
		// z  
		glColor3f(0.0, 0.0, deg / 6.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, max);
		glEnd();
		// 虚线部分  
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(3, 0xAAAA);
		glBegin(GL_LINES);
		// x  

		glColor3f(deg / 6.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-max, 0.0, 0.0);
		// y  
		glColor3f(0.0, deg / 6.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, -max, 0.0);
		// z  
		glColor3f(0.0, 0.0, deg / 6.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, -max);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}
	glPopMatrix();}

	

	createcubee();
	glPushMatrix();
	glLineWidth(1.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);//floor
	/*
	glColor4f(0.9, 0.6, 0.99, 0.0);
	glLineWidth(2);
	glBegin(GL_LINES);

	






	float z = -5.5, y1 = 50;
	for (float x1 = -50; x1<50; ++x1)
	{
		glVertex3f(x1, y1, z);
		glVertex3f(x1, -y1, z);
	}
	float x2 = 50;
	for (float y2 = -50; y2<50; ++y2)
	{
		glVertex3f(x2, y2, z);
		glVertex3f(-x2, y2, z);
	}
	glEnd();*/
	glBegin(GL_QUADS);
	glColor3f(158 / 256.0, 133 / 256.0, 93 / 256.0);
	glVertex3f(-50, -50, -5.51);
	glColor3f(53 / 256.0, 44 / 256.0, 31 / 256.0);
	glVertex3f(-50, 50, -5.51);
	glVertex3f(50, 50, -5.51);
	glColor3f(158 / 256.0, 133 / 256.0, 93 / 256.0);
	glVertex3f(50, -50, -5.51);
	glEnd();

	/*
	
	glBegin(GL_QUADS);
	glColor3f(158 / 256.0, 133 / 256.0, 93 / 256.0);
	glVertex3f(-49.9, -49.9, -5.51);
	glVertex3f(-49.9, 49.9, -5.51);
	glVertex3f(-49.9, 49.9, 49.9);
	glVertex3f(-49.9, -49.9, 49.9);
	glEnd();







	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glColor4f(0.9, 0.6, 0.99, 0.0);
	
	glBegin(GL_LINES);
	float x = -50, y3 = 50;
	for (float z1 = -5.5; z1<50; ++z1)
	{
	glVertex3f(x, y3, z1);
	glVertex3f(x, -y3, z1);
	}
	float z2 = 50;
	for (float y4 = -50; y4<50; ++y4)
	{
	glVertex3f(x, y4, z2);
	glVertex3f(-x, y4, z2);
	}
	glEnd();

	
	glBegin(GL_QUADS);
	glColor3f(158 / 256.0, 133 / 256.0, 93 / 256.0);


	glVertex3f(-49.9, 49.9, -5.51);
	glVertex3f(49.9, 49.9, -5.51);
	glVertex3f(49.9, 49.9, 49.9);
	glVertex3f(-49.9, 49.9, 49.9);
	glEnd();



	glBegin(GL_LINES);
	glColor4f(1, 1, 1, 0.0);
	glVertex3f(-50, 50, -5.51);
	glVertex3f(-50, 50, 50);
	glEnd();
	*/
	if (prevideo[1] != 100 && nowmode != 2)
	{





		glPointSize(2000 / sqrt((videoxx - youx)*(videoxx - youx) + (videoyy - youy)*(videoyy - youy) + (videozz - youz)*(videozz - youz)));
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);//点的颜色为红色
		glVertex3f(videoxx*0.25, videoyy*0.25, videozz*0.25);//顶点（vertex）位置：(0.7, 0.5, 0.4)
		glEnd();//结束绘制点
	}
	glPopMatrix();//floor
	for (int i = 0; i<itemnum; i++)
	{
		bool sel = selectt == i;
		switch ((int)item[i][0])
		{
		case 2:
			createlight(item[i], sel);
			break;
		}
	}
	for (int i = 0; i<itemnum; i++)
	{
		//_cprintf("%d ", item[i][0]);
		shadow = false;
		bool sel = selectt == i;
		glNewList(1 + i * 2, GL_COMPILE);
		switch ((int)item[i][0])
		{
		case 1:
			createcube(item[i], sel);
			////_cprintf("%f %f %f\n",item[i][1],item[i][2],item[i][3]);
			break;
		case 3:
			createsphere(item[i], sel);
			break;
		}
		glEndList();
		glCallList(1 + i * 2);
		shadow = true;
		glNewList(2 + i * 2, GL_COMPILE);
		glColor3f(0, 0, 0);
		switch ((int)item[i][0])
		{
		case 1:
			createcube(item[i], sel);
			////_cprintf("%f %f %f\n",item[i][1],item[i][2],item[i][3]);
			break;
		case 3:
			createsphere(item[i], sel);
			break;
		}
		glEndList();
		for (int ii = 0; ii < linum; ii++)
		{
			////_cprintf("no.%ditem position%f %f %f \n", i,item[i][1],item[i][2],item[i][3]);
			////_cprintf("no.%dlight%f %f %f \n", ii,li[ii][0],li[ii][1],li[ii][2]);
			float relative[4] = { li[ii][0] * 0.25,li[ii][1] * 0.25,li[ii][2] * 0.25,1 };
			glPushMatrix();
			generate_shadow_matrix(shadow_matrix, ground, relative);
			glMultMatrixf((GLfloat*)shadow_matrix);
			glColor3f(0, 0, 0);
			glCallList(2 + i * 2);
			glPopMatrix();
		}
		////_cprintf("%dlight   %ditem\n", linum,itemnum);
	}


	SwapBuffers(wglGetCurrentDC());
}



void COPENGLMFCView::review(void)
{
	glLoadIdentity();
	if (thirdpersonview)
		if (nowmode == -2)
			gluLookAt(youx*5.25 - lookix * 5, youy*5.25 - lookiy * 5, youz*5.25 - lookiz * 5, lookix*0.25, lookiy*0.25, lookiz*0.25, upix, upiy, upiz);//临时视角
		else
			gluLookAt(youx*5.25 - lookx * 5, youy*5.25 - looky * 5, youz*5.25 - lookz * 5, lookx*0.25, looky*0.25, lookz*0.25, upx, upy, upz);

	else
		if (nowmode == -2)
			gluLookAt(youx*0.25, youy*0.25, youz*0.25, lookix*0.25, lookiy*0.25, lookiz*0.25, upix, upiy, upiz);//临时视角
		else
			gluLookAt(youx*0.25, youy*0.25, youz*0.25, lookx*0.25, looky*0.25, lookz*0.25, upx, upy, upz);
	myDisPlay();
}

void COPENGLMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// 设置背景色  
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// TODO: Add your specialized code here and/or call the base class  
}

void COPENGLMFCView::OnTimer(UINT_PTR nIDEvent)
{   //动画
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	////_cprintf("%d\n",deg);
	deg = deg<5 ? deg + 1 : 0;
	if(!radiositybool)
	myDisPlay();
	//glutPostRedisplay();
	CView::OnTimer(nIDEvent);
}





/*
// TextOpenCv.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
void changecolor(Mat& img, int rgb, int deg, int width)
{
deg %= 256;
Vec3b color;
if (rgb >= 0 && rgb <3)
{
for (size_t row = 0; row<img.rows; row++)
for (size_t col = 0; col<img.cols; col++)
{
//设置原图像中某点的BGR颜色值
color = Vec3b(0, 0, 0);
color(rgb) = img.at<Vec3b>(row, col)(rgb);
if (color(rgb) % 256 > deg && color(rgb) % 256<(deg + width) || color(rgb) % 256 + 256 < deg && color(rgb) % 256>(deg + width))
{
img.at<Vec3b>(row, col) = Vec3b(255, 255, 255);
img.at<Vec3b>(row, col)(rgb) = 0;
}
else
img.at<Vec3b>(row, col) = color;

}

}
}

void cgcolor(Mat& img, int rgb)
{
Vec3b color;
if (rgb >= 0 && rgb <3)
{
for (size_t row = 0; row<img.rows; row++)
for (size_t col = 0; col<img.cols; col++)
{
//设置原图像中某点的BGR颜色值
color = Vec3b(0, 0, 0);
color(rgb) = img.at<Vec3b>(row, col)(rgb);
img.at<Vec3b>(row, col) = color;

}

}
}
void findedge(Mat& img, int rgb, int deg=0, int width=0)
{
int ***pic =(int***) new int**[img.rows];

for (int i = 0; i <img.rows; i++)
{
pic[i] = (int**)new int*[img.cols];

for (int j = 0; j < img.cols; j++)
{
pic[i][j] = (int*)new int[4];
pic[i][j][0] = i > 0 ? img.at<Vec3b>(i - 1, j)(rgb) - img.at<Vec3b>(i, j)(rgb) : 0;
pic[i][j][1] = i < (img.rows-1) ? img.at<Vec3b>(i + 1, j)(rgb)- img.at<Vec3b>(i , j)(rgb) : 0;
pic[i][j][2] = j > 0 ? img.at<Vec3b>(i, j-1)(rgb) - img.at<Vec3b>(i, j)(rgb) : 0;
pic[i][j][3] = j < img.cols-1 ? img.at<Vec3b>(i , j+1)(rgb) - img.at<Vec3b>(i, j)(rgb) : 0;
}
}
for (int i = 0; i <img.rows; i++)
{

for (int j = 0; j < img.cols; j++)
{
if (pic[i][j][3] > deg || pic[i][j][3] <-deg || pic[i][j][2] > deg || pic[i][j][2] <-deg || pic[i][j][1] > deg || pic[i][j][1] <-deg || pic[i][j][0] > deg || pic[i][j][0] <-deg)
{

img.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
img.at<Vec3b>(i, j)(rgb) = 0;
}

}
}
for (int i = 0; i <img.rows; i++)
{

for (int j = 0; j < img.cols; j++)
{
delete[] pic[i][j];

}
delete[] pic[i];
}
delete[] pic;
}
int main() {
// 读入一张图片（游戏原画）
Mat imgmother = imread("pic.jpg");
Mat img = imgmother.clone();
Mat img2 = imgmother.clone();
Mat img3 = imgmother.clone();

// 创建一个名为 "游戏原画"窗口
namedWindow("pic");
// 在窗口中显示游戏原画
namedWindow("pic2");
namedWindow("pic3");

imshow("pic3", img3);
imshow("pic2", img2);
imshow("pic", img);
int d = 0;
for (;;)
{
int c = waitKey(0);

switch ((char)c)
{
case '\x1b':
cout << "Exiting ..." << endl;
goto exit_main;
case 'r':
cout << "changered" << endl;
changecolor(img, 'r',d,20);
break;
case 'g':
cout << "changegreen" << endl;
changecolor(img2, 'g', d, 20);
break;
case 'b':
cout << "changeblue" << endl;
changecolor(img3, 'b', d, 20);
imshow("pic3", img3);
break;
case 'n':
cout << "<" << "... ";
break;
}

changecolor(img, 0, d, 20);
changecolor(img2, 1, d, 20);
changecolor(img3, 2, d, 20);
d++;
d %= 256;
cout << d << endl;
}
img = imgmother.clone();
img2 = imgmother.clone();
img3 = imgmother.clone();
cgcolor(img, 0);
cgcolor(img2, 1);
cgcolor(img3, 2);
findedge(img, 0, 30);
findedge(img2, 1, 30);
findedge(img3, 2, 30);
imshow("pic3", img3);
imshow("pic2", img2);
imshow("pic", img);
waitKey(0);

exit_main:
destroyWindow("游戏原画");
return 0;
}
*/










void COPENGLMFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	double i, j, k, ii, jj, kk;
	_cprintf("press %c", nChar);
	if (nChar == 16)
	{
		shiftctrlalt += 1;
		_cprintf(" with shift", nChar);
	}
	if (nChar == 17)
	{
		shiftctrlalt += 2;
		_cprintf(" and ctrl", nChar);
	}
	if (nChar == 18)
		shiftctrlalt += 4;
	_cprintf("\n", nChar);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//_cprintf("shiftctrl is %d\n", shiftctrlalt);
	switch (nChar)
	{
	case 87://front W
		switch (shiftctrlalt)
		{
		case 3:

			youy += 4;
			looky += 4;
			break;
		case 0:
			i = lookx * 5 - youx * 4;
			j = looky * 5 - youy * 4;
			k = lookz * 5 - youz * 4;
			youx += (lookx - youx) * 4;
			youy += (looky - youy) * 4;
			youz += (lookz - youz) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			break;
		case 1:


			i = youx + 0.08715574274765816*upx + 0.9961946980917455*(lookx - youx);
			j = youy + 0.08715574274765816*upy + 0.9961946980917455*(looky - youy);
			k = youz + 0.08715574274765816*upz + 0.9961946980917455*(lookz - youz);
			ii = 0.9961946980917455*(upx)-0.08715574274765816*(lookx - youx);
			jj = 0.9961946980917455*(upy)-0.08715574274765816*(looky - youy);
			kk = 0.9961946980917455*(upz)-0.08715574274765816*(lookz - youz);
			upx = ii;
			upy = jj;
			upz = kk;
			lookx = i;
			looky = j;
			lookz = k;
		}
		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 83://behind S
		switch (shiftctrlalt)

		{


		case 3:

			youy -= 4;
			looky -= 4;
			break;
		case 0:
			i = -lookx * 3 + youx * 4;
			j = -looky * 3 + youy * 4;
			k = -lookz * 3 + youz * 4;
			youx -= (lookx - youx) * 4;
			youy -= (looky - youy) * 4;
			youz -= (lookz - youz) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			break;
		case 1:


			i = youx - 0.08715574274765816*upx + 0.9961946980917455*(lookx - youx);
			j = youy - 0.08715574274765816*upy + 0.9961946980917455*(looky - youy);
			k = youz - 0.08715574274765816*upz + 0.9961946980917455*(lookz - youz);
			ii = 0.9961946980917455*(upx)+0.08715574274765816*(lookx - youx);
			jj = 0.9961946980917455*(upy)+0.08715574274765816*(looky - youy);
			kk = 0.9961946980917455*(upz)+0.08715574274765816*(lookz - youz);
			upx = ii;
			upy = jj;
			upz = kk;
			lookx = i;
			looky = j;
			lookz = k;
		}
		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 65://left A
		switch (shiftctrlalt)

		{


		case 3:

			youx -= 4;
			lookx -= 4;
			break;
		case 0:
			i = lookx - ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			j = looky - ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			k = lookz - ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			ii = youx - ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			jj = youy - ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			kk = youz - ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			youx = ii;
			youy = jj;
			youz = kk;
			break;
		case 1:



			i = youx - 0.08715574274765816*(looky - youy) + 0.9961946980917455*(lookx - youx);
			j = youy + 0.08715574274765816*(lookx - youx) + 0.9961946980917455*(looky - youy);
			ii = -0.08715574274765816*(upy)+0.9961946980917455*(upx);
			jj = 0.08715574274765816*(upx)+0.9961946980917455*(upy);
			lookx = i;
			looky = j;
			upx = ii;
			upy = jj;
		}
		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 68://right D
		switch (shiftctrlalt)

		{


		case 3:

			youx += 4;
			lookx += 4;
			break;
		case 0:
			i = lookx + ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			j = looky + ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			k = lookz + ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			ii = youx + ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			jj = youy + ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			kk = youz + ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			youx = ii;
			youy = jj;
			youz = kk;
			break;
		case 1:



			i = youx + 0.08715574274765816*(looky - youy) + 0.9961946980917455*(lookx - youx);
			j = youy - 0.08715574274765816*(lookx - youx) + 0.9961946980917455*(looky - youy);
			ii = +0.08715574274765816*(upy)+0.9961946980917455*(upx);
			jj = -0.08715574274765816*(upx)+0.9961946980917455*(upy);
			lookx = i;
			looky = j;
			upx = ii;
			upy = jj;
		}
		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 81://up Q
		switch (shiftctrlalt)
		{


		case 3:

			youz += 4;
			lookz += 4;
			break;
		case 0:
			youx += upx * 2;
			youy += upy * 2;
			youz += upz * 2;
			lookx += upx * 2;
			looky += upy * 2;
			lookz += upz * 2;
			break;
		case 1:


			i = youx - 0.08715574274765816*((looky - youy)*upz - (lookz - youz)*upy) + 0.9961946980917455*(lookx - youx);
			j = youy - 0.08715574274765816*((lookz - youz)*upx - (lookx - youx)*upz) + 0.9961946980917455*(looky - youy);
			k = youz - 0.08715574274765816*((lookx - youx)*upy - (looky - youy)*upx) + 0.9961946980917455*(lookz - youz);
			lookx = i;
			looky = j;
			lookz = k;
		}







		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 69://down E
		switch (shiftctrlalt)
		{


		case 3:

			youz -= 4;
			lookz -= 4;
			break;
		case 0:
			youx -= upx * 2;
			youy -= upy * 2;
			youz -= upz * 2;
			lookx -= upx * 2;
			looky -= upy * 2;
			lookz -= upz * 2;
			break;
		case 1:


			i = youx + 0.08715574274765816*((looky - youy)*upz - (lookz - youz)*upy) + 0.9961946980917455*(lookx - youx);
			j = youy + 0.08715574274765816*((lookz - youz)*upx - (lookx - youx)*upz) + 0.9961946980917455*(looky - youy);
			k = youz + 0.08715574274765816*((lookx - youx)*upy - (looky - youy)*upx) + 0.9961946980917455*(lookz - youz);
			lookx = i;
			looky = j;
			lookz = k;
		}







		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 66:// B
		switch (shiftctrlalt)
		{


		case 1:
			lookx = youx;
			looky = youy + 1;
			lookz = youz;
			upx = 0;
			upy = 0;
			upz = 1;
			break;
		case 0:
			i = sqrt(youx*youx + youy * youy + youz * youz);
			lookx = youx - youx / i;
			looky = youy - youy / i;
			lookz = youz - youz / i;
			j = -sqrt(youz*youz*youx*youx + youz * youz*youy*youy + (youx*youx + youy * youy)*(youx*youx + youy * youy));
			upx = youz * youx / j;
			upy = youz * youy / j;
			upz = -(youx*youx + youy * youy) / j;
			break;
		case 3:
			upx = 0;
			upy = 0;
			upz = 1;
			youx = 0;
			youy = -10;
			youz = 0;
			lookx = youx;
			looky = youy + 1;
			lookz = youz;
			break;
		}
		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 86:// V
		thirdpersonview = !thirdpersonview;
		//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
		break;
	case 27:
		cvwindow = false;
		break;
	case 82:
		radiositybool = true;
		showr();
		PostMessage(WM_QUIT, 0, 0);//最常用
	}
	review();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void COPENGLMFCView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//_cprintf("%d up", nChar);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	shiftctrlalt = 0;

	if (GetKeyState(16)<0)
		shiftctrlalt += 1;
	if (GetKeyState(17)<0)
		shiftctrlalt += 2;
	if (GetKeyState(18)<0)
		shiftctrlalt += 4;
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void COPENGLMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	double i, j, k, ii, jj, kk, n;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetKeyState(1) & 0x8000) {
		_cprintf("mouseleft down\n");
		if (point.y != pointy)
		{

			i = youx + sin((point.y - pointy) / 512.0)*upx + cos((point.y - pointy) / 512.0)*(lookx - youx);
			j = youy + sin((point.y - pointy) / 512.0)*upy + cos((point.y - pointy) / 512.0)*(looky - youy);
			k = youz + sin((point.y - pointy) / 512.0)*upz + cos((point.y - pointy) / 512.0)*(lookz - youz);
			ii = cos((point.y - pointy) / 512.0)*(upx)-sin((point.y - pointy) / 512.0)*(lookx - youx);
			jj = cos((point.y - pointy) / 512.0)*(upy)-sin((point.y - pointy) / 512.0)*(looky - youy);
			kk = cos((point.y - pointy) / 512.0)*(upz)-sin((point.y - pointy) / 512.0)*(lookz - youz);
			upx = ii;
			upy = jj;
			upz = kk;
			lookx = i;
			looky = j;
			lookz = k;

			review();
		}
		if (point.x != pointx)
		{

			i = youx + sin((pointx - point.x) / 512.0)*(looky - youy) + cos((pointx - point.x) / 512.0)*(lookx - youx);
			j = youy - sin((pointx - point.x) / 512.0)*(lookx - youx) + cos((pointx - point.x) / 512.0)*(looky - youy);
			ii = sin((pointx - point.x) / 512.0)*(upy)+cos((pointx - point.x) / 512.0)*(upx);
			jj = -sin((pointx - point.x) / 512.0)*(upx)+cos((pointx - point.x) / 512.0)*(upy);
			lookx = i;
			looky = j;
			upx = ii;
			upy = jj;
			review();

		}
		SetFocus();

	}
	else if (GetKeyState(2) & 0x8000) {
		_cprintf("mouseright down\n");
		if (point.y != pointy)
		{

			youx += upx * (point.y - pointy) / 4;
			youy += upy * (point.y - pointy) / 4;
			youz += upz * (point.y - pointy) / 4;
			lookx += upx * (point.y - pointy) / 4;
			looky += upy * (point.y - pointy) / 4;
			lookz += upz * (point.y - pointy) / 4;

		}
		if (point.x != pointx)
		{
			i = lookx + ((looky - youy)*upz - (lookz - youz)*upy)*(pointx - point.x) / 10;
			j = looky + ((lookz - youz)*upx - (lookx - youx)*upz)*(pointx - point.x) / 10;
			k = lookz + ((lookx - youx)*upy - (looky - youy)*upx)*(pointx - point.x) / 10;
			ii = youx + ((looky - youy)*upz - (lookz - youz)*upy)*(pointx - point.x) / 10;
			jj = youy + ((lookz - youz)*upx - (lookx - youx)*upz)*(pointx - point.x) / 10;
			kk = youz + ((lookx - youx)*upy - (looky - youy)*upx)*(pointx - point.x) / 10;
			lookx = i;
			looky = j;
			lookz = k;
			youx = ii;
			youy = jj;
			youz = kk;

		}
		review();
	}
	pointx = point.x;
	pointy = point.y;
	////_cprintf("%d,%d\n", point.x, point.y);
	CView::OnMouseMove(nFlags, point);
}


void COPENGLMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
}


void COPENGLMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz, lookx - youx, looky - youy, lookz - youz, upx, upy, upz);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnLButtonUp(nFlags, point);
}
/**/
//void COPENGLMFCView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{//_cprintf("haha");
//  // 此功能要求 Windows Vista 或更高版本。
//  // _WIN32_WINNT 符号必须 >= 0x0600。
//  // TODO: 在此添加消息处理程序代码和/或调用默认值
//  double i, j, k;
//  i = lookx +zDelta*(youx-lookx);
//  j = looky +zDelta*(youy-looky);
//  k = lookz +zDelta*(youz-lookz);
//  youx += zDelta*(youx-lookx);
//  youy += zDelta*(youy-looky);
//  youz += zDelta*(youz-lookz);
//  lookx = i;
//  looky = j;
//  lookz = k;
//  CView::OnMouseHWheel(nFlags, zDelta, pt);
//}
BOOL COPENGLMFCView::PreTranslateMessage(MSG* pMsg)

{
	if (pMsg->message == WM_MOUSEWHEEL)  //判断是否有按键按下     
		_cprintf("mousewheel roll\n");

	{
		int n = (short)HIWORD(pMsg->wParam);
		double i, j, k;
		i = lookx - n * (youx - lookx) / 16;
		j = looky - n * (youy - looky) / 16;
		k = lookz - n * (youz - lookz) / 16;
		youx -= n * (youx - lookx) / 16;
		youy -= n * (youy - looky) / 16;
		youz -= n * (youz - lookz) / 16;
		lookx = i;
		looky = j;
		lookz = k;
		review();


	}
	return false;

}


void COPENGLMFCView::createcubee()
{

	//CCreate CreateCubeeee;
	//CreateCubeeee.OnEnChangeEdit1();
	//CreateCubeeee.OnEnChangeEdit2();
	//CreateCubeeee.OnEnChangeEdit3();

	float cx = CCreate::ccx;
	float cy = CCreate::ccy;
	float cz = CCreate::ccz;
	if ((cx != lyjx || cy != lyjy || cz != lyjz ) && (cx != 0 || cy != 0 || cz != 0))
	{
		//_cprintf("kajskldfja;sddnfp");
	item[itemnum][0] = 1;
	item[itemnum][1] = cx*4;
	item[itemnum][2] = cy*4;
	item[itemnum][3] = cz*4;
	item[itemnum][4] = 1;
	itemnum++;
	lyjx = cx;
	lyjy = cy;
	lyjz = cz;
	//for(int i=0;i<6;i++)
	//_cprintf("%f %f %f %f %f \n", item[i][0], item[i][1], item[i][2], item[i][3], item[i][4] );
	//_cprintf("\n");
	review();
	}



}
int cvAdd4cMat_q(cv::Mat &dst, cv::Mat &scr)
{
	std::vector<cv::Mat>scr_channels;
	std::vector<cv::Mat>dstt_channels;
	split(scr, scr_channels);
	split(dst, dstt_channels);
	CV_Assert(scr_channels.size() == 4 && dstt_channels.size() == 3);
	for (int i = 0; i < 3; i++)
	{
		dstt_channels[i] = dstt_channels[i].mul(255.0 - scr_channels[3], 1 / 255.0);
		dstt_channels[i] += scr_channels[i].mul(scr_channels[3], 1 / 255.0);
	}
	merge(dstt_channels, dst);
	return true;
}


void COPENGLMFCView::OnVideoo()
{

	Mat lamp = imread("lamp.png",-1);
	Mat cube = imread("cube.png",-1);
	Mat sphere = imread("sphere.png",-1);
	int mode = -1;
	bool debounce = false;
	int count = 0, cou = 0, checkdebounce = 0;
	int* fdb = NULL;
	double videox, videoz;
	double videoy = 100;
	double vidxx, vidyy, vidzz;
	prevideo[0] = prevideo[1] = prevideo[2] = 0;
	float alpha;
	VideoCapture cap(0);
	namedWindow("调用摄像头", 1);
	setMouseCallback("调用摄像头", onMousecv);
	cvwindow = true;


	cap >> frame;








	while (cvwindow)
	{

		cap >> frame;
		cv::flip(frame, frame2, 1);
		/*
		frame2.create(frame.size(), frame.type());
		for (int i = 0; i < frame.rows; i++)
			for (int j = 0; j < frame.cols; j++)
			{
				frame2.at<Vec3b>(i, frame.cols - 1 - j)(0) = frame.at<Vec3b>(i, j)(0);
				frame2.at<Vec3b>(i, frame.cols - 1 - j)(1) = frame.at<Vec3b>(i, j)(1);
				frame2.at<Vec3b>(i, frame.cols - 1 - j)(2) = frame.at<Vec3b>(i, j)(2);
				findarea[i][j] = -1;
			}*/
		fdb = findblue();
		////_cprintf("%d\n",fdb);
		if (fdb[2] > 0)
		{
			videoy = -10000.0 / sqrt(fdb[2]) + 100.0;
			videox = -(fdb[0] - frame2.cols / 2.0) / frame.cols*(videoy + 20);
			videoz = 10 + (fdb[1] - frame2.rows / 2.0) / frame2.rows* (videoy + 20);
			vidyy = sqrt(fdb[2]);
			vidxx = (fdb[0] - frame2.cols / 2.0) / frame.cols * 100;
			vidzz = -(fdb[1] - frame2.rows / 2.0) / frame2.rows * 100;
			videoyy = (looky - youy)*vidyy + ((lookz - youz)*upx - (lookx - youx)*upz)*vidxx + upy * vidzz + youy;
			videoxx = (lookx - youx)*vidyy + ((looky - youy)*upz - (lookz - youz)*upy)*vidxx + upx * vidzz + youx;
			videozz = (lookz - youz)*vidyy + ((lookx - youx)*upy - (looky - youy)*upx)*vidxx + upz * vidzz + youz;
			////_cprintf("x=%f,y=%f,z=%f\n", videoxx, videoyy, videozz);
			////_cprintf("(%f,%f,%f),lookat(%f,%f,%f),up(%f,%f,%f)\n", youx, youy, youz,lookx-youx,looky-youy,lookz-youz,upx,upy,upz);
			if ((prevideo[1] - videoy)*(prevideo[1] - videoy) + (prevideo[0] - videox)*(prevideo[0] - videox) + (prevideo[2] - videoz)*(prevideo[2] - videoz) > 20.0f)
			{


				prevideo[0] = videox;
				prevideo[1] = videoy;
				prevideo[2] = videoz;
				debounce = false;
				checkdebounce = 0;
			}


			else if (!debounce)
			{
				prevideo[0] = videox;
				prevideo[1] = videoy;
				prevideo[2] = videoz;

				checkdebounce++;
				if (checkdebounce > 2)
					debounce = true;
			}
			switch (nowmode)
			{
			case -3:
			{
				item[selectt][1] = videoxx;
				item[selectt][2] = videoyy;
				item[selectt][3] = videozz;
			}
			break;
			case -2:                          //视角
			{
				float len = sqrt((videoxx - youx)*(videoxx - youx) + (videoyy - youy)*(videoyy - youy) + (videozz - youz)*(videozz - youz));
				lookix = (youx*(len - 1) + videoxx) / len;
				lookiy = (youy*(len - 1) + videoyy) / len;
				lookiz = (youz*(len - 1) + videozz) / len;
				float le = sqrt((lookix - youx)*(lookix - youx) + (lookiy - youy)*(lookiy - youy));
				upix = (lookix - youx)*(lookiz - youz) / le;
				upiy = (lookiy - youy)*(lookiz - youz) / le;
				upiz = le;

				////_cprintf("lookix,lookiy,liz,%f %f %f %f %f %f\n",lookix-youx,lookiy-youy,lookiz-youz,upix,upiy,upiz);

			}
			break;
			case -1:
				break;//无动作
			case 0:
				lookx += prevideo[0] - youx;
				looky += prevideo[1] - youy;
				lookz += prevideo[2] - youz;
				youy = prevideo[1];
				youx = prevideo[0];
				youz = prevideo[2];
				break;
			case 1:
				item[itemnum - 1][1] = videoxx;
				item[itemnum - 1][2] = videoyy;
				item[itemnum - 1][3] = videozz;
				item[itemnum - 1][4] = 1;
				////_cprintf("pos %f %f %f,%d/n", videox, videoy, videoz,itemnum);
				break;
			case 2:
				li[linum - 1][0] = videoxx;
				li[linum - 1][1] = videoyy;
				li[linum - 1][2] = videozz;
				li[linum - 1][3] = 2;
				item[itemnum - 1][1] = videoxx;
				item[itemnum - 1][2] = videoyy;
				item[itemnum - 1][3] = videozz;
				break;
			case 3:
				item[itemnum - 1][1] = videoxx;
				item[itemnum - 1][2] = videoyy;
				item[itemnum - 1][3] = videozz;
				item[itemnum - 1][4] = 2;
				break;
			case 4:
				item[itemnum - 1][1] = videoxx;
				item[itemnum - 1][2] = videoyy;
				item[itemnum - 1][3] = videozz;
				break;

			}
			review();


		}
		else
		{
			videoy = 100;
		}
		imageROI = frame2(Rect(0, 0, 120, 120));
		cvAdd4cMat_q(imageROI, cube);
		imageROI = frame2(Rect(0, 120, 120, 120));
		cvAdd4cMat_q(imageROI, lamp);
		imageROI = frame2(Rect(0, 240, 120, 120));
		cvAdd4cMat_q(imageROI, sphere);
		/*
		for (int i = 0; i<480; i++)
			for (int j = 0; j < 120; j++)
			{
				if (i < 120 && j<360)
				{
					alpha = cube.ptr<uchar>(i)[j * 4 + 3] / 256.0;
					////_cprintf("alpha%f\n",alpha);
					if (alpha != 0) //4通道图像的alpha判断
					{
						frame2.at<Vec3b>(i, j)(0) = (1 - alpha)*frame2.at<Vec3b>(i, j)(0) + (alpha)*cube.ptr<uchar>(i)[j * 4 + 0];
						frame2.at<Vec3b>(i, j)(1) = (1 - alpha)*frame2.at<Vec3b>(i, j)(1) + (alpha)*cube.ptr<uchar>(i)[j * 4 + 1];
						frame2.at<Vec3b>(i, j)(2) = (1 - alpha)*frame2.at<Vec3b>(i, j)(2) + (alpha)*cube.ptr<uchar>(i)[j * 4 + 2];
					}
				}
				else if (i < 240)
				{
					alpha = lamp.ptr<uchar>(i - 120)[j * 4 + 3] / 256.0;
					////_cprintf("alpha%f\n",alpha);
					if (alpha != 0) //4通道图像的alpha判断
					{
						frame2.at<Vec3b>(i, j)(0) = (1 - alpha)*frame2.at<Vec3b>(i, j)(0) + (alpha)*lamp.ptr<uchar>(i - 120)[j * 4 + 0];
						frame2.at<Vec3b>(i, j)(1) = (1 - alpha)*frame2.at<Vec3b>(i, j)(1) + (alpha)*lamp.ptr<uchar>(i - 120)[j * 4 + 1];
						frame2.at<Vec3b>(i, j)(2) = (1 - alpha)*frame2.at<Vec3b>(i, j)(2) + (alpha)*lamp.ptr<uchar>(i - 120)[j * 4 + 2];
					}

				}
				else if (i < 360)
				{
					alpha = sphere.ptr<uchar>(i - 240)[j * 4 + 3] / 256.0;
					////_cprintf("alpha%f\n",alpha);
					if (alpha != 0) //4通道图像的alpha判断
					{
						frame2.at<Vec3b>(i, j)(0) = (1 - alpha)*frame2.at<Vec3b>(i, j)(0) + (alpha)*sphere.ptr<uchar>(i - 240)[j * 4 + 0];
						frame2.at<Vec3b>(i, j)(1) = (1 - alpha)*frame2.at<Vec3b>(i, j)(1) + (alpha)*sphere.ptr<uchar>(i - 240)[j * 4 + 1];
						frame2.at<Vec3b>(i, j)(2) = (1 - alpha)*frame2.at<Vec3b>(i, j)(2) + (alpha)*sphere.ptr<uchar>(i - 240)[j * 4 + 2];
					}
				}
			}*/
		imshow("调用摄像头", frame2);
		mode = waitKey(1);
		cvwindow = (mode != 27) && cvwindow;
		if (mode == 77 || mode == 109)
			iii = !iii;
		if (mode == 78 || mode == 110) 
			iiii = !iiii;
			
		if (mode == 32)
		{
			if (fdb[0] < 120 && nowmode == -1)
			{
				itemnum++;
				nowmode = 1 + fdb[1] / 120;
				item[itemnum - 1][0] = nowmode;
				item[itemnum - 1][1] = videoxx;
				item[itemnum - 1][2] = videoyy;
				item[itemnum - 1][3] = videozz;
				if (nowmode == 2)
				{
					item[itemnum - 1][4] = lightnum;
					item[itemnum - 1][5] = linum;
					lightnum++;
					li[linum][0] = videoxx;
					li[linum][1] = videoyy;
					li[linum][2] = videozz;
					li[linum][3] = 1;
					linum++;
				}
				selectt = itemnum - 1;
			}
			else
			{
				if (nowmode == -1 && selectt > -1)
				{
					nowmode = -3;
				}
				else if (nowmode == -3)
				{
					nowmode = -4;
					_cprintf("!!!!!!!!!!!!!!!!!!nowmode:%d\n", nowmode);
				}
				else {
					selectt = -1;
				}
				if (nowmode == -2)
				{

					lookx = lookix;
					looky = lookiy;
					lookz = lookiz;
					upz = upiz;
					upx = upix;
					upy = upiy;
				}
				if (nowmode == -4)
				{
					selectt = -1;
					nowmode = -2;

				}
				nowmode = nowmode == 0 ? -2 : (nowmode == -1 ? 0 : nowmode == -3 ? -3 : -1);
				if (nowmode == -2)
				{

					lookix = lookx;
					lookiy = looky;
					lookiz = lookz;
					upiz = upz;
					upix = upx;
					upiy = upy;
				}
			}
			////_cprintf("%d", nowmode);
		}
		else if (mode == 9)
		{
			if (itemnum>0)
				selectt = (selectt + itemnum - 1) % itemnum;
		}
		else if (mode == 8)
		{
			if (item[selectt][0] == 2)
			{
				li[(int)item[selectt][5]][0] = li[linum - 1][0];
				li[(int)item[selectt][5]][1] = li[linum - 1][1];
				li[(int)item[selectt][5]][2] = li[linum - 1][2];
				linum--;
			}
			for (int i = 0; i<100; i++)
			{

				item[selectt][i] = item[itemnum - 1][i];
			}
			itemnum--;
			selectt = -1;
		}
		else if ((mode == 97 || mode == 65) && nowmode == -1) {
			float i, j, k, ii, jj, kk;
			i = lookx - ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			j = looky - ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			k = lookz - ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			ii = youx - ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			jj = youy - ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			kk = youz - ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			youx = ii;
			youy = jj;
			youz = kk;
			review();
		}
		else if ((mode == 100 || mode == 68) && nowmode == -1) {
			float i, j, k, ii, jj, kk;

			i = lookx + ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			j = looky + ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			k = lookz + ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			ii = youx + ((looky - youy)*upz - (lookz - youz)*upy) * 4;
			jj = youy + ((lookz - youz)*upx - (lookx - youx)*upz) * 4;
			kk = youz + ((lookx - youx)*upy - (looky - youy)*upx) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			youx = ii;
			youy = jj;
			youz = kk;
			review();
		}
		else if ((mode == 69 || mode == 101) && nowmode == -1)
		{

			youx -= upx * 2;
			youy -= upy * 2;
			youz -= upz * 2;
			lookx -= upx * 2;
			looky -= upy * 2;
			lookz -= upz * 2;
			review();
		}
		else if ((mode == 81 || mode == 113) && nowmode == -1)
		{

			youx += upx * 2;
			youy += upy * 2;
			youz += upz * 2;
			lookx += upx * 2;
			looky += upy * 2;
			lookz += upz * 2;
			review();
		}
		else if ((mode == 87 || mode == 119) && nowmode == -1)
		{
			float i, j, k;
			i = lookx * 5 - youx * 4;
			j = looky * 5 - youy * 4;
			k = lookz * 5 - youz * 4;
			youx += (lookx - youx) * 4;
			youy += (looky - youy) * 4;
			youz += (lookz - youz) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			review();
		}
		else if ((mode == 83 || mode == 115) && nowmode == -1)
		{
			float i, j, k;
			i = -lookx * 3 + youx * 4;
			j = -looky * 3 + youy * 4;
			k = -lookz * 3 + youz * 4;
			youx -= (lookx - youx) * 4;
			youy -= (looky - youy) * 4;
			youz -= (lookz - youz) * 4;
			lookx = i;
			looky = j;
			lookz = k;
			review();
		}
	}

	destroyWindow("调用摄像头");
}