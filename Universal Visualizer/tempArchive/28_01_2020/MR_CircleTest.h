#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Face.h"
#include "MR_Plane3D.h"
#include "MR_Basis2D.h"
#include "MR_Sector2D.h"
//’от€ грань по умолчанию лежит в плоскости, но плоскость находитс€ в пространстве.
//—ледовательно, вс€ геометри€ все равно будет в пространстве.
//¬се вычислени€ с точностью до smallV
namespace MR
{
	namespace Geometry
	{
		///<summary>
		/// ласс дл€ тестировани€ нахождени€ точки внутри или снаружи грани.
		///<summary>
		class CircleTest
		{
		public:
			///<summary>
			///—оздание теста точки дл€ грани
			///<summary>
			CircleTest(const Model::Face &face, const Geometry::Point3D &point, double radius = smallV);
			~CircleTest();

			bool isInside() { return IsInside; }
		private:
			///<summary>
			///проверка на корректность CircleTest
			///<summary>
			bool check();
			///<summary>
			///проверка на пересечение окружностью модели. true- если пересекает и значит тест неверный.
			///<summary>
			bool isCircleIntersectFace() const;
			///<summary>
			///проверка на принадлежность точки плоскости грани. true- если принадлежит, значит все правильно.
			///<summary>
			bool isPointInFacePlane() const;
			///<summary>
			///“ест точки на вхождение в грань
			///<summary>
			void test();
			///<summary>
			///–адиус тестирующей окружности
			///<summary>
			double Radius = smallV;
			///<summary>
			///“естова€ грань, относительно которой определ€ют нахождение точки
			///</summary>
			const MR::Model::Face TestFace;
			///<summary>
			///“естируема€ точка
			///</summary>
			const Geometry::Point3D TestPoint;
			///<summary>
			///true- если точка внутри. ѕо умолчанию, она снаружи
			///<summary>
			bool IsInside = false;
			///<summary>
			///true- если тест корректный.
			///<summary>
			bool isOk;
			std::list<Sector2D*> Sectors;
		};
	}
}