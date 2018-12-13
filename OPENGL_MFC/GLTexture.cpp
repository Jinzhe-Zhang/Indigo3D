#include "GLTexture.h"
RayLightMap::RayLightMap()
{
	dataBuf= NULL;
	TexIndex = -1;
}

RayLightMap::~RayLightMap(){
}

bool RayLightMap::makeBMP(	int width, int height,
							unsigned char colorR,
							unsigned char colorG,
							unsigned char colorB)
{
	mapWidth	= width;
	mapHeight	= height;

	// ���ٿռ�
	dataBuf = new unsigned char[width*height*4];

	// �����������ռ��ָ��Ϊ�� NULL
	memset(dataBuf, 0, sizeof(void *)*1);

	for(long i=0; i<width*height*4; i+=4){
		dataBuf[i+0] = colorR;
		dataBuf[i+1] = colorG;
		dataBuf[i+2] = colorB;
		dataBuf[i+3] = 255;
	}

	// ���� OpenGL �������
	glGenTextures(1, &TexIndex);

	// ���������� Tex �������
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TexIndex);

	// �����䣬�����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	// ��������
	gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA, 
						width, height,
						GL_RGBA, 
						GL_UNSIGNED_BYTE,
						dataBuf);

	// ע�⣬���ﲻ�����ͷſռ䣬��Ϊ���ǻ���Ҫ������
/*
	// �ͷ��ڴ�ռ�
	if (dataBuf){
		delete[] dataBuf;
		return true;
	}*/

	return false;
}

void RayLightMap::SetPixel(int x, int y,
						   unsigned char R,
						   unsigned char G,
						   unsigned char B)
{
	strColorRGB *pt;
	
	pt = (strColorRGB *) (dataBuf + (x+1)*4 + mapWidth*4*y - 4);

	if((pt->R + R) > 255)
		pt->R = 255;
	else
		pt->R+= R;

	if((pt->G + G) > 255)
		pt->G = 255;
	else
		pt->G+= G;

	if((pt->B + B) > 255)
		pt->B = 255;
	else
		pt->B+= B;

/*
procedure TGLBMP.AddPixel(x,y:integer;r,g,b:byte);
var   pixel : PGLRGBQUAD;
begin
  Pixel := Pointer(Cardinal(rgbBits) + (x+1)*4 + Width*4*y - 4);

  if Pixel^.Red+r>255 then
   Pixel^.Red:=255
  else
  Pixel^.Red:=Pixel^.Red+r;

  if Pixel^.Green+g>255 then
   Pixel^.Green:=255
  else
  Pixel^.Green:=Pixel^.Green+g;

  if Pixel^.Blue+b>255 then
   Pixel^.Blue:=255
  else
  Pixel^.Blue:=Pixel^.Blue+b;

end;
*/
}

int RayLightMap::getcolor(int x,int y,int c)
{
	strColorRGB *ptt;

	ptt = (strColorRGB *)dataBuf;
	return c == 0 ? ptt->R : c == 1 ? ptt->G : ptt->B;
	/*
	procedure TGLBMP.AddPixel(x,y:integer;r,g,b:byte);
	var   pixel : PGLRGBQUAD;
	begin
	Pixel := Pointer(Cardinal(rgbBits) + (x+1)*4 + Width*4*y - 4);

	if Pixel^.Red+r>255 then
	Pixel^.Red:=255
	else
	Pixel^.Red:=Pixel^.Red+r;

	if Pixel^.Green+g>255 then
	Pixel^.Green:=255
	else
	Pixel^.Green:=Pixel^.Green+g;

	if Pixel^.Blue+b>255 then
	Pixel^.Blue:=255
	else
	Pixel^.Blue:=Pixel^.Blue+b;

	end;
	*/
}
bool RayLightMap::UpdateTextrue()
{
	if(TexIndex == -1) return false;

	// ɾ��ԭ���������
	glDeleteTextures(1, &TexIndex);

	TexIndex = -1;

	// ���� OpenGL �������
	glGenTextures(1, &TexIndex);

	// ���������� Tex �������
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TexIndex);

	// �����䣬�����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	// ��������
	gluBuild2DMipmaps(	GL_TEXTURE_2D, GL_RGBA, 
						mapWidth, mapHeight,
						GL_RGBA, 
						GL_UNSIGNED_BYTE,
						dataBuf);

	return true;
}





bool LoadBMP(char* filename, GLuint *Tex)
{
	// �ļ� ��֤
	if (!filename) return false;
	FILE *pf=NULL;
	fopen_s(&pf,filename,"r");
    if (!pf){ 
		MessageBoxA(NULL, "�Ҳ��������ļ���", "�����������", MB_OK);
		return false;
	}

	fclose(pf);

	// ����һ�����������[�ڴ�ռ�]
	AUX_RGBImageRec *TextureImage[1];

	// �����������ռ��ָ��Ϊ�� NULL
	memset(TextureImage,0,sizeof(void *)*1);

	// ����һ������BMP�ļ���[�ڴ�ռ�]������ָ��־��[�ڴ�ռ�]
	//TextureImage[0] = auxDIBImageLoad(filename);

	// �õ�����Ĵ�С
	int width	= TextureImage[0]->sizeX;
	int height	= TextureImage[0]->sizeY;

	// ���� OpenGL �������
	glGenTextures(1, Tex);

	// ���������� Tex �������
	glBindTexture(GL_TEXTURE_2D, *Tex);

	// ������ Use mipmapping filter
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	// Generate the mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

	// �ͷ��ڴ�ռ�
	if (TextureImage[0]){
		if (TextureImage[0]->data){
			free(TextureImage[0]->data);
				return true;
		}
		free(TextureImage[0]);
	}
	return false;
}
