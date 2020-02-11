#pragma once
#include "stdafx.h"
#include "global.h"

namespace MR
{
	namespace Helpers
	{
		///<summary>
		///класс приближенных вычислений double
		///</summary>
		class DoublePreciseApproximate
		{
		public:
			/// <summary>
			/// Precise - точные вычисления.
			/// Approximate - приблизительные вычисления.
			/// </summary>
			enum AccuracyType { Precise, Approximate };
			DoublePreciseApproximate();
			///<summary>
			///создание вещественного числа с погрешностью
			///</summary>
			///<param name ="value">значение</param>
			///<param name ="value">погрешность</param>
			DoublePreciseApproximate(double value, double epsilon = smallV, AccuracyType type = AccuracyType::Approximate);
			///<summary>
			///создание вещественного числа с погрешностью из другого вещественного числа с погрешностью
			///</summary>
			///<param name ="value">значение</param>
			///<param name ="value">погрешность (-1 значит погрешность берется из other)</param>
			DoublePreciseApproximate(const DoublePreciseApproximate &other, double epsilon = -1.0);

			///<summary>
			///вернуть точность числа
			///</summary>
			inline AccuracyType getAccuracyType() const;
			///<summary>
			///задать точность числа
			///</summary>
			inline void setAccuracyType(AccuracyType type);
			///<summary>
			///вернуть погрешность числа
			///</summary>
			inline double getEpsilon() const;
			///<summary>
			///задать погрешность числа
			///</summary>
			inline void setEpsilon(double epsilon);
			///<summary>
			///вернуть число
			///</summary>
			inline double getValue() const;
			///<summary>
			///вернуть число
			///</summary>
			inline double operator ()() const;
			inline const bool operator == (const DoublePreciseApproximate &right) const;
			inline const bool operator != (const DoublePreciseApproximate &right) const;
			inline const bool operator > (const DoublePreciseApproximate &right) const;
			inline const bool operator < (const DoublePreciseApproximate &right) const;
			inline const bool operator >= (const DoublePreciseApproximate &right) const;
			inline const bool operator <= (const DoublePreciseApproximate &right) const;

			inline const bool operator == (double right) const;
			inline const bool operator != (double right) const;
			inline const bool operator > (double right) const;
			inline const bool operator < (double right) const;
			inline const bool operator >= (double right) const;
			inline const bool operator <= (double right) const;

			inline DoublePreciseApproximate &operator = (const DoublePreciseApproximate &right);
			inline DoublePreciseApproximate &operator = (double right);

			inline DoublePreciseApproximate operator +(const DoublePreciseApproximate &right) const;
			inline DoublePreciseApproximate operator -(const DoublePreciseApproximate &right) const;
			inline DoublePreciseApproximate operator *(const DoublePreciseApproximate &right) const;
			inline DoublePreciseApproximate operator /(const DoublePreciseApproximate &right) const;

			inline DoublePreciseApproximate operator +(double right) const;
			inline DoublePreciseApproximate operator -(double right) const;
			inline DoublePreciseApproximate operator *(double right) const;
			inline DoublePreciseApproximate operator /(double right) const;
		private:
			double value;
			double epsilon;
			AccuracyType type;
		};
	}
}