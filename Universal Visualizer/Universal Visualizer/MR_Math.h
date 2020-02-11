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
			/// ���������� ���� � ��������
			/// </summary>
			/// <param name="Radians">���� � ��������</param>
			/// <returns></returns>
			static double RadiansToDegrees(double Radians)
			{
				return Radians / PI * 180.0;
			}
			/// <summary>
			/// ���������� ���� � ��������
			/// </summary>
			/// <param name="Degrees">���� � ��������</param>
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