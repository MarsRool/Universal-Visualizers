#include "stdafx.h"
#include "texture.h"
#include "Form1.h"

/*// �����������
CTexture::CTexture()
{
}
 
// ����������
CTexture::~CTexture()
{
}*/
 
// �������, ��������������� ����������� �������� � ���������� ���������.
// � ������� ���������� ��� �����, ��� ����� � ��������� �� ��������.
void CTexture::LoadTexture(char *filename, TextureImage &textre, bool &loaded)
{
	TextureImage *texture=&textre;
	texture->imageData=0;
	loaded=true;
	/*std::string name=filename;
	for (int i=name.size()-1;i>0;i--)
	{
		if ( name[i] == '.' )
		{
			name[i]=0;
			break;
		}
		name[i]=0;
	}
	filename=name.c_str();*/
    // ������ DevIL ��������� ����

	if (System::IO::File::Exists(ChToStr(filename)))
		ilLoadImage(filename);//��������� � ���� ������: � ����� ������������ ����� � � ����� obj
	else if(System::IO::File::Exists(L"data\\obj\\" + ChToStr(filename)))
		ilLoadImage(StrToCh(L"data\\obj\\" + ChToStr(filename)));
	else
	{
		loaded = false;
		return;
	}

	int err = ilGetError();
	if (err != IL_NO_ERROR)
	{
		/*const char* strError = iluErrorString(err);
		MessageBox(NULL, strError, "������ ��� ��������!", MB_OK);
		exit(1);*/
		loaded = false;
		return;
	}
 
    // �������� ������ ��������
    texture->width = ilGetInteger(IL_IMAGE_WIDTH);          // ������
    texture->height = ilGetInteger(IL_IMAGE_HEIGHT);        // ������
    texture->bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);  // ���� �� �������
 
    // ��������� ������ � ���� ��������
    texture->imageData = ilGetData();
 
	if (texture->imageData[0] == 0)
	{
		loaded = false;
		return;
	}

    ilEnable(IL_CONV_PAL);

    // ��� ������ �����������
    unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);
 
    // ���������� ��������
    glGenTextures(1, &texture->texID);

    // ����������� ������ �������� � ID
    glBindTexture(GL_TEXTURE_2D,texture->texID);

    // ������ ���-����
    gluBuild2DMipmaps(GL_TEXTURE_2D, texture->bpp, texture->width,
        texture->height, type, GL_UNSIGNED_BYTE, texture->imageData);

    // ������������� �������� �������
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
 
void CTexture::FreeTexture(TextureImage &texture)
{
}