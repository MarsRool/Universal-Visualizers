#pragma once
#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_Model.h"
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
		///MR модель.
		///Интерпретация - добавление граней по линии пересечения, если они пересекают друг друга - дробление каждого объекта на модели.
		///Процедура общего теста: add -> getModelTested3DObjects.
		///Сама TestedModel не может быть протестирована, она лишь содержит протестированные либо нет объекты.
		///</summary>
		class TestedModel : public Model
		{
		public:
			TestedModel();
			///<summary>
			///Создание копии модели.
			///</summary>
			///<param name ="modelToCopy">Модель</param>
			///<param name ="fullCopy">true- полная копия, false - неполная</param>
			TestedModel(const TestedModel &modelToCopy, bool fullCopy = true);

			MR::Model::TestedModel* getModelTested3DObjects();
		private:
		};
	}
}