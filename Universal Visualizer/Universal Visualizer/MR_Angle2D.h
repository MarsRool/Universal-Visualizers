#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Math.h"
#include "MR_Vector3D.h"
#include "DoublePreciseApproximate.h"

namespace MR
{
	namespace Geometry
	{
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
			/// <summary>
			/// ������� ����� ����
			/// </summary>
			/// <param name="other">���������� ������ ����</param>
			Angle2D(const Angle2D &other);
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
			/// <param name="vector">������������ ������</param>
			/// <param name="accuracyType">������ ��� ��������������� �������</param>
			Angle2D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			~Angle2D() {}

			/// <summary>
			/// ���������� ���� � ��������.
			/// </summary>
			double getAngleDegree() const { return angleDegree(); }
			/// <summary>
			/// ������������� ���� � ��������.
			/// </summary>
			void setAngleDegree(double angleDegree) { this->angleDegree = MR::Helpers::Math::ValueToDiapazon(angleDegree, 0, 360); }

			/// <summary>
			/// ���������� ���� � ��������.
			/// </summary>
			double getAngleRadians() const { return MR::Helpers::Math::DegreesToRadians(getAngleDegree()); }
			/// <summary>
			/// ������������� ���� � ��������.
			/// </summary>
			void setAngleRadians(double angleRadians) { setAngleDegree(MR::Helpers::Math::RadiansToDegrees(angleRadians)); }

			/// <summary>
			/// ���������� ������ ����������� �������������� ����
			/// </summary>
			Vector3D getDirectVector() const { return Vector3D(std::cos(getAngleRadians()), std::sin(getAngleRadians()), 0.0); }
			/// <summary>
			/// ������������� ���� �������������� ������� �����������
			/// </summary>
			void setAngleFromDirectVector(const Vector3D &vectorDirect) { setAngleRadians(std::atan2(vectorDirect.vy(), vectorDirect.vx())); }

			/// <summary>
			/// ���������� ������ ����������� ����� �� �������� (�� 90 �������� ������ ������� �������)
			/// </summary>
			Vector3D getUpVector() const { return Vector3D(-std::sin(getAngleRadians()), std::cos(getAngleRadians()), 0.0f); }
			/// <summary>
			/// ���������� ������ ����������� ���� �� �������� (�� 90 �������� �� ������� �������)
			/// </summary>
			Vector3D getDownVector() const { return -getUpVector(); }

			///<summary>
			///������� �������� �����
			///</summary>
			MR::Helpers::DoublePreciseApproximate::AccuracyType getAccuracyType() const { return angleDegree.getAccuracyType(); }
			///<summary>
			///������ �������� �����
			///</summary>
			void setAccuracyType(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType) { angleDegree.setAccuracyType(accuracyType); }
			///������� ����������� �����
			///</summary>
			double getEpsilon() const { return angleDegree.getEpsilon(); }
			///<summary>
			///������ ����������� �����
			///</summary>
			void setEpsilon(double epsilon) { angleDegree.setEpsilon(epsilon); }

			Angle2D &operator = (const Angle2D &right);
			Angle2D operator +(const Angle2D &right) const;
			Angle2D operator -(const Angle2D &right) const;
			Angle2D operator *(double right) const;
			Angle2D operator /(double right) const;

			const bool operator ==(const Angle2D &right) const;
			const bool operator !=(const Angle2D &right) const;
			const bool operator <(const Angle2D &right) const;
			const bool operator >(const Angle2D &right) const;
			const bool operator <=(const Angle2D &right) const;
			const bool operator >=(const Angle2D &right) const;
		private:
			MR::Helpers::DoublePreciseApproximate angleDegree;
		};
	}
}