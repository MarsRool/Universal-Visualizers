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
			~Angle2D();
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
			/// <param name="vector"></param>
			Angle2D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType =
											MR::Helpers::DoublePreciseApproximate::AccuracyType::Approximate);
			/// <summary>
			/// Возвращает угол в градусах.
			/// </summary>
			double getAngleDegree() const;
			/// <summary>
			/// Устанавливает угол в градусах.
			/// </summary>
			void setAngleDegree(double angleDegree);

			/// <summary>
			/// Возвращает угол в радианах.
			/// </summary>
			double getAngleRadians() const;
			/// <summary>
			/// Устанавливает угол в радианах.
			/// </summary>
			void setAngleRadians(double angleRadians);

			/// <summary>
			/// Возвращает вектор направления соответственно углу
			/// </summary>
			Vector3D getDirectVector() const;
			/// <summary>
			/// Устанавливает угол соответственно вектору направления
			/// </summary>
			void setAngleFromDirectVector(const Vector3D &vectorDirect);

			/// <summary>
			/// Возвращает вектор направления вверх от текущего (на 90 градусов против часовой стрелки)
			/// </summary>
			Vector3D getUpVector() const;

			/// <summary>
			/// Возвращает вектор направления вниз от текущего (на 90 градусов по часовой стрелке)
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