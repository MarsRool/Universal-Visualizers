#pragma once
#include "stdafx.h"

namespace MR
{
	namespace Geometry
	{
		class Point2D//MR 2D �����
		{
		private:
			double X, Y;
		public:
		};

		///<summary>
		///MR 3D �����
		///</summary>
		class Point3D
		{
		public:
			Point3D();
			Point3D(double X_i, double Y_i, double Z_i);
			Point3D(const Point3D &PointToCopy);
			~Point3D() {}//������ ����������.

			friend bool equalPoints(const Point3D *point_left, const Point3D *point_right);
			const bool operator == (const Point3D &point_right);
			Point3D &operator = (const Point3D &point_right);
			Point3D operator + (const Point3D &point_right) const;
			Point3D operator - (const Point3D &point_right) const;
			///<summary>
			///����������� ���-�� ��������� � �����
			///</summary>
			Point3D &operator ++ ();
			///<summary>
			///��������� ���-�� ��������� � �����
			///</summary>
			Point3D &operator -- ();
			Point3D &operator += (short int added);

			///<summary>
			///true- ���� ���������� �����, ������� �������� �����, ������ 0.
			///</summary>
			bool existing() const { return CountIncludingInEdges; }
			short int getCountIncludingInEdges() const { return CountIncludingInEdges; }

			double x() const { return X; }
			double y() const { return Y; }
			double z() const { return Z; }
			void setX(double x_in) { X = x_in; }
			void setY(double y_in) { Y = y_in; }
			void setZ(double z_in) { Z = z_in; }
			void set(double X_i, double Y_i, double Z_i);
			void get(double &X_i, double &Y_i, double &Z_i);

			friend Point3D *searchPoint(const std::list<Point3D*> &Points, Point3D *Point_key);//������� ����� ������ ����� � ������� �����

			double distance(const Point3D &point) const;
			static Point3D getMiddlePoint(const Point3D &point1, const Point3D &point2);
			Point3D getMiddlePoint(const Point3D &point) { return getMiddlePoint(*this, point); }
		private:
			bool check();

			double X, Y, Z;
			///<summary>
			///���������� �����, ������� �������� �����. ����������� ��� ������������ ������ �� ����� ������������ ������� �����. ������� ����� 0.
			///</summary>
			short int CountIncludingInEdges = 0;
		};
	}
}