#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_Face.h"
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
		///<summary>
		///MR ������.
		///�������� - ������������ ��������, ����� �������� ��������� �� ����� � �������� ���������������� ���������.
		///Object - �������� ������ Points, Edges � Points. ������ �� ����� �������� � ������� ������.
		///</summary>
		class Object
		{
		public:
			///<summary>
			///�������� ������� �������
			///</summary>
			Object();
			///<summary>
			///������ ������ ��� �������� ����� ��� �������. �������: ����� ������ ���� ��������� �� ������.
			///</summary>
			Object(const std::list<Face*> &Faces_i, string name = "");
			Object(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i, string name = "");//�������� ������� �� ��� ������������������ ��������
			///<summary>
			///������� ������ ����� �������
			///</summary>
			Object(const Object &objectToCopy);
			~Object();

			///<summary>
			///true- ���� ������ ������
			///</summary>
			bool isEmpty();

			Geometry::Point3DCartesian getPos() const;
			void setPos(Geometry::Point3DCartesian *pointIn);

			string getStrName() const;
			void setStrName(string strIn);
			void getFaces(std::list<Face*> &Faces_out) const { Faces_out = Faces; }

			void drawObject();

			///<summary>
			///������� ������ ����� �������
			///</summary>
			virtual Object& operator = (const Object &objToCopy);

			static void uniquePoints(std::list<Geometry::Point3DCartesian*> &list);
			static void uniqueEdges(std::list<Edge*> &list);

		protected:
			bool check() const;
			///<summary>
			///�������� ���� ������ �� �������������� ����� ���������
			///</summary>
			bool isAllFacesInOnePlane() const;
			///<summary>
			///������ �������� ������ � ���������� ������� � �������� ����������.
			///</summary>
			void clearData();
			///<summary>
			///�������� �������������� ���������
			///</summary>
			void clearNonexistent();
			///<summary>
			///������� ������ ����� ������� � ������������ ����� �����������! �� ���� ������� ��������� ����������� ������������ �������
			///</summary>
			void CopyUnique(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i);
			///<summary>
			///���������� ������ ���� �������� � ������� ������, ��� ���� �������� objectToCopy ���������� ������
			///</summary>
			void ReplaceNotUnique(Object &objectToCopy);
			///<summary>
			///�������� �������������� ��������� ��������� ��� �� �������������
			///</summary>
			void deleteNotUsedElements();

			void clearSelection();
			///<summary>
			///�������� ��� ����� � ��� � ��� �������
			///</summary>
			void selectFaces(Face* face);
			///<summary>
			///�������� ��� ����� � ��� � ��� ������� �� ������� ������
			///</summary>
			void selectFaces(Face* face, const std::list<Face*> &Faces);

			double counticolor(double a, double b, double c, int k);

			///<summary>
			/// ����� �������
			///</summary>
			std::list<Geometry::Point3DCartesian*> Points;
			///<summary>
			/// ����� �������
			///</summary>
			std::list<Edge*> Edges;
			///<summary>
			/// ����� �������
			///</summary>
			std::list<Face*> Faces;
			///<summary>
			/// ��� �������
			///</summary>
			string StrName = "";

			///<summary>
			///������� �������
			///</summary>
			Geometry::Point3DCartesian Position;

			///<summary>
			///������������� �������
			///</summary>
			short int TypeColor = 3;/*��� ��������� �������.
			1 - ������� ������� ������ �������(���������)
				2 - ������� ������� ������ �������(����������)
				3 - ��������� 4 ������� �� dl, dr, ul, ur.
				4 - ��������.*/
				///<summary>
				///�����������(����������) ���� �������
				///</summary>
			RGB_MR Color;
			///<summary>
			///����������� ���� downleft, downright, upleft, upright colors (�� 0.0 �� 1.0)
			///</summary>
			RGB_MR ColorGrad[4];
			///<summary>
			///��������. �� ������ �����. ������ �� �������� �� ����������� ������ ����.
			///</summary>
			RGB_MR ColorGradLand[7];
		};
	}
}
