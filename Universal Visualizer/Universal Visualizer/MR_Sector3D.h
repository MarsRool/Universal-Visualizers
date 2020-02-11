#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Angle3D.h"
#include "MR_Face.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///����� ������� ����� � ������������, ����������� � ������� ��������� ��������������� ��������� ����� �� ��������� �����
		///</summary>
		class Sector3D
		{
		public:
			///<summary>
			///������� ������ ����� �� (���������) �������������� ������
			///</summary>
			Sector3D(const MR::Model::Face &face, const Point3DCartesian &centerSphere);
			///<summary>
			///������� ����� ������� �����
			///</summary>
			Sector3D(const Sector3D &other);

			///<summary>
			///true- ���� ������ �� �������� ����� ��� ��������� ����� ���������
			///</summary>
			bool isFullSphereOrEmpty() { return (angles.size() == 0); }
			//bool isZero(); - ��������� ��������, ����� ����� ����������� ����������� ������������ ������� ����.������, ����� ������� ������� � �������� ���� ��� ��������� ������� � �������
			//bool isFullCircle(); - ����������
			///<summary>
			///true- ���� ������ ���������� ������ ������.
			///</summary>
			bool isSectorIntersect(const Sector3D &sec) const;
			///<summary>
			///true- ���� ������ �������� ������� ������� (������ � ���).
			///�.�. ����� ��� ������� 2 ����� ��������� �����.
			///��� ����, ����� ����������, ����� �� �� ����������.
			///</summary>
			bool isSectorTangential(const Sector3D &sec) const;

			///<summary>
			///���������� ��� �������, ���� ��� ��������, ����� ���������� nullptr
			///</summary>
			static Sector3D *integrateSectors(const Sector3D &sec1, const Sector3D &sec2);
			///<summary>
			///���������� �������. �������� sectors
			///</summary>
			static void integrateSectors(std::list<Sector3D*> &sectors);
		private:
			//static void dividePath(const std::list<MR::Geometry::Point3D*> &points, std::vector<std::list<MR::Geometry::Point3D*>> &pathes);
			//static void checkPath(const std::list<MR::Geometry::Point3D*> &points);
			bool check();
			void setFromPointsPath(const std::list<MR::Geometry::Point3DCartesian*> &points, const Point3DCartesian &centerSphere);
			///<summary>
			///�������� ������, ���� � ��� ���������� ������������� �����
			///</summary>
			void simplify();
			std::list<Angle3D> angles;
		};
	}
}