

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glext.h>

#pragma comment( lib, "opengl32.lib")
#pragma comment( lib, "glu32.lib")
#pragma comment( lib, "glaux.lib")
///////////////////////////////////////



#ifndef	__GLTEXTURE_H__
#define	__GLTEXTURE_H__





struct strColorRGB{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

class RayLightMap{

public :
	RayLightMap();
	~RayLightMap();
	
	int mapWidth;
	int mapHeight;

	unsigned int TexIndex;

//	bool LoadedTextrue;

	// …Ë÷√Õº∆¨ª∫≥Â«¯÷∏’Î
	unsigned char	*dataBuf;

	bool makeBMP(int width, int height,
				 unsigned char colorR,unsigned char colorG, unsigned char colorB);

	void SetPixel(	int x, int y,
					unsigned char R, unsigned char G, unsigned char B);

	int getcolor(int x,int y,int c);

	bool UpdateTextrue();
};

bool LoadBMP(char* filename, GLuint *Tex);


#endif //__GLTEXTURE_H__

