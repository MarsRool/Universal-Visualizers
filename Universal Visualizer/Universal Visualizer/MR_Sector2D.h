#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"
#include "MR_Angle2D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///класс сектора круга/окружности на плоскости, описываемый с помощью двух углов: 
		///angle1 < angle2, если дуга от angle1 до angle2(внутренняя), и 
		///angle1 > angle2, если дуга от angle2 до angle1(внешняя)
		///</summary>
		class Sector2D
		{
		public:
			///<summary>
			///создает сектор круга/окружности по двум точкам и точке между ними для однозначности
			///</summary>
			Sector2D(const Angle2D &angle1, const Angle2D &angle2, const Angle2D &angleMiddle);

			///<summary>
			///true- если сектор равен нулю (приблизительно)
			///</summary>
			bool isZero();
			///<summary>
			///true- если сектор равен полному кругу (приблизительно)
			///</summary>
			bool isFullCircle();
			///<summary>
			///true- если сектор смежен с другим сектором, т.е. пересекает или касается другого сектора
			///для того, чтобы определить, можно ли их объединять.
			///</summary>
			bool isSectorAdjacent(const Sector2D &sec) const { return (isSectorIntersect(sec) || isSectorTangential(sec)); }
			///<summary>
			///true- если сектор пересекает другой сектор.
			///</summary>
			bool isSectorIntersect(const Sector2D &sec) const;
			///<summary>
			///true- если сектор касается другого сектора (смежен с ним).
			///т.е. имеет общую(-ие) граничные точки
			///</summary>
			bool isSectorTangential(const Sector2D &sec) const;

			///<summary>
			///объединяет два сектора, если это возможно, иначе возвращает nullptr
			///</summary>
			static Sector2D *integrateSectors(const Sector2D &sec1, const Sector2D &sec2);
			///<summary>
			///объединяет секторы. изменяет sectors.
			///</summary>
			static void integrateSectors(std::list<Sector2D*> &sectors);
		private:
			///<summary>
			///конвертирует два угла в диапазон [angle1Out, angle2Out], где
			///angle2Out &lt; 360, angle1Out &lt; angle2Out,
			///-360 &lt; angle1Out &lt; 360, angle2Out - angle1Out &lt;= 360
			///</summary>
			void AngleToDegreeDiapazon(MR::Helpers::DoublePreciseApproximate &angle1Out, MR::Helpers::DoublePreciseApproximate &angle2Out) const;
			///<summary>
			///конвертирует диапазон [angle1In, angle2In] в два угла, где
			///angle2Out &lt; 360, angle1Out &lt; angle2Out,
			///-360 &lt; angle1Out &lt; 360, angle2Out - angle1Out &lt;= 360
			///</summary>
			void DegreeDiapazonToAngle(MR::Helpers::DoublePreciseApproximate angle1In, MR::Helpers::DoublePreciseApproximate angle2In);
			void correct(const Angle2D &angleMiddle);
			Angle2D angle1, angle2;
		};
	}
}