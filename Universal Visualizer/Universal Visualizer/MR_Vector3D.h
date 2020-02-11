#pragma once
#include "stdafx.h"
#include "MR_Point3D_Cartesian.h"

namespace MR
{
	namespace Geometry
	{
		class Vector3D
		{
		public:
			Vector3D();
			Vector3D(double Vx_i, double Vy_i, double Vz_i);
			Vector3D(const Point3DCartesian &point1, const Point3DCartesian &point2);
			Vector3D(const Vector3D &vectorToCopy);
			~Vector3D();

			void setVector(const Point3DCartesian &point1, const Point3DCartesian &point2);
			void setVector(double Vx_i, double Vy_i, double Vz_i);
			void getVector(double &Vx_i, double &Vy_i, double &Vz_i) const;
			double getLength() const;
			double vx() const { return Vx; }
			double vy() const { return Vy; }
			double vz() const { return Vz; }
			
			///<summary>
			///true- если вектор нулевой
			///</summary>
			bool istZero();
			///<summary>
			///нормировать вектор
			///</summary>
			void normalize();

			friend double scalarProduct(const Vector3D &vec1, const Vector3D &vec2);
			friend Vector3D vectorProduct(const Vector3D &vec1, const Vector3D &vec2);
			friend double mixedProduct(const Vector3D &vec1, const Vector3D &vec2, const Vector3D &vec3);
			double scalarProduct(const Vector3D &vec2) const { return MR::Geometry::scalarProduct(*this, vec2); }
			Vector3D vectorProduct(const Vector3D &vec2) const { return MR::Geometry::vectorProduct(*this, vec2); }
			double mixedProduct(const Vector3D &vec2, const Vector3D &vec3) const { return MR::Geometry::mixedProduct(*this, vec2, vec3); }

			///<summary>
			///true- когда примерно параллельны (отличие порядка smallV)
			///</summary>
			friend bool parallelAproximately(const Vector3D &left, const Vector3D &right);
			///<summary>
			///true- когда примерно равны (отличие порядка smallV)
			///</summary>
			friend bool compareAproximately(const Vector3D &left, const Vector3D &right);
			friend Vector3D operator - (const Vector3D &v);
			Vector3D &operator = (const Vector3D & right);
			Vector3D operator + (const Vector3D & right) const;
			Vector3D operator - (const Vector3D & right) const;
			Vector3D operator * (double a) const;
			Vector3D operator / (double a) const;
			bool operator == (const Vector3D & right) const;
			bool operator != (const Vector3D & right) const { return (!operator==(right)); }

			///<summary>
			///возвращает угол между векторами в радианах. От 0 до Pi
			///</summary>
			double getAngleRad(const Vector3D & right) const;
		private:
			bool check();

			void calculateLength();

			///<summary>
			///Vx, Vy, Vz - компоненты вектора
			///</summary>
			double Vx = 0.0, Vy = 0.0, Vz = 0.0;
			///<summary>
			///Длина вектора
			///</summary>
			double Length = 0.0;
		};
	}
}