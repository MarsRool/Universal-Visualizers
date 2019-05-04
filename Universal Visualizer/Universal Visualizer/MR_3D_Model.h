#pragma once
#include "stdafx.h"
#include "MR_math.h"
#include "3DModel.h"
#include "graph.h"
//��� ������ ��������� ����� �������, ����� �� ������ �� ��������/���������, ��� ��������� ������������� ��������������
//� ���� ������:
//�� �������� ������� ����� ����������, �������������� ��������� ������
//���������� �������� � ��������������� �����������, ����� ���-�� ����� ������������, ��� ���������� �����������, ��� ���������� ����

//Type **element �������� ����� �� �������, ������� ������ ���� ������ � ������������ � ��������� � �����������
//*element �������� ����� �� ��� �������. ��� ������� � ����� ������� ����������� ��������� �������� ��� ���������� ���������

namespace MR
{
	class Edge//MR �����
	{
	private:
		Point3D **Point1, **Point2;
		short int CountIncludingInFaces;///���������� ������, ������� �������� �����. ����������� ��� ������������ ������ �� ����� ������������ ������� ������. ������� ����� 0.
	public:
		Edge();
		Edge(Point3D **Point1_i, Point3D **Point2_i, short int count = 0);
		Edge(const Edge & edgeToCopy);
		~Edge();//������ ����������.

		bool check();
		short int getCountIncludingInFaces() { return CountIncludingInFaces; }
		void getPoints(Point3D **Point1_i, Point3D **Point2_i);
		Vector3D getVector12();
		friend Edge **searchEdge(std::vector<Edge**> Edges, Edge * Edge_key);///������� ����� ������ ����� � ������� �����. � ������ �� ���������� ������ NULL
		friend Point3D * getCommonPointInEdges(std::vector<Edge**> Edges);///����� ����� ����� ���� �����, ���� ����� ����. � ������ �� ���������� ������ NULL

		const bool operator == (const Edge &edge_right);///����� �����, ���� ����� �� ����� (1==1, 2==2 || 1==2, 2==1 ��������������)
		Edge& operator ++ (int);
		Edge& operator -- (int);
		Edge& operator += (int added);
		Edge& operator = (const Edge &edge_right);
	};

	class Face//MR �����
	{///��������� ������������ ������������ �� �����, ��� ��� ��� ����������� ���-�� ������� ������ �����
	private:
		std::vector<Point3D**> Points;///������ ������
		std::vector<Edge**> Edges;///������ �����
		Vector3D *Normal;///�������
		double Area;///�������
		Point3D *CenterOfMass;///����� ����
		bool Flag;///true- ���� ��� ���������� � ����������� ����� �� 3D ������

		void calculateNormal();
		void calculateArea();///���� ���������
		void calculateCenterOfMass();
	public:
		Face();
		Face(std::vector<Edge**> Edges_i);
		Face(const Face & faceToCopy);
		~Face();///��� �������� �����, ����������� ���-�� ������� ������ �����.
		///Face(std::vector<Point3D*> Points_i);//����������, ������ ��� ����� ��� ��� �������� �����, ������� ����������� �����, ����� �����, � ������ ����� ��� ����.

		bool istEdgesInPlane(std::vector<Edge**> Edges_i);///true- ���� ����� ��������� � ����� ���������
		void getEdges(std::vector<Edge**> *Edges_out) { *Edges_out = Edges; }
		void setEdges(std::vector<Edge**> *Edges_in) { Edges = *Edges_in; }
		Vector3D* getNormal() { return Normal; }
		Point3D* getCenterOfMass() { return CenterOfMass; }
		bool check();
		bool flag() { return Flag; }
		void setFlag(bool flag_i) { Flag = flag_i; }
		bool isBoundary();

		const bool operator == (const Face &face_right);///����� �����, ���� ����� �� ����� (1==1, 2==2 || 1==2, 2==1 ��������������)
		Face& operator = (const Face &faceToCopy);
	};

	class Object//MR ������
	{///�������� - ������������ ��������, ����� �������� �� �����
	private:
		std::vector<Point3D**> Points;	/// ����� �������
		std::vector<Edge**> Edges;		/// ����� �������
		std::vector<Face**> Faces;		/// ����� �������
		string StrName;					/// ��� �������

		Point3D *Position;				///������� �������

		///������������� �������
		short int TypeColor;/*��� ��������� �������.
		1 - ������� ������� ������ �������(���������)
			2 - ������� ������� ������ �������(����������)
			3 - ��������� 4 ������� �� dl, dr, ul, ur.
			4 - ��������.*/
		RGB_MR Color;///�����������(����������) ���� �������
		RGB_MR ColorGrad[4];///����������� ���� downleft, downright, upleft, upright colors (�� 0.0 �� 1.0)
		RGB_MR ColorGradLand[7];///��������. �� ������ �����. ������ �� �������� �� ����������� ������ ����.
	public:
		Object();
		///������ ������ ��� �������� ����� ��� �������. �������: ����� ������ ���� ��������� �� ������.
		Object(std::vector<Point3D**> *Points_i, std::vector<Edge**> *Edges_i, std::vector<Face**> *Faces_i, string name = "");//�������� ������� �� ��� ������������������ ��������
		Object(const Object &objectToCopy);
		~Object();
	private:
		void clearData();
	public:
		bool isEmpty();///true- ���� ������ ������
		bool check();///1)�������� �� ������������
		void uniqueElements();///2)���������� ��������� ��� �� �������������
		Object* getObjCleanedBoundaryFaces();///3)������� �� �������� ������� ������, � ������� ���� ���� ��� ����� �������������� ����

	private:
		void selectFaces(Face* face);///�������� ��� ����� � ��� � ��� �������
		void selectFaces(Face* face, std::vector<Face**>* Faces);///�������� ��� ����� � ��� � ��� ������� �� ������� ������
	public:
		std::vector<Object*>* get3DObjects();///4)������� ������� ������ �� �������, ���� �� ��������� � ������ �������. ���� ������ ����, �� �� ������ ����� ����. � ������ ������ ������ NULL

		Point3D* getPos();
		void setPos(Point3D *point_in);

		void drawObject();
	private:
		double counticolor(double a, double b, int c, int k);
	public:
		Object& operator = (const Object &objToCopy);
	};

	class Model//MR ������
	{///������������� - ���������� ������ �� ����� �����������, ���� ��� ���������� ���� ����� - ��������� ������� ������� �� ������
	private:
		std::vector<Object*> Objects;
	public:
		Model();
		Model(const Model *modelToCopy);
		void addFrom3DModel(const t3DModel & Model);///������ ������������� �������������
		void addFromGraph(const graph &Graph);///������ ������������� �������������

		void drawModel();

		///��������� ������ �����
		///add -> check -> unique -> getObjCleanedBoundaryFaces -> get3DObjects
		bool check();
		void uniqueObjects();
		
		MR::Model* getModelTested3DObjects();

	};
}