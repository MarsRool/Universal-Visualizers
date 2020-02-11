#pragma once
#include "stdafx.h"
#include "MR_Vector3D.h"
#include "3DModel.h"
#include "MR_Edge.h"
#include "graph.h"
//��� ������ ��������� ����� �������, ����� �� ������ �� ��������/���������, ��� ��������� ������������� ��������������
//� ���� ������:
//�� �������� ������� ����� ����������, �������������� ��������� ������
//���������� �������� � ��������������� �����������, ����� ���-�� ����� ������������, ��� ���������� �����������, ��� ���������� ����

//Type **element �������� ����� �� �������, ������� ������ ���� ������ � ������������ � ��������� � �����������
//*element �������� ����� �� ��� �������. ��� ������� � ����� ������� ����������� ��������� �������� ��� ���������� ���������

namespace MR
{
	namespace Model
	{
		///MR �����
		///��������� ������������ ������������ �� �����, ��� ��� ��� ����������� ���-�� ������� ������ �����
		class Face
		{
		public:
			Face(const std::list<Edge*> &Edges_i);
			///<summary>
			///������� �������� ����� �����
			///</summary>
			Face(const Face & faceToCopy);
			///<summary>
			///��� �������� �����, ����������� ���-�� ������� ������ �����.
			///</summary>
			~Face();
			//Face(std::vector<Point3D*> Points_i);//����������, ������ ��� ����� ��� ��� �������� �����, ������� ����������� �����, ����� �����, � ������ ����� ��� ����.
			
			///<summary>
			///true- ���� ����� ��������� � ����� ���������
			///</summary>
			static bool istEdgesInPlane(const std::list<Edge*> &Edges_i);
			void getEdges(std::list<Edge*> &Edges_out) const { Edges_out = Edges; }
			void setEdges(const std::list<Edge*> &Edges_in) { Edges = Edges_in; }
			void getPoints(std::list<Geometry::Point3DCartesian*> &Points_out) const { Points_out = Points; }
			void setEdges(const std::list<Geometry::Point3DCartesian*> &Points_in) { Points = Points_in; }
			const Geometry::Vector3D &getNormal() const { return Normal; }
			const Geometry::Point3DCartesian &getCenterOfMass() { return CenterOfMass; }
			void getPointsPath(std::list<MR::Geometry::Point3DCartesian*> &points) const;

			bool flag() const { return Flag; }
			void setFlag(bool flag_i) { Flag = flag_i; }
			bool isBoundary();

			///<summary>
			///����� �����, ���� ����� �� ����� (1==1, 2==2 || 1==2, 2==1 ��������������)
			///</summary>
			friend bool equalFaces(const Face &face_left, const Face &face_right);
			///����� �����, ���� ����� �� ����� (1==1, 2==2 || 1==2, 2==1 ��������������)
			bool operator == (const Face &face_right);
			///<summary>
			///������� �������� ����� �����
			///</summary>
			Face& operator = (const Face &faceToCopy);
		private:
			bool check();

			void CopyNotUnique(const Face &faceToCopy);

			void calculateNormal();
			void calculateArea();//���� ���������
			void calculateCenterOfMass();

			///<summary>
			///������ ������
			///<summary>
			std::list<Geometry::Point3DCartesian*> Points;
			///<summary>
			///������ �����
			///<summary>
			std::list<Edge*> Edges;
			///<summary>
			///�������
			///<summary>
			Geometry::Vector3D Normal = { 0.0, 0.0, 0.0 };
			///<summary>
			///�������
			///<summary>
			double Area = 0;
			///<summary>
			///����� ����
			///<summary>
			Geometry::Point3DCartesian CenterOfMass;
			///<summary>
			///true- ���� ��� ���������� � ����������� ����� �� 3D ������
			///<summary>
			bool Flag = false;
		};
	}
}