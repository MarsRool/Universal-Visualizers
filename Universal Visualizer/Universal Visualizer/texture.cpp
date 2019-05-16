#include "stdafx.h"
#include "texture.h"
#include "Form1.h"

/*// Конструктор
CTexture::CTexture()
{
}
 
// Деструктор
CTexture::~CTexture()
{
}*/
 
// Функция, непосредственно загружающая текстуру в переданную структуру.
// В функцию передается тип файла, имя файла и указатель на текстуру.
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
    // Просим DevIL загрузить файл

	if (System::IO::File::Exists(ChToStr(filename)))
		ilLoadImage(filename);//проверяем в двух местах: в папке исполняемого файла и в папке obj
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
		MessageBox(NULL, strError, "Ошибка при загрузке!", MB_OK);
		exit(1);*/
		loaded = false;
		return;
	}
 
    // Получаем данные текстуры
    texture->width = ilGetInteger(IL_IMAGE_WIDTH);          // Ширина
    texture->height = ilGetInteger(IL_IMAGE_HEIGHT);        // Высота
    texture->bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);  // Байт на пиксель
 
    // Загружаем данные в нашу текстуру
    texture->imageData = ilGetData();
 
	if (texture->imageData[0] == 0)
	{
		loaded = false;
		return;
	}

    ilEnable(IL_CONV_PAL);

    // Тип данных изображения
    unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);
 
    // Генерируем текстуру
    glGenTextures(1, &texture->texID);

    // Привязываем данные текстуры к ID
    glBindTexture(GL_TEXTURE_2D,texture->texID);

    // биндим мип-мапы
    gluBuild2DMipmaps(GL_TEXTURE_2D, texture->bpp, texture->width,
        texture->height, type, GL_UNSIGNED_BYTE, texture->imageData);

    // Устанавливаем качество текстур
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
 
void CTexture::FreeTexture(TextureImage &texture)
{
}