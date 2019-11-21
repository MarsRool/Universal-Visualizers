#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"

namespace MR
{
	namespace Geometry
	{
		class Basis2D
		{
		public:
			Basis2D(const Vector3D &vec1, const Vector3D &vec2);

			///<summary>
			///возвращает угол вектора в радианах. От 0 до 2Pi
			///</summary>
			double getAngleRad_0To2Pi(const Vector3D &vec, bool &isOk) const;
			///<summary>
			///возвращает угол вектора в радианах. От -Pi до Pi
			///</summary>
			double getAngleRad_NegPiToPi(const Vector3D &vec, bool &isOk) const;

			///<summary>
			///возвращает угол между векторами в радианах. От 0 до Pi. Эквивалент Vector3D::getAngleRad()
			///</summary>
			double getAngleRad_0ToPi(const Vector3D &left, const Vector3D &right, bool &isOk) const;
			///<summary>
			///возвращает угол между векторами в радианах. От 0 до 2Pi
			///</summary>
			double getAngleRad_0To2Pi(const Vector3D &left, const Vector3D & right, bool &isOk) const;
			///<summary>
			///возвращает угол между векторами в радианах. От -Pi до Pi
			///</summary>
			double getAngleRad_NegPiToPi(const Vector3D &left, const Vector3D & right, bool &isOk) const;
		private:
			///<summary>
			///true- если вектор в плоскости 2D базиса
			///</summary>
			bool isVectorsInPlane(const Vector3D &vec) const;
			Vector3D Ex, Ey;
		};
	}
}