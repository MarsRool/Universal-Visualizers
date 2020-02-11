#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_TestedObject.h"
#include "graph.h"
//придется проводить очистку лишних элементов: Points и Edges.
//в этом случае:
//не придется вводить новые переменные, контролирующие состояния класса
//исключатся ситуации с неопределенными состояниями, когда что-то будет неопределено, или определено неправильно, или устаревшая инфа

//Type **element содержит адрес на элемент, который должен быть создан в конструкторе и уничтожен в деструкторе
//*element содержит адрес на сам элемент. это создано с целью создать возможность управлять адресами при унификации элементов

namespace MR
{
	namespace Model
	{
		///<summary>
		///MR модель
		///</summary>
		class Model
		{
		public:
			Model();
			///<summary>
			///Создание копии модели.
			///</summary>
			///<param name ="modelToCopy">Модель</param>
			///<param name ="fullCopy">true- полная копия, false - неполная</param>
			Model(const Model &modelToCopy, bool fullCopy = true);
			///<summary>
			///только эквивалентная интерпретация
			///</summary>
			void addFrom3DModel(const t3DModel & Model);
			///<summary>
			///только эквивалентная интерпретация
			///</summary>
			void addFromGraph(const graph &Graph);
			void addObject(const Object &object);
			void drawModel();

			void getObjects(std::list<Object*> &Objects_out) const { Objects_out = Objects; }
		protected:
			std::list<Object*> Objects;
		};
	}
}