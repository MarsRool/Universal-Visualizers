#pragma once
#include "MR_Vector3D.h"
#include "stdafx.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///������ � ������������, �������� � ������������ ����
		///</summary>
		class Line3D
		{
		public:
			Line3D();
			Line3D(const Vector3D &Direction_i, const Point3D &Point_i);
			Line3D(const Point3D &Point1, const Point3D &Point2);
			~Line3D();

			///<summary>
			///true- ����� �������� ����� (������� ������� smallV)
			///</summary>
			friend bool compareAproximately(const Line3D &left, const Line3D &right);
			friend Line3D operator - (const Line3D &v);
			Line3D &operator = (const Line3D & right);
			bool operator == (const Line3D & right) const;
			bool operator != (const Line3D & right) const { return (!operator==(right)); }
			const Point3D& getPoint() const { return Point; }

			double distance(const Point3D &point) const;
			double distance(const Line3D &line) const;
			///<summary>
			///������������ �� �������� x
			///</summary>
			Point3D calculateX(double x) const;
			///<summary>
			///������������ �� �������� y
			///</summary>
			Point3D calculateY(double y) const;
			///<summary>
			///������������ �� �������� z
			///</summary>
			Point3D calculateZ(double z) const;
			///<summary>
			///������������ �� �������� t
			///</summary>
			Point3D calculateT(double t) const;
			
			///<summary>
			///true- ���� �����������
			///</summary>
			bool isParallel(const Line3D &line) const;
			///<summary>
			///���������� ���� ����� ������� � ��������
			///</summary>
			double getAngleRad(const Line3D &line) const;
		private:
			///<summary>
			///����������� ������
			///</summary>
			Vector3D Direction;
			///<summary>
			///�����, ����� ������� �������� ������
			///</summary>
			Point3D Point;
		};
	}
}