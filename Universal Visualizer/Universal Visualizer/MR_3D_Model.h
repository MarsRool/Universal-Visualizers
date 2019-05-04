#pragma once
#include "stdafx.h"
#include "MR_math.h"
#include "3DModel.h"
#include "graph.h"
//все классы построены таким образом, чтобы на момент их создания/изменения, все параметры автоматически рассчитывались
//в этом случае:
//не придется вводить новые переменные, контролирующие состояния класса
//исключатся ситуации с неопределенными состояниями, когда что-то будет неопределено, или определено неправильно, или устаревшая инфа

//Type **element содержит адрес на элемент, который должен быть создан в конструкторе и уничтожен в деструкторе
//*element содержит адрес на сам элемент. это создано с целью создать возможность управлять адресами при унификации элементов

namespace MR
{
	class Edge//MR ребро
	{
	private:
		Point3D **Point1, **Point2;
		short int CountIncludingInFaces;///количество граней, которые содержат ребро. добавляется при формировании модели на этапе формирования массива граней. Сначала равна 0.
	public:
		Edge();
		Edge(Point3D **Point1_i, Point3D **Point2_i, short int count = 0);
		Edge(const Edge & edgeToCopy);
		~Edge();//пустой деструктор.

		bool check();
		short int getCountIncludingInFaces() { return CountIncludingInFaces; }
		void getPoints(Point3D **Point1_i, Point3D **Point2_i);
		Vector3D getVector12();
		friend Edge **searchEdge(std::vector<Edge**> Edges, Edge * Edge_key);///находит адрес адреса ребра в массиве ребер. В случае не нахождения вернет NULL
		friend Point3D * getCommonPointInEdges(std::vector<Edge**> Edges);///найти общую точку всех ребер, если такая есть. В случае не нахождения вернет NULL

		const bool operator == (const Edge &edge_right);///ребра равны, если равны их точки (1==1, 2==2 || 1==2, 2==1 соответственно)
		Edge& operator ++ (int);
		Edge& operator -- (int);
		Edge& operator += (int added);
		Edge& operator = (const Edge &edge_right);
	};

	class Face//MR грань
	{///осторожно использовать конструкторы из ребер, так как это увеличивает кол-во смежных граней ребер
	private:
		std::vector<Point3D**> Points;///массив вершин
		std::vector<Edge**> Edges;///массив ребер
		Vector3D *Normal;///нормаль
		double Area;///площадь
		Point3D *CenterOfMass;///центр масс
		bool Flag;///true- если уже участвовал в рекурсивном тесте на 3D модель

		void calculateNormal();
		void calculateArea();///надо вычислить
		void calculateCenterOfMass();
	public:
		Face();
		Face(std::vector<Edge**> Edges_i);
		Face(const Face & faceToCopy);
		~Face();///при удалении грани, уменьшается кол-во смежных граней ребер.
		///Face(std::vector<Point3D*> Points_i);//недоступно, потому что перед тем как добавить грань, сначала добавляются точки, потом ребра, а значит ребра уже есть.

		bool istEdgesInPlane(std::vector<Edge**> Edges_i);///true- если ребра находятся в одной плоскости
		void getEdges(std::vector<Edge**> *Edges_out) { *Edges_out = Edges; }
		void setEdges(std::vector<Edge**> *Edges_in) { Edges = *Edges_in; }
		Vector3D* getNormal() { return Normal; }
		Point3D* getCenterOfMass() { return CenterOfMass; }
		bool check();
		bool flag() { return Flag; }
		void setFlag(bool flag_i) { Flag = flag_i; }
		bool isBoundary();

		const bool operator == (const Face &face_right);///ребра равны, если равны их точки (1==1, 2==2 || 1==2, 2==1 соответственно)
		Face& operator = (const Face &faceToCopy);
	};

	class Object//MR объект
	{///алгоритм - формирование объектов, потом проверка на дубли
	private:
		std::vector<Point3D**> Points;	/// Точки объекта
		std::vector<Edge**> Edges;		/// Ребра объекта
		std::vector<Face**> Faces;		/// Грани объекта
		string StrName;					/// Имя обьекта

		Point3D *Position;				///позиция объекта

		///раскрашивание объекта
		short int TypeColor;/*тип раскраски функции.
		1 - разными цветами каждую функцию(монотонно)
			2 - разными цветами каждую функцию(градиентно)
			3 - раскраска 4 цветами от dl, dr, ul, ur.
			4 - ландшафт.*/
		RGB_MR Color;///стандартный(монотонный) цвет функции
		RGB_MR ColorGrad[4];///градиентный цвет downleft, downright, upleft, upright colors (от 0.0 до 1.0)
		RGB_MR ColorGradLand[7];///ландшафт. по второй схеме. радуга от красного до фиолетового сверху вниз.
	public:
		Object();
		///нельзя просто так добавить любые три массива. условие: ребра должны быть построены на гранях.
		Object(std::vector<Point3D**> *Points_i, std::vector<Edge**> *Edges_i, std::vector<Face**> *Faces_i, string name = "");//создание объекта из уже инициализированных массивов
		Object(const Object &objectToCopy);
		~Object();
	private:
		void clearData();
	public:
		bool isEmpty();///true- если пустой объект
		bool check();///1)проверка на корректность
		void uniqueElements();///2)унификация элементов для их однозначности
		Object* getObjCleanedBoundaryFaces();///3)вернуть из текущего объекта объект, в котором есть одно или более геометрическое тело

	private:
		void selectFaces(Face* face);///выделить эту грань и все с ней смежные
		void selectFaces(Face* face, std::vector<Face**>* Faces);///выделить эту грань и все с ней смежные из массива граней
	public:
		std::vector<Object*>* get3DObjects();///4)разбить текущий объект на объекты, если их несколько в данном объекте. Если объект один, то он вернет копию себя. В случае ошибки вернет NULL

		Point3D* getPos();
		void setPos(Point3D *point_in);

		void drawObject();
	private:
		double counticolor(double a, double b, int c, int k);
	public:
		Object& operator = (const Object &objToCopy);
	};

	class Model//MR модель
	{///интерпретация - добавление граней по линии пересечения, если они пересекают друг друга - дробление каждого объекта на модели
	private:
		std::vector<Object*> Objects;
	public:
		Model();
		Model(const Model *modelToCopy);
		void addFrom3DModel(const t3DModel & Model);///только эквивалентная интерпретация
		void addFromGraph(const graph &Graph);///только эквивалентная интерпретация

		void drawModel();

		///процедура общего теста
		///add -> check -> unique -> getObjCleanedBoundaryFaces -> get3DObjects
		bool check();
		void uniqueObjects();
		
		MR::Model* getModelTested3DObjects();

	};
}