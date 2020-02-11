#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Math.h"
#include "DoublePreciseApproximate.h"

namespace MR
{
	namespace Geometry
	{
		class Vector3D;
		/// <summary>
		/// �����, �������������� ����� ���� �� ���������
		/// </summary>
		class Angle2D
		{
		public:
			/// <summary>
			/// Degrees - ���� � ��������.
			/// Radians - ���� � ��������.
			/// </summary>
			enum AngleType { Degrees, Radians };
			/// <summary>
			/// ������� ������� ����
			/// </summary>
			/// <param name="accuracyType">������ ��� ��������������� �������</param>
			Angle2D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
					MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			~Angle2D();
			/// <summary>
			/// ������� ���� �� angle � ����������� �� ������� ����������
			/// </summary>
			/// <param name="angle">�������� ����</param>
			/// <param name="angleType">������� ��� �������</param>
			/// <param name="accuracyType">������ ��� ��������������� �������</param>
			Angle2D(double angle, AngleType angleType = AngleType::Degrees,
								MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
								MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// ������� ���� �� angle � ����������� �� ������� ����������
			/// </summary>
			/// <param name="angle">�������� ����</param>
			/// <param name="angleType">������� ��� �������</param>
			/// <param name="accuracyType">������ ��� ��������������� �������</param>
			Angle2D(const MR::Helpers::DoublePreciseApproximate &angle, AngleType angleType = AngleType::Degrees);
			/// <summary>
			/// ������� ���� �� �������
			/// </summary>
			/// <param name="vector"></param>
			Angle2D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
											MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// ���������� ���� � ��������.
			/// </summary>
			double getAngleDegree() const;
			/// <summary>
			/// ������������� ���� � ��������.
			/// </summary>
			void setAngleDegree(double angleDegree);

			/// <summary>
			/// ���������� ���� � ��������.
			/// </summary>
			double getAngleRadians() const;
			/// <summary>
			/// ������������� ���� � ��������.
			/// </summary>
			void setAngleRadians(double angleRadians);

			/// <summary>
			/// ���������� ������ ����������� �������������� ����
			/// </summary>
			Vector3D getDirectVector() const;
			/// <summary>
			/// ������������� ���� �������������� ������� �����������
			/// </summary>
			void setAngleFromDirectVector(const Vector3D &vectorDirect);

			/// <summary>
			/// ���������� ������ ����������� ����� �� �������� (�� 90 �������� ������ ������� �������)
			/// </summary>
			Vector3D getUpVector() const;

			/// <summary>
			/// ���������� ������ ����������� ���� �� �������� (�� 90 �������� �� ������� �������)
			/// </summary>
			Vector3D getDownVector() const;

			Angle2D &operator = (const Angle2D &right);
			Angle2D operator +(const Angle2D &right) const;
			Angle2D operator -(const Angle2D &right) const;
			const bool operator ==(const Angle2D &right) const;
			const bool operator !=(const Angle2D &right) const;
		private:
			MR::Helpers::DoublePreciseApproximate angleDegree;
		};
	}
}