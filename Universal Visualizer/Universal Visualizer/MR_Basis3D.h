#pragma once
#include "stdafx.h"
#include "MR_Vector3D.h"
#include "MR_Angle3D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///класс трехмерного ортонормированного базиса
		///</summary>
		class Basis3D
		{
		public:
			///<summary>
			///создает ортонормированный базис i, j, k
			///</summary>
			Basis3D();
			///<summary>
			///создает ортонормированный базис по трем векторам
			///</summary>
			Basis3D(const Vector3D &vec1, const Vector3D &vec2, const Vector3D &vec3);
			///<summary>
			///создает ортонормированный базис по двум векторам. третий равен векторному произведению.
			///</summary>
			Basis3D(const Vector3D &vec1, const Vector3D &vec2);
			
			///<summary>
			///декартовы координаты в сферические
			///</summary>
			static void CartesianToSpherical(const MR::Helpers::DoublePreciseApproximate &x,
									const MR::Helpers::DoublePreciseApproximate &y,
									const MR::Helpers::DoublePreciseApproximate &z,
									Angle3D &spereAngle);
			///<summary>
			///сферические координаты в декартовы
			///</summary>
			static void SphericalToCartesian(const Angle3D &spereAngle,
				MR::Helpers::DoublePreciseApproximate &x,
				MR::Helpers::DoublePreciseApproximate &y,
				MR::Helpers::DoublePreciseApproximate &z);
		private:
			Vector3D Ex, Ey, Ez;
		};
	}
}