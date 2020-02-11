#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///класс сектора сферы в пространстве, описываемый с помощью множества последовательно связанных точек на единичной сфере
		///</summary>
		class Sector3D
		{
		public:
			Sector3D(double angle1, double angle2, double angleMiddle);

			//bool isZero(); - доработка возможна, когда будет разработана возможность рассчитывать площадь геом.фигуры, чтобы оценить площадь и телесный угол как отношение площади к радиусу
			//bool isFullCircle(); - аналогично
			bool isSectorIntersect(const Sector3D &sec) const;

			static bool compareSectors(const Sector3D *a, const Sector3D *b);
			///<summary>
			///объединяет два сектора, если это возможно, иначе возвращает nullptr
			///</summary>
			static Sector3D *integrateSectors(const Sector3D &sec1, const Sector3D &sec2);
			///<summary>
			///объединяет отсортированные секторы
			///</summary>
			static void integrateSectors(std::list<Sector3D*> &sectors);
			///<summary>
			///сортировка списка секторов по возрастанию angle1
			///</summary>
			static void sortSectors(std::list<Sector3D*> &sectors);
		private:
			void correct(double angleMiddle);
			bool check();
			double angle1, angle2;
		};
	}
}