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
			~DoublePreciseApproximate() {}

			///<summary>
			///вернуть точность числа
			///</summary>
			AccuracyType getAccuracyType() const { return type; }
			///<summary>
			///задать точность числа
			///</summary>
			void setAccuracyType(AccuracyType type) { this->type = type; }
			///<summary>
			///вернуть погрешность числа
			///</summary>
			double getEpsilon() const { return epsilon; }
			///<summary>
			///задать погрешность числа
			///</summary>
			void setEpsilon(double epsilon) { this->epsilon = epsilon; }
			///<summary>
			///вернуть число
			///</summary>
			double getValue() const { return value; }
			///<summary>
			///вернуть число
			///</summary>
			double operator ()() const { return value; }
			const bool operator == (const DoublePreciseApproximate &right) const;
			const bool operator != (const DoublePreciseApproximate &right) const;
			const bool operator > (const DoublePreciseApproximate &right) const;
			const bool operator < (const DoublePreciseApproximate &right) const;
			const bool operator >= (const DoublePreciseApproximate &right) const;
			const bool operator <= (const DoublePreciseApproximate &right) const;

			const bool operator == (double right) const;
			const bool operator != (double right) const;
			const bool operator > (double right) const;
			const bool operator < (double right) const;
			const bool operator >= (double right) const;
			const bool operator <= (double right) const;

			DoublePreciseApproximate &operator = (const DoublePreciseApproximate &right);
			DoublePreciseApproximate &operator = (double right);

			DoublePreciseApproximate operator +(const DoublePreciseApproximate &right) const;
			DoublePreciseApproximate operator -(const DoublePreciseApproximate &right) const;
			DoublePreciseApproximate operator *(const DoublePreciseApproximate &right) const;
			DoublePreciseApproximate operator /(const DoublePreciseApproximate &right) const;

			DoublePreciseApproximate operator +(double right) const;
			DoublePreciseApproximate operator -(double right) const;
			DoublePreciseApproximate operator *(double right) const;
			DoublePreciseApproximate operator /(double right) const;
		private:
			double value;
			double epsilon;
			AccuracyType type;
		};
	}
}