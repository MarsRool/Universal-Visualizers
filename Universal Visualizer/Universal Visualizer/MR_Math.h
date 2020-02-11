#pragma once
#include "stdafx.h"
#include "global.h"

namespace MR
{
	namespace Helpers
	{
		static class Math
		{
		public:			
			/// <summary>
			/// ¬озвращает угол в градусах
			/// </summary>
			/// <param name="Radians">угол в радианах</param>
			/// <returns></returns>
			static double RadiansToDegrees(double Radians)
			{
				return Radians / PI * 180.0;
			}
			/// <summary>
			/// ¬озвращает угол в радианах
			/// </summary>
			/// <param name="Degrees">угол в градусах</param>
			/// <returns></returns>
			static double DegreesToRadians(double Degrees)
			{
				return Degrees * PI / 180.0f;
			}

			static double ValueToDiapazon(double value, double left, double right)
			{
				if (left > right)
					std::swap(left, right);
				while (value >= right)
					value -= (right - left);
				while (value < left)
					value += (right - left);
				return value;
			}
		};
	}
}