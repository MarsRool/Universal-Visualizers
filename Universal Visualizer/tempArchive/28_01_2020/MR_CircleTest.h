#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Face.h"
#include "MR_Plane3D.h"
#include "MR_Basis2D.h"
#include "MR_Sector2D.h"
//���� ����� �� ��������� ����� � ���������, �� ��������� ��������� � ������������.
//�������������, ��� ��������� ��� ����� ����� � ������������.
//��� ���������� � ��������� �� smallV
namespace MR
{
	namespace Geometry
	{
		///<summary>
		///����� ��� ������������ ���������� ����� ������ ��� ������� �����.
		///<summary>
		class CircleTest
		{
		public:
			///<summary>
			///�������� ����� ����� ��� �����
			///<summary>
			CircleTest(const Model::Face &face, const Geometry::Point3D &point, double radius = smallV);
			~CircleTest();

			bool isInside() { return IsInside; }
		private:
			///<summary>
			///�������� �� ������������ CircleTest
			///<summary>
			bool check();
			///<summary>
			///�������� �� ����������� ����������� ������. true- ���� ���������� � ������ ���� ��������.
			///<summary>
			bool isCircleIntersectFace() const;
			///<summary>
			///�������� �� �������������� ����� ��������� �����. true- ���� �����������, ������ ��� ���������.
			///<summary>
			bool isPointInFacePlane() const;
			///<summary>
			///���� ����� �� ��������� � �����
			///<summary>
			void test();
			///<summary>
			///������ ����������� ����������
			///<summary>
			double Radius = smallV;
			///<summary>
			///�������� �����, ������������ ������� ���������� ���������� �����
			///</summary>
			const MR::Model::Face TestFace;
			///<summary>
			///����������� �����
			///</summary>
			const Geometry::Point3D TestPoint;
			///<summary>
			///true- ���� ����� ������. �� ���������, ��� �������
			///<summary>
			bool IsInside = false;
			///<summary>
			///true- ���� ���� ����������.
			///<summary>
			bool isOk;
			std::list<Sector2D*> Sectors;
		};
	}
}