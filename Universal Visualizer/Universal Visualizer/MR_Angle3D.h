#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Angle2D.h"

namespace MR
{
	namespace Geometry
	{
		/// <summary>
		///  ласс, представл€ющий собой угол - координату на единичной сфере в сферической системе координат
		/// </summary>
		class Angle3D
		{
		public:
			/// <summary>
			/// —оздает нулевой 3D угол сферических координат. фи = 0, тета = 0
			/// </summary>
			/// <param name="accuracyType">точные или приближительные расчеты</param>
			Angle3D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// —оздает копию 3D угла
			/// </summary>
			/// <param name="other">копируемый другой 3D угол</param>
			Angle3D(const Angle3D &other);
			/// <summary>
			/// —оздает 3D угол из углов фи и тета сферических координат
			/// </summary>
			/// <param name="phi">долгота, [0; 360) градусов</param>
			/// <param name="theta">высота, [0; 180] градусов</param>
			Angle3D(const Angle2D &phi, const Angle2D &theta);
			/// <summary>
			/// —оздает угол из вектора
			/// </summary>
			/// <param name="vector">направл€ющий вектор</param>
			/// <param name="accuracyType">точные или приближительные расчеты</param>
			Angle3D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			~Angle3D() {}

			/// <summary>
			/// ¬озвращает долготу.
			/// </summary>
			Angle2D getPhi() const { return phi; }
			/// <summary>
			/// ”станавливает долготу.
			/// </summary>
			void setPhi(Angle2D phi) { this->phi = phi; }

			/// <summary>
			/// ¬озвращает широту.
			/// </summary>
			Angle2D getTheta() const { return theta; }
			/// <summary>
			/// ”станавливает широту.
			/// </summary>
			void setTheta(Angle2D phi) { this->theta = theta > Angle2D(180) ? phi + Angle2D(180) : phi; }

			/// <summary>
			/// ¬озвращает вектор направлени€ соответственно углу
			/// </summary>
			Vector3D getDirectVector() const
			{
				return Vector3D(std::cos(phi.getAngleRadians()) * std::sin(theta.getAngleRadians()),
								std::sin(phi.getAngleRadians()) * std::sin(theta.getAngleRadians()),
								std::cos(theta.getAngleRadians()));
			}
			/// <summary>
			/// ”станавливает угол соответственно вектору направлени€
			/// </summary>
			void setAngleFromDirectVector(Vector3D vectorDirect)
			{
				vectorDirect.normalize();
				phi.setAngleFromDirectVector(vectorDirect);
				theta.setAngleRadians(std::acos(vectorDirect.vz()));
			}

			///<summary>
			///вернуть точность числа
			///</summary>
			MR::Helpers::DoublePreciseApproximate::AccuracyType getAccuracyType() const { return (phi.getAccuracyType() == theta.getAccuracyType() ? phi.getAccuracyType() : MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate); }
			///<summary>
			///задать точность числа
			///</summary>
			void setAccuracyType(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType) { phi.setAccuracyType(accuracyType); theta.setAccuracyType(accuracyType); }

			///вернуть погрешность числа
			///</summary>
			double getEpsilon() const { return (phi.getEpsilon() > theta.getEpsilon() ? phi.getEpsilon() : theta.getEpsilon()); }
			///<summary>
			///задать погрешность числа
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