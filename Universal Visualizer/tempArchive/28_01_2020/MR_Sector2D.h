#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///класс сектора круга/окружности на плоскости, описываемый с помощью двух углов:
		///angle1 < angle2 и angle2 < 2*PI
		///</summary>
		class Sector2D
		{
		public:
			///<summary>
			///создает сектор круга/окружности по двум точкам и точке между ними для однозначности
			///</summary>
			Sector2D(double angle1, double angle2, double angleMiddle);

			///<summary>
			///true- если сектор равен нулю (приблизительно)
			///</summary>
			bool isZero();
			///<summary>
			///true- если сектор равен полному кругу (приблизительно)
			///</summary>
			bool isFullCircle();
			///<summary>
			///true- если сектор пересекает другой сектор или смежен с ним.
			///для того, чтобы определить, можно ли их объединять.
			///</summary>
			bool isSectorIntersect(const Sector2D &sec) const;

			static bool compareSectors(const Sector2D *a, const Sector2D *b);
			///<summary>
			///объединяет два сектора, если это возможно, иначе возвращает nullptr
			///</summary>
			static Sector2D *integrateSectors(const Sector2D &sec1, const Sector2D &sec2);
			///<summary>
			///объединяет отсортированные секторы
			///</summary>
			static void integrateSectors(std::list<Sector2D*> &sectors);
			///<summary>
			///сортировка списка секторов по возрастанию angle1
			///</summary>
			static void sortSectors(std::list<Sector2D*> &sectors);
		private:
			void correct(double angleMiddle);
			bool check();
			double angle1, angle2;
		};
	}
}