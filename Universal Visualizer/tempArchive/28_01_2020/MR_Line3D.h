#pragma once
#include "MR_Vector3D.h"
#include "stdafx.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///прямая в пространстве, заданная в каноническом виде
		///</summary>
		class Line3D
		{
		public:
			Line3D();
			Line3D(const Vector3D &Direction_i, const Point3D &Point_i);
			Line3D(const Point3D &Point1, const Point3D &Point2);
			~Line3D();

			///<summary>
			///true- когда примерно равны (отличие порядка smallV)
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
			///рассчитывает по заданной x
			///</summary>
			Point3D calculateX(double x) const;
			///<summary>
			///рассчитывает по заданной y
			///</summary>
			Point3D calculateY(double y) const;
			///<summary>
			///рассчитывает по заданной z
			///</summary>
			Point3D calculateZ(double z) const;
			///<summary>
			///рассчитывает по заданной t
			///</summary>
			Point3D calculateT(double t) const;
			
			///<summary>
			///true- если параллельны
			///</summary>
			bool isParallel(const Line3D &line) const;
			///<summary>
			///возвращает угол между прямыми в радианах
			///</summary>
			double getAngleRad(const Line3D &line) const;
		private:
			///<summary>
			///направление прямой
			///</summary>
			Vector3D Direction;
			///<summary>
			///точка, через которую проходит прямая
			///</summary>
			Point3D Point;
		};
	}
}