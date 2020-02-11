#pragma once
#include "stdafx.h"

#include "texture.h"

using namespace std;

// Структура 3D-точки
struct CV3{
    float x,y,z;
};

// Структура 2D-точки
struct CV2{
    float x,y;
};
// Это структура полигона. Она используется для индексирования массивов координат
// вершин и текстур. Эта информация сообщает нам о том, какие номера вершин в массиве
// какому полигону принадлежат. То же самое касается текстурных координат.
struct tFace
{
    int vi[3];// vertex index
	int ti[3];// texture index
	int ni[3];// normal index
	int Id_tex;// индекс текстуры
	//вершина, индекс
	//нормали это векторы в каждой вершине. т.е. направления от центра до вершины для освещения.
	//!Не являются нормалями полигонаS
};

//структура для текстур
struct TK
{
	float rgb[3];//цвет RGB
	bool ist;//существует ли этот цвет
	//string  strFile;//имя файла
	bool fileist;//существует ли этот файл
	CTexture texture;//загруженная текстура
};

// Эта структура хранит информацию о материале. Это может быть текстурная карта света.
struct tMaterialInfo
{
    string  strName;			// Имя текстуры
    int   texureId;             // ID текстуры

    TK Ka; // ambient
	TK Kd; // diffuse
	TK Ks; // specular (не используется)
	TK Ke; // цвет (не используется)

	float Ni; //не используется. для оптической плотности
	float Ns; //не используется. для зеркального показателя от 0 до 100
	float d; //прозрачность от 0 до 1 (не используется)
	int illum;//огни? (не используется)
};

// Содержит всю информацию об объекте.
struct t3DObject
{
	vector<tFace> pFaces;       // Полигоны обьекта
	int  numFaces;              // Число полигонов объекта
	string strName;             // Имя обьекта
};

class t3DModel
{
private:
	bool isto;					//загружена ли модель

	int  numVerts;              // Число вершин в модели
    int  numTexVertex;          // Число текстурных координат
	int  numNormals;            // Число нормалей

	int  numTex;				// Число текстур
	vector<tMaterialInfo> Textures;  //Описание каждой текстуры
	bool bHasTexture;           // TRUE если есть текстурная карта для этого обьекта
	
	vector<CV3>   pVerts;		// Массив вершин обьекта
    vector<CV2>   pTexVerts;    // Текстурные координаты
	vector<CV3>   pNormals;     // Нормали обьекта

	int numOfObjects;           // Число обьектов в модели
    vector<t3DObject> Objects;  // Полигоны обьекта
public:
	//инициализация модели
	t3DModel();

	//загрузка модели
	void loadModel(const char * path);

	//вывод объекта
	void DrawObj(int posx, int posy, int posz);

	//напечатать объекты модели. n - количество полигонов в каждой модели
	void Print_Objects(int n);

	// set/get
	//возвратить, загружена ли модель
	bool GetLoadedModel();

	//вернуть данные
	void Return_Data(bool &isto_out,
		int &numVerts_out, vector<CV3> &pVerts_out,
		int &numOfObjects_out, vector<t3DObject> &Objects_out) const;
private:
	//инициализация материалов модели
	void InitMaterial(tMaterialInfo &mat);
	//загрузка материалов модели
	void LoadMaterial(const char * path);
	//напечатать полигоны объекта модели
	void Print_Obj_Faces(const t3DObject &obj, int n);
};

extern std::vector<t3DModel> MODELS_3D;