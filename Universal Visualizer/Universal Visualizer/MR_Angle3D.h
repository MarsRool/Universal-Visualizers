#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Angle2D.h"

namespace MR
{
	namespace Geometry
	{
		/// <summary>
		/// �����, �������������� ����� ���� - ���������� �� ��������� ����� � ����������� ������� ���������
		/// </summary>
		class Angle3D
		{
		public:
			/// <summary>
			/// ������� ������� 3D ���� ����������� ���������. �� = 0, ���� = 0
			/// </summary>
			/// <param name="accuracyType">������ ��� ��������������� �������</param>
			Angle3D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// ������� ����� 3D ����
			/// </summary>
			/// <param name="other">���������� ������ 3D ����</param>
			Angle3D(const Angle3D &other);
			/// <summary>
			/// ������� 3D ���� �� ����� �� � ���� ����������� ���������
			/// </summary>
			/// <param name="phi">�������, [0; 360) ��������</param>
			/// <param name="theta">������, [0; 180] ��������</param>
			Angle3D(const Angle2D &phi, const Angle2D &theta);
			/// <summary>
			/// ������� ���� �� �������
			/// </summary>
			/// <param name="vector">������������ ������</param>
			/// <param name="accuracyType">������ ��� ��������������� �������</param>
			Angle3D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			~Angle3D() {}

			/// <summary>
			/// ���������� �������.
			/// </summary>
			Angle2D getPhi() const { return phi; }
			/// <summary>
			/// ������������� �������.
			/// </summary>
			void setPhi(Angle2D phi) { this->phi = phi; }

			/// <summary>
			/// ���������� ������.
			/// </summary>
			Angle2D getTheta() const { return theta; }
			/// <summary>
			/// ������������� ������.
			/// </summary>
			void setTheta(Angle2D phi) { this->theta = theta > Angle2D(180) ? phi + Angle2D(180) : phi; }

			/// <summary>
			/// ���������� ������ ����������� �������������� ����
			/// </summary>
			Vector3D getDirectVector() const
			{
				return Vector3D(std::cos(phi.getAngleRadians()) * std::sin(theta.getAngleRadians()),
								std::sin(phi.getAngleRadians()) * std::sin(theta.getAngleRadians()),
								std::cos(theta.getAngleRadians()));
			}
			/// <summary>
			/// ������������� ���� �������������� ������� �����������
			/// </summary>
			void setAngleFromDirectVector(Vector3D vectorDirect)
			{
				vectorDirect.normalize();
				phi.setAngleFromDirectVector(vectorDirect);
				theta.setAngleRadians(std::acos(vectorDirect.vz()));
			}

			///<summary>
			///������� �������� �����
			///</summary>
			MR::Helpers::DoublePreciseApproximate::AccuracyType getAccuracyType() const { return (phi.getAccuracyType() == theta.getAccuracyType() ? phi.getAccuracyType() : MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate); }
			///<summary>
			///������ �������� �����
			///</summary>
			void setAccuracyType(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType) { phi.setAccuracyType(accuracyType); theta.setAccuracyType(accuracyType); }

			///������� ����������� �����
			///</summary>
			double getEpsilon() const { return (phi.getEpsilon() > theta.getEpsilon() ? phi.getEpsilon() : theta.getEpsilon()); }
			///<summary>
			///������ ����������� �����
			///</summary>
			void setEpsilon(double epsilon) { phi.setEpsilon(epsilon); theta.setEpsilon(epsilon); }

			Angle3D &operator = (const Angle3D &right);
			Angle3D __declspec(deprecated) operator +(const Angle3D &right) const;
			Angle3D __declspec(deprecated) operator -(const Angle3D &right) const;

			const bool operator ==(const Angle3D &right) const;
			const bool operator !=(const Angle3D &right) const;
		private:
			Angle2D phi, theta;
		};
	}
}