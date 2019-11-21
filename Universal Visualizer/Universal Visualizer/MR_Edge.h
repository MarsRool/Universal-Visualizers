#pragma once
#include "stdafx.h"
#include "MR_Plane3D.h"
#include "3DModel.h"
#include "graph.h"
///��� ������ ��������� ����� �������, ����� �� ������ �� ��������/���������, ��� ��������� ������������� ��������������
///� ���� ������:
///�� �������� ������� ����� ����������, �������������� ��������� ������
///���������� �������� � ��������������� �����������, ����� ���-�� ����� ������������, ��� ���������� �����������, ��� ���������� ����

///Type **element �������� ����� �� �������, ������� ������ ���� ������ � ������������ � ��������� � �����������
///*element �������� ����� �� ��� �������. ��� ������� � ����� ������� ����������� ��������� �������� ��� ���������� ���������

namespace MR
{
	namespace Model
	{
		///<summary>
		///MR �����
		///</summary>
		class Edge
		{
		public:
			Edge(const Geometry::Point3D *Point1_i, const Geometry::Point3D *Point2_i, short int count = 0);
			///<summary>
			///������� �������� ����� �����
			///</summary>
			Edge(const Edge & edgeToCopy);
			~Edge();

			///<summary>
			///true- ���� ���������� ������, ������� �������� �����, ������ 0.
			///</summary>
			bool existing() const;
			short int getCountIncludingInFaces() const { return CountIncludingInFaces; }
			void getPoints(Geometry::Point3D **Point1_i, Geometry::Point3D **Point2_i);
			Geometry::Vector3D getVector12() const;
			///<summary>
			///������� ����� ������ ����� � ������� �����. � ������ �� ���������� ������ nullptr
			///</summary>
			friend Edge *searchEdge(const std::list<Edge*> &Edges, const Edge *Edge_key);
			///<summary>
			///����� ����� ����� ���� �����, ���� ����� ����. � ������ �� ���������� ������ nullptr. �������� �� ������!
			///</summary>
			friend Geometry::Point3D * getCommonPointInEdges(const std::list<Edge*> &Edges);

			///<summary>
			///�������� �� ��������� �� ��������
			///</summary>
			friend bool equalEdges(const Edge *point_left, const Edge *point_right);
			///<summary>
			///����� �����, ���� ����� �� ����� (1==1 && 2==2 || 1==2 && 2==1 ��������������)
			///</summary>
			const bool operator == (const Edge &edge_right) const;
			///<summary>
			///����������� ���-�� ��������� � �����
			///</summary>
			Edge& operator ++ ();
			///<summary>
			///��������� ���-�� ��������� � �����
			///</summary>
			Edge& operator -- ();
			///<summary>
			///����������� ���-�� ��������� � ����� �� added
			///</summary>
			Edge& operator += (short int added);
			///<summary>
			///������� �������� ����� �����
			///</summary>
			Edge& operator = (const Edge &edge_right);
		private:
			bool check() const;

			void CopyNotUnique(const Geometry::Point3D *Point1_i, const Geometry::Point3D *Point2_i, short int count = 0);

			Geometry::Point3D *Point1 = nullptr, *Point2 = nullptr;
			//���������� ������, ������� �������� �����. ����������� ��� ������������ ������ �� ����� ������������ ������� ������. ������� ����� 0.
			short int CountIncludingInFaces = 0;
		};
	}
}