#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Angle3D.h"
#include "MR_Face.h"

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
			///<summary>
			///создает сектор сферы из (замкнутой) геометрической фигуры
			///</summary>
			Sector3D(const MR::Model::Face &face, const Point3DCartesian &centerSphere);
			///<summary>
			///создает копию сектора сферы
			///</summary>
			Sector3D(const Sector3D &other);

			///<summary>
			///true- если сектор не содержит углов или заполняет сферу полностью
			///</summary>
			bool isFullSphereOrEmpty() { return (angles.size() == 0); }
			//bool isZero(); - доработка возможна, когда будет разработана возможность рассчитывать площадь геом.фигуры, чтобы оценить площадь и телесный угол как отношение площади к радиусу
			//bool isFullCircle(); - аналогично
			///<summary>
			///true- если сектор пересекает другой сектор.
			///</summary>
			bool isSectorIntersect(const Sector3D &sec) const;
			///<summary>
			///true- если сектор касается другого сектора (смежен с ним).
			///т.е. имеет как минимум 2 общие граничные точки.
			///для того, чтобы определить, можно ли их объединять.
			///</summary>
			bool isSectorTangential(const Sector3D &sec) const;

			///<summary>
			///объединяет два сектора, если это возможно, иначе возвращает nullptr
			///</summary>
			static Sector3D *integrateSectors(const Sector3D &sec1, const Sector3D &sec2);
			///<summary>
			///объединяет секторы. изменяет sectors
			///</summary>
			static void integrateSectors(std::list<Sector3D*> &sectors);
		private:
			//static void dividePath(const std::list<MR::Geometry::Point3D*> &points, std::vector<std::list<MR::Geometry::Point3D*>> &pathes);
			//static void checkPath(const std::list<MR::Geometry::Point3D*> &points);
			bool check();
			void setFromPointsPath(const std::list<MR::Geometry::Point3DCartesian*> &points, const Point3DCartesian &centerSphere);
			///<summary>
			///упрощает сектор, если в нем содержатся повторяющиеся ребра
			///</summary>
			void simplify();
			std::list<Angle3D> angles;
		};
	}
}