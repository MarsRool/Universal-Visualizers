#include "stdafx.h"
#include "conversions.h"
#include "MR_Model.h"

MR::Model::Model::Model()
{
}

MR::Model::Model::Model(const Model &modelToCopy, bool fullCopy)
{
	for (Object *o : modelToCopy.Objects)
		Objects.push_back( (fullCopy ? new Object(*o) : o));
}

void MR::Model::Model::addFrom3DModel(const t3DModel & Model)
{	
	/*std::list<Edge*> test;
	test.push_back(new Edge(new Point3D(-46.658493, -45.805752, 47.203850), new Point3D(46.197060, - 45.805752, 47.203850)));
	test.push_back(new Edge(new Point3D(46.197060, -45.805752, 47.203850), new Point3D(-46.658493, - 45.805752, 47.203850)));
	test.unique(equalEdges);*/
	//сначала создаем три массива: точек, ребер и граней
	std::vector<Geometry::Point3D*> Points_v;
	std::vector<Edge*> Edges_v;
	std::vector<Face*> Faces_v;
	
	std::list<Geometry::Point3D*> Points;
	std::list<Edge*> Edges;
	std::list<Face*> Faces;

	bool isto;							//загружена ли модель

	int  numVerts;						// Число вершин в модели
	//int  numTexVertex;				// Число текстурных координат

	//int  numTex;						// Число текстур
	//vector<tMaterialInfo> Textures;	//Описание каждой текстуры
	//bool bHasTexture;					// TRUE если есть текстурная карта для этого обьекта

	vector<CV3>   pVerts;				// Массив вершин обьекта
	//vector<CV2>   pTexVerts;			// Текстурные координаты

	int numOfObjects;					// Число обьектов в модели
	vector<t3DObject> Objects;			// Полигоны обьекта
	Model.Return_Data(isto, numVerts, pVerts, numOfObjects, Objects);

	if (isto)
	{
		list<Edge*> edges_i;
		Edge* edge_j;
		Geometry::Point3D* points_j[3];
		for (unsigned int l = 1; l < Objects.size(); l++)
		{
			Edges_v.clear();
			Faces_v.clear();
			Points_v.clear();
			for (unsigned int i = 1; i < pVerts.size(); i++)//заполнение точек
				Points_v.push_back(new Geometry::Point3D(pVerts[i].x, pVerts[i].y, pVerts[i].z));
			for (unsigned int i = 1; i < Objects[l].pFaces.size(); i++)//для каждой грани:
			{
				for (int j = 0; j < 3; j++)
				{
					if (Objects[l].pFaces[i].vi[j] - 1 < static_cast<int>(Points_v.size()))
						points_j[j] = Points_v.at(Objects[l].pFaces[i].vi[j] - 1);
					else
						points_j[j] = nullptr;
				}

				edges_i.clear();
				for (int j = 0; j < 3; j++)
				{
					edge_j = new Edge(points_j[j], points_j[(j + 1) % 3]);
					edges_i.push_back(edge_j);
					Edges_v.push_back(edge_j);
				}
				Faces_v.push_back(new Face(edges_i));
			}

			for (Geometry::Point3D *p : Points_v)
				Points.push_back(p);
			for (Edge *e : Edges_v)
				Edges.push_back(e);
			for (Face *f : Faces_v)
				Faces.push_back(f);
			this->Objects.push_back(new Object(Points, Edges, Faces, Objects[l].strName));
			for (Geometry::Point3D *p : Points_v)
				delete p;
			for (Edge *e : Edges_v)
				delete e;
			for (Face *f : Faces_v)
				delete f;
		}
	}
}

void MR::Model::Model::addFromGraph(const graph &Graph)
{
	Object *object();
}

void MR::Model::Model::addObject(const Object & object)
{	
	Objects.push_back(new Object(object));
}

void MR::Model::Model::drawModel()
{
	for (Object* o : Objects)
		o->drawObject();
}
