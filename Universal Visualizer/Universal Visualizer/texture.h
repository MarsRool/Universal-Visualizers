#pragma once
#include "data/IL/il.h"
#include "data/IL/ilu.h"
#include "data/GL_my/freeglut.h"
#include "data/GL_my/glaux.h"

class TextureImage
{
public:
    GLubyte *imageData;     // Данные текстуры
    GLuint  bpp;            // Байт на пиксел
    GLuint  width,height;   // Высота и ширина
	GLuint  texID;          // ID текстуры
};

class CTexture{
public:

    TextureImage image;
	bool loaded;

	void LoadTexture(char *filename, TextureImage &texture, bool &loaded);
    void FreeTexture(TextureImage &texture);
};