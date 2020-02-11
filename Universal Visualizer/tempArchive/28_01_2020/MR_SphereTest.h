#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Model.h"
#include "MR_Basis3D.h"
#include "MR_Sector3D.h"
#include "MR_Plane3D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///Класс для тестирования нахождения точки внутри или снаружи объекта или модели (совокупности объектов)
		///<summary>
		class SphereTest
		{
		public:
			///<summary>
			///Создание теста точки для модели
			///<summary>
			SphereTest(const MR::Model::Model &model, const Geometry::Point3D &point, double radius = smallV);
			///<summary>
			///true- если точка внутри
			///<summary>
			bool isInside() { return IsInside; }
			///<summary>
			///true- если точка снаружи
			///<summary>
			bool isOutside() { return (!isInside()); }
			/*///<summary>
			///!!!Продумать. Вернуть объект, в который входит точка. Если точка снаружи, результат nullptr
			///<summary>
			MR::Model::Object *getIncludingObject();*/
		private:
			///<summary>
			///проверка на корректность SphereTest
			///<summary>
			bool check();
			///<summary>
			///проверка на пересечение сферой модели. true- если пересекает и значит тест неверный.
			///<summary>
			bool isSphereIntersectModel();
			///<summary>
			///Тест точки на вхождение в модель
			///<summary>
			void test();
			///<summary>
			///Радиус тестирующей сферы
			///<summary>
			double Radius = smallV;
			///<summary>
			///Тестовая модель, относительно которой определяют нахождение точки
			///</summary>
			const MR::Model::Model TestModel;
			///<summary>
			///Тестируемая точка
			///</summary>
			const Geometry::Point3D TestPoint;
			///<summary>
			///true- если точка внутри. По умолчанию, она снаружи
			///<summary>
			bool IsInside = false;
			///<summary>
			///true- если тест корректный.
			///<summary>
			bool isOk;
			/*///<summary>
			///!!!Продумать. Объекты, в которые входит точка
			///<summary>
			list<MR::Model::Object*> IncludingObjects;*/
		};
	}
}