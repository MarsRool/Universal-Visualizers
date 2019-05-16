#include "stdafx.h"
#include "global.h"
#include "func.h"
#include "3DModel.h"
using namespace std;

void t3DModel::loadModel(const char * path)
{//путь к файлу, ссылка на объект
	//инициализация объекта

	FILE * file;
	fopen_s(&file, path, "r");
	if( file == NULL )
	{    
		printf("Impossible to open the file !\n");
		isto = false;
		return;
	}

	int path_folder_n;
	char* y = find_folder(path,path_folder_n);
	char lineHeader[128];
	int res;
	long int offset;
	int IDi=0;//текущий ID текстуры
	int Oi=0;//текущий номер объекта, в который загружаются полигоны
	string mati;//имя текстуры
	int j=0;
	//Чтение файла
	CV3 v3={0,0,0};
	CV2 v2={0,0};
	pVerts.push_back(v3);
	pNormals.push_back(v3);
	pTexVerts.push_back(v2);
	t3DObject Objecti;
	Objects.push_back(Objecti);
	while( 1 ){
		j++;
		if(j==15)
		{
			j=j;
		}
		lineHeader[0]=0;
		res=0;
		offset=0;
		// читаем первый символ в файле
		res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF)
		   break; // EOF = Конец файла. Заканчиваем цикл чтения
		// else : парсим строку
	
		//v Сначала обработаем вершины:
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			CV3 vertex;//текущая точка
			numVerts++;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			pVerts.push_back(vertex);
		}
	
		//vt координаты текстур
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			CV2 uv;//текущие координаты текстуры
			numTexVertex++;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y );
			pTexVerts.push_back(uv);
		}

	   //vn нормали
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			numNormals++;
			CV3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			pNormals.push_back(normal);
		}

		else if ( strcmp( lineHeader, "g" ) == 0 )
		{
			t3DObject Objecti;
			Objecti.numFaces=0;
			char x[255];
			int matches = fscanf_s(file, "%s\n", x, sizeof(x));
			if (matches == 1 && x[0]!=0)
			{
				numOfObjects++;
				Objecti.strName=x;
				tFace tf;
				Objecti.pFaces.push_back(tf);
				Objects.push_back(Objecti);
				Oi=numOfObjects;
			}
		}

		//f полигоны
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			Objects[Oi].numFaces++;
			tFace vv;
			char strFace[sostr], ch;
			char *strF = new char[sostr];
			fscanf_s(file, "%[^\n]%c", strFace, sizeof(strFace), &ch, 1);
			for (int i = 0; i < sostr; i++)
				strF[i] = strFace[i];
			for (int i = 0; i < 3; i++)
			{
				vv.vi[i] = findDoubleInStr(strF, 127, &strF);//Вершины
				vv.ti[i] = 0;
				vv.ni[i] = 0;
				if (strF[0] == '/' && strF[1] == '/')//Вершины // Нормали
				{
					vv.ni[i] = findDoubleInStr(strF, 127, &strF);
				}
				else if (strF[0] == '/')
				{
					vv.ti[i] = findDoubleInStr(strF, 127, &strF);//Вершины / Текстурные координаты
					if (strF[0] == '/')
					{
						vv.ni[i] = findDoubleInStr(strF, 127, &strF);//Вершины / Текстурные координаты / Нормали
					}
				}

			}
			/*int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vv.vi[0], &vv.ti[0], &vv.ni[0],
				&vv.vi[1], &vv.ti[1], &vv.ni[1],
				&vv.vi[2], &vv.ti[2], &vv.ni[2]);*/
			vv.Id_tex=IDi;//установка ID текстуры
			Objects[Oi].pFaces.push_back(vv);
			/*if (matches != 9)
			{
				Objects[Oi].numFaces--;
			}*/
		}

		//успользовать такой-то материал
		else if (strcmp( lineHeader, "usemtl" ) == 0)
		{
			bHasTexture = true;
			char x[255];
			res = fscanf_s(file, "%s\n", x, sizeof(x));
			mati=x;
			if (res == 1 && mati!="")
			{
				bool Double=false;//true, если дубль
				int Double_i=0;//i дубля
				for (int i=1;i<=numTex;i++)//проверка на дубли
					if (Textures[i].strName == mati)
					{
						Double = true;//дубль
						Double_i=i;
					}
				
				if ( Double == false )
				{//идентификация текстуры
					/*numTex++;
					tMaterialInfo matii;
					matii.strName=mati;
					matii.texureId=numTex;
					Textures.push_back(matii);
					IDi=numTex;*/
					IDi=-1;
				}
				else
				{
					IDi=Textures[Double_i].texureId;
				}
			}
		}

		//в таком-то файле лежат материалы
		else if (strcmp( lineHeader, "mtllib" ) == 0)
		{
			char x[255];
			res = fscanf_s(file, "%s\n", x, sizeof(x));
			if (res == 1 && x!="" && path_folder_n>0)
			{
				string fold=y;
				string pathi=x;
				string ressi=fold+pathi;
				const char* reschi=ressi.c_str();
				LoadMaterial(reschi);//файл лежит абыгде
			}
			else if (res == 1 && x!="" && path_folder_n<=0)
			{
				LoadMaterial(x);//файл лежит в папке с программой
			}
		}
		//fgets(lineHeader,256,file);
	}
	fclose (file);
	isto = true;
}