#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_Face.h"
#include "graph.h"
//все классы построены таким образом, чтобы на момент их создания/изменения, все параметры автоматически рассчитывались
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
		///MR объект.
		///Алгоритм - формирование объектов, потом проверка элементов на дубли и удаление неиспользующихся элементов.
		///Object - владелец памяти Points, Edges и Points. Только он может выделять и удалять память.
		///</summary>
		class Object
		{
		public:
			///<summary>
			///Создание пустого объекта
			///</summary>
			Object();
			///<summary>
			///нельзя просто так добавить любые три массива. условие: ребра должны быть построены на гранях.
			///</summary>
			Object(const std::list<Face*> &Faces_i, string name = "");
			Object(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i, string name = "");//создание объекта из уже инициализированных массивов
			///<summary>
			///создает полную копию объекта
			///</summary>
			Object(const Object &objectToCopy);
			~Object();

			///<summary>
			///true- если пустой объект
			///</summary>
			bool isEmpty();

			Geometry::Point3DCartesian getPos() const;
			void setPos(Geometry::Point3DCartesian *pointIn);

			string getStrName() const;
			void setStrName(string strIn);
			void getFaces(std::list<Face*> &Faces_out) const { Faces_out = Faces; }

			void drawObject();

			///<summary>
			///создает полную копию объекта
			///</summary>
			virtual Object& operator = (const Object &objToCopy);

			static void uniquePoints(std::list<Geometry::Point3DCartesian*> &list);
			static void uniqueEdges(std::list<Edge*> &list);

		protected:
			bool check() const;
			///<summary>
			///Проверка всех граней на принадлежность одной плоскости
			///</summary>
			bool isAllFacesInOnePlane() const;
			///<summary>
			///Полное очищение памяти и приведение объекта к нулевому содержанию.
			///</summary>
			void clearData();
			///<summary>
			///Очищение несуществующих элементов
			///</summary>
			void clearNonexistent();
			///<summary>
			///создает полную копию объекта с независимыми тремя множествами! То есть создает отдельное независимое пространство адресов
			///</summary>
			void CopyUnique(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i);
			///<summary>
			///перемещает данные трех множеств в текущий объект, при этом исходный objectToCopy становится пустым
			///</summary>
			void ReplaceNotUnique(Object &objectToCopy);
			///<summary>
			///удаление неиспользуемых элементов элементов для их однозначности
			///</summary>
			void deleteNotUsedElements();

			void clearSelection();
			///<summary>
			///выделить эту грань и все с ней смежные
			///</summary>
			void selectFaces(Face* face);
			///<summary>
			///выделить эту грань и все с ней смежные из массива граней
			///</summary>
			void selectFaces(Face* face, const std::list<Face*> &Faces);

			double counticolor(double a, double b, double c, int k);

			///<summary>
			/// Точки объекта
			///</summary>
			std::list<Geometry::Point3DCartesian*> Points;
			///<summary>
			/// Ребра объекта
			///</summary>
			std::list<Edge*> Edges;
			///<summary>
			/// Грани объекта
			///</summary>
			std::list<Face*> Faces;
			///<summary>
			/// Имя обьекта
			///</summary>
			string StrName = "";

			///<summary>
			///позиция объекта
			///</summary>
			Geometry::Point3DCartesian Position;

			///<summary>
			///раскрашивание объекта
			///</summary>
			short int TypeColor = 3;/*тип раскраски функции.
			1 - разными цветами каждую функцию(монотонно)
				2 - разными цветами каждую функцию(градиентно)
				3 - раскраска 4 цветами от dl, dr, ul, ur.
				4 - ландшафт.*/
				///<summary>
				///стандартный(монотонный) цвет функции
				///</summary>
			RGB_MR Color;
			///<summary>
			///градиентный цвет downleft, downright, upleft, upright colors (от 0.0 до 1.0)
			///</summary>
			RGB_MR ColorGrad[4];
			///<summary>
			///ландшафт. по второй схеме. радуга от красного до фиолетового сверху вниз.
			///</summary>
			RGB_MR ColorGradLand[7];
		};
	}
}
