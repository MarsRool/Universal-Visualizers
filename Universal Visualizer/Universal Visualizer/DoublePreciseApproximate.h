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
			~DoublePreciseApproximate() {}

			///<summary>
			///������� �������� �����
			///</summary>
			AccuracyType getAccuracyType() const { return type; }
			///<summary>
			///������ �������� �����
			///</summary>
			void setAccuracyType(AccuracyType type) { this->type = type; }
			///<summary>
			///������� ����������� �����
			///</summary>
			double getEpsilon() const { return epsilon; }
			///<summary>
			///������ ����������� �����
			///</summary>
			void setEpsilon(double epsilon) { this->epsilon = epsilon; }
			///<summary>
			///������� �����
			///</summary>
			double getValue() const { return value; }
			///<summary>
			///������� �����
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