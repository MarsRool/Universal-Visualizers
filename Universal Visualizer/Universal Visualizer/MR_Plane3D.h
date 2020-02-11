#pragma once
#include "MR_Line3D.h"

namespace MR
{
	namespace Model
	{
		class Face;
	}
	namespace Geometry
	{
		class Plane3D
		{
		public:
			Plane3D(const Vector3D &Normal_i, const Point3DCartesian &Point_i);//вектор нормали и точка на плоскости
			Plane3D(const Vector3D &Vector1, const Vector3D &Vector2, const Point3DCartesian &Point_i);//два вектора, параллельные плоскости и точка.
			Plane3D(const Point3DCartesian &Point1, const Point3DCartesian &Point2, const Point3DCartesian &Point3);//три точки на плоскости
			Plane3D(const Model::Face &face);
			Plane3D(const Plane3D &planeToCopy);
			~Plane3D();

			Vector3D getNormal() const { return Normal; }
			bool operator==(const Plane3D &plane);
			bool operator!=(const Plane3D &plane) { return !(operator==(plane)); }
			
			double distance(const Point3DCartesian &Point_i) const;
			///<summary>
			///Возвращает где находится точка: 
			///1 - снаружи, 0 - на плоскости, -1 - внутри плоскости
			///</summary>
			short int whereIsPoint(const Point3DCartesian &Point_i) const;
			///<summary>
			///true- если точки находятся в обеих сторонах от плоскости
			///</summary>
			bool istDotsInBothSides(const std::list<Point3DCartesian*> &Points) const;

			bool isInPlane(const Point3DCartesian &point);
			bool isInPlane(const Line3D &line);
		private:
			///<summary>
			///нормаль плоскости
			///<summary>
			Vector3D Normal;
			///<summary>
			///точка, через которую проходит плоскость
			///<summary>
			Point3DCartesian Point;
		};
	}
}
