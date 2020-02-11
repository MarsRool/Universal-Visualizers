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
			Line3D(const Vector3D &Direction_i, const Point3DCartesian &Point_i);
			Line3D(const Point3DCartesian &Point1, const Point3DCartesian &Point2);
			~Line3D();

			///<summary>
			///true- когда примерно равны (отличие порядка smallV)
			///</summary>
			friend bool compareAproximately(const Line3D &left, const Line3D &right);
			friend Line3D operator - (const Line3D &v);
			Line3D &operator = (const Line3D & right);
			bool operator == (const Line3D & right) const;
			bool operator != (const Line3D & right) const { return (!operator==(right)); }
			const Point3DCartesian& getPoint() const { return Point; }

			double distance(const Point3DCartesian &point) const;
			double distance(const Line3D &line) const;
			///<summary>
			///рассчитывает по заданной x
			///</summary>
			Point3DCartesian calculateX(double x) const;
			///<summary>
			///рассчитывает по заданной y
			///</summary>
			Point3DCartesian calculateY(double y) const;
			///<summary>
			///рассчитывает по заданной z
			///</summary>
			Point3DCartesian calculateZ(double z) const;
			///<summary>
			///рассчитывает по заданной t
			///</summary>
			Point3DCartesian calculateT(double t) const;
			
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
			Point3DCartesian Point;
		};
	}
}