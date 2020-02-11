#pragma once
#include "stdafx.h"
#include "global.h"

namespace MR
{
	namespace Helpers
	{
		///<summary>
		///����� ������������ ���������� double
		///</summary>
		class DoublePreciseApproximate
		{
		public:
			/// <summary>
			/// Precise - ������ ����������.
			/// Approximate - ��������������� ����������.
			/// </summary>
			enum AccuracyType { Precise, Approximate };
			DoublePreciseApproximate();
			///<summary>
			///�������� ������������� ����� � ������������
			///</summary>
			///<param name ="value">��������</param>
			///<param name ="value">�����������</param>
			DoublePreciseApproximate(double value, double epsilon = smallV, AccuracyType type = AccuracyType::Approximate);
			///<summary>
			///�������� ������������� ����� � ������������ �� ������� ������������� ����� � ������������
			///</summary>
			///<param name ="value">��������</param>
			///<param name ="value">����������� (-1 ������ ����������� ������� �� other)</param>
			DoublePreciseApproximate(const DoublePreciseApproximate &other, double epsilon = -1.0);

			///<summary>
			///������� �������� �����
			///</summary>
			inline AccuracyType getAccuracyType() const;
			///<summary>
			///������ �������� �����
			///</summary>
			inline void setAccuracyType(AccuracyType type);
			///<summary>
			///������� ����������� �����
			///</summary>
			inline double getEpsilon() const;
			///<summary>
			///������ ����������� �����
			///</summary>
			inline void setEpsilon(double epsilon);
			///<summary>
			///������� �����
			///</summary>
			inline double getValue() const;
			///<summary>
			///������� �����
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