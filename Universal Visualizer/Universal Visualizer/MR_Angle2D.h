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
		/// Класс, представляющий собой угол на плоскости
		/// </summary>
		class Angle2D
		{
		public:
			/// <summary>
			/// Degrees - угол в градусах.
			/// Radians - угол в радианах.
			/// </summary>
			enum AngleType { Degrees, Radians };
			/// <summary>
			/// Создает нулевой угол
			/// </summary>
			/// <param name="accuracyType">точные или приближительные расчеты</param>
			Angle2D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// Создает копию угла
			/// </summary>
			/// <param name="other">копируемый другой угол</param>
			Angle2D(const Angle2D &other);
			/// <summary>
			/// Создает угол из angle в зависимости от системы исчисления
			/// </summary>
			/// <param name="angle">значение угла</param>
			/// <param name="angleType">градусы или радианы</param>
			/// <param name="accuracyType">точные или приближительные расчеты</param>
			Angle2D(double angle, AngleType angleType = AngleType::Degrees,
				MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// Создает угол из angle в зависимости от системы исчисления
			/// </summary>
			/// <param name="angle">значение угла</param>
			/// <param name="angleType">градусы или радианы</param>
			/// <param name="accuracyType">точные или приближительные расчеты</param>
			Angle2D(const MR::Helpers::DoublePreciseApproximate &angle, AngleType angleType = AngleType::Degrees);
			/// <summary>
			/// Создает угол из вектора
			/// </summary>
			/// <param name="vector">направляющий вектор</param>
			/// <param name="accuracyType">точные или приближительные расчеты</param>
			Angle2D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
				MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			~Angle2D() {}

			/// <summary>
			/// Возвращает угол в градусах.
			/// </summary>
			double getAngleDegree() const { return angleDegree(); }
			/// <summary>
			/// Устанавливает угол в градусах.
			/// </summary>
			void setAngleDegree(double angleDegree) { this->angleDegree = MR::Helpers::Math::ValueToDiapazon(angleDegree, 0, 360); }

			/// <summary>
			/// Возвращает угол в радианах.
			/// </summary>
			double getAngleRadians() const { return MR::Helpers::Math::DegreesToRadians(getAngleDegree()); }
			/// <summary>
			/// Устанавливает угол в радианах.
			/// </summary>
			void setAngleRadians(double angleRadians) { setAngleDegree(MR::Helpers::Math::RadiansToDegrees(angleRadians)); }

			/// <summary>
			/// Возвращает вектор направления соответственно углу
			/// </summary>
			Vector3D getDirectVector() const { return Vector3D(std::cos(getAngleRadians()), std::sin(getAngleRadians()), 0.0); }
			/// <summary>
			/// Устанавливает угол соответственно вектору направления
			/// </summary>
			void setAngleFromDirectVector(const Vector3D &vectorDirect) { setAngleRadians(std::atan2(vectorDirect.vy(), vectorDirect.vx())); }

			/// <summary>
			/// Возвращает вектор направления вверх от текущего (на 90 градусов против часовой стрелки)
			/// </summary>
			Vector3D getUpVector() const { return Vector3D(-std::sin(getAngleRadians()), std::cos(getAngleRadians()), 0.0f); }
			/// <summary>
			/// Возвращает вектор направления вниз от текущего (на 90 градусов по часовой стрелке)
			/// </summary>
			Vector3D getDownVector() const { return -getUpVector(); }

			///<summary>
			///вернуть точность числа
			///</summary>
			MR::Helpers::DoublePreciseApproximate::AccuracyType getAccuracyType() const { return angleDegree.getAccuracyType(); }
			///<summary>
			///задать точность числа
			///</summary>
			void setAccuracyType(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType) { angleDegree.setAccuracyType(accuracyType); }
			///вернуть погрешность числа
			///</summary>
			double getEpsilon() const { return angleDegree.getEpsilon(); }
			///<summary>
			///задать погрешность числа
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