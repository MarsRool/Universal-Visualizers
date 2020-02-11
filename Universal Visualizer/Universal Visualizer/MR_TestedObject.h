#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_Object.h"
#include "graph.h"

namespace MR
{
	namespace Model
	{
		///<summary>
		///MR тестированный объект.
		///Наследует Object.
		///Конструкторы возвращают не протестированные обхекты.
		///Протестированные объекты возвращает только метод(экземплярный или статический) getTested3dObjects
		///</summary>
		class TestedObject : public Object
		{
		public:
			///<summary>
			///Создание пустого объекта(нет тестирования)
			///</summary>
			TestedObject();
			///<summary>
			///нельзя просто так добавить любые три массива. условие: ребра должны быть построены на гранях. (нет тестирования)
			///</summary>
			TestedObject(const std::list<Face*> &Faces_i, string name = "");
			///<summary>
			///нельзя просто так добавить любые три массива. условие: ребра должны быть построены на гранях. (нет тестирования)
			///</summary>
			TestedObject(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i, string name = "");
			///<summary>
			///создает полную копию объекта(если копируемый объект протестирован, копия считается протестированной, нет - нет)
			///</summary>
			TestedObject(const TestedObject &objectToCopy);
			~TestedObject();
			///<summary>
			///создает полную копию объекта(если копируемый объект протестирован, копия считается протестированной, нет - нет)
			///</summary>
			TestedObject& operator = (const TestedObject &objToCopy);

			///<summary>
			///Возвращает коллекцию протестированных объектов из object(статически)
			///</summary>
			static std::list<TestedObject*>* getTested3dObjects(const TestedObject &object);
			///<summary>
			///Возвращает коллекцию протестированных объектов из текущего объекта
			///</summary>
			std::list<TestedObject*>* getTested3dObjects();
			///<summary>
			///true- объект протестирован
			///</summary>
			bool isTested() { return IsTested; }

			///<summary>
			///заменяет Object на TestedObject, при этом исходный objectToCopy удаляется
			///</summary>
			static TestedObject* ToTestedObject(Object* objectToCopy);
		private:
			///<summary>
			///Тест на граничные грани, которые удаляются.
			///Возвращает из текущего объекта полный независимый объект, в котором есть одно или более геометрическое тело
			///Выделяет память под новый объект
			///</summary>
			static TestedObject* getObjCleanedBoundaryFaces(const TestedObject & object);

			///<summary>
			///Разбить текущий объект на объекты, если их несколько в данном объекте.
			///Возвращает список полных независимых разбитых объектов (объект, если он один)
			///В случае ошибки/пустой объект, вернет пустой список
			///Выделяет память под новые объекты.
			///Значение входной переменной меняется!!!
			///</summary>
			///<param name="object">
			///Значение входной переменной меняется!!!
			///</param>
			static std::list<TestedObject*>* get3DObjects(TestedObject & object);

			bool IsTested = false;
		};
	}
}