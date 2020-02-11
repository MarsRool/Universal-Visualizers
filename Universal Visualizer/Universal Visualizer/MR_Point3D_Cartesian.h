#pragma once
#include "stdafx.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///MR 2D точка
		///</summary>
		class Point2D
		{
		private:
			double X, Y;
		public:
		};

		class Point3DSpherical;
		///<summary>
		///MR 3D точка
		///</summary>
		class Point3DCartesian
		{
		public:
			Point3DCartesian();
			Point3DCartesian(double X_i, double Y_i, double Z_i);
			Point3DCartesian(const Point3DCartesian &PointToCopy);
			~Point3DCartesian() {}//пустой деструктор.

			friend bool equalPoints(const Point3DCartesian *point_left, const Point3DCartesian *point_right);
			bool operator == (const Point3DCartesian &point_right) const { return equalPoints(this, &point_right); }
			Point3DCartesian &operator = (const Point3DCartesian &point_right);
			Point3DCartesian operator + (const Point3DCartesian &point_right) const;
			Point3DCartesian operator - (const Point3DCartesian &point_right) const;
			///<summary>
			///увеличивает кол-во вхождений в ребра
			///</summary>
			Point3DCartesian &operator ++ ();
			///<summary>
			///уменьшает кол-во вхождений в ребра
			///</summary>
			Point3DCartesian &operator -- ();
			Point3DCartesian &operator += (int added);

			///<summary>
			///true- если количество ребер, которые содержат точку, больше 0.
			///</summary>
			bool existing() const { return (CountIncludingInEdges > 0); }
			int getCountIncludingInEdges() const { return CountIncludingInEdges; }

			double x() const { return X; }
			double y() const { return Y; }
			double z() const { return Z; }
			void setX(double x_in) { X = x_in; }
			void setY(double y_in) { Y = y_in; }
			void setZ(double z_in) { Z = z_in; }
			void set(double X_i, double Y_i, double Z_i) { setX(X_i); setY(Y_i); setZ(Z_i); }
			void get(double &X_i, double &Y_i, double &Z_i) const { X_i = x(); Y_i = y(); Z_i = z(); }

			friend Point3DCartesian *searchPoint(const std::list<Point3DCartesian*> &Points, Point3DCartesian *Point_key);//находит адрес адреса точки в массиве точек

			double distance(const Point3DCartesian &point) const;
			static Point3DCartesian getMiddlePoint(const Point3DCartesian &point1, const Point3DCartesian &point2);
			Point3DCartesian getMiddlePoint(const Point3DCartesian &point) { return getMiddlePoint(*this, point); }
			Point3DSpherical toSpherical() const;
		private:
			bool check();

			double X, Y, Z;
			///<summary>
			///количество ребер, которые содержат точку. добавляется при формировании модели на этапе формирования массива ребер. Сначала равна 0.
			///</summary>
			int CountIncludingInEdges = 0;
		};
	}
}