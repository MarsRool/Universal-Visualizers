#pragma once
#include "stdafx.h"

namespace MR
{
	namespace Geometry
	{
		class Point2D//MR 2D точка
		{
		private:
			double X, Y;
		public:
		};

		///<summary>
		///MR 3D точка
		///</summary>
		class Point3D
		{
		public:
			Point3D();
			Point3D(double X_i, double Y_i, double Z_i);
			Point3D(const Point3D &PointToCopy);
			~Point3D() {}//пустой деструктор.

			friend bool equalPoints(const Point3D *point_left, const Point3D *point_right);
			const bool operator == (const Point3D &point_right);
			Point3D &operator = (const Point3D &point_right);
			Point3D operator + (const Point3D &point_right) const;
			Point3D operator - (const Point3D &point_right) const;
			///<summary>
			///увеличивает кол-во вхождений в ребра
			///</summary>
			Point3D &operator ++ ();
			///<summary>
			///уменьшает кол-во вхождений в ребра
			///</summary>
			Point3D &operator -- ();
			Point3D &operator += (short int added);

			///<summary>
			///true- если количество ребер, которые содержат точку, больше 0.
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

			friend Point3D *searchPoint(const std::list<Point3D*> &Points, Point3D *Point_key);//находит адрес адреса точки в массиве точек

			double distance(const Point3D &point) const;
			static Point3D getMiddlePoint(const Point3D &point1, const Point3D &point2);
			Point3D getMiddlePoint(const Point3D &point) { return getMiddlePoint(*this, point); }
		private:
			bool check();

			double X, Y, Z;
			///<summary>
			///количество ребер, которые содержат точку. добавляется при формировании модели на этапе формирования массива ребер. Сначала равна 0.
			///</summary>
			short int CountIncludingInEdges = 0;
		};
	}
}