#pragma once
#include "stdafx.h"
#include "MR_Plane3D.h"
#include "3DModel.h"
#include "graph.h"
///все классы построены таким образом, чтобы на момент их создания/изменения, все параметры автоматически рассчитывались
///в этом случае:
///не придется вводить новые переменные, контролирующие состояния класса
///исключатся ситуации с неопределенными состояниями, когда что-то будет неопределено, или определено неправильно, или устаревшая инфа

///Type **element содержит адрес на элемент, который должен быть создан в конструкторе и уничтожен в деструкторе
///*element содержит адрес на сам элемент. это создано с целью создать возможность управлять адресами при унификации элементов

namespace MR
{
	namespace Model
	{
		///<summary>
		///MR ребро
		///</summary>
		class Edge
		{
		public:
			Edge(const Geometry::Point3D *Point1_i, const Geometry::Point3D *Point2_i, short int count = 0);
			///<summary>
			///создает неполную копию ребра
			///</summary>
			Edge(const Edge & edgeToCopy);
			~Edge();

			///<summary>
			///true- если количество граней, которые содержат ребро, больше 0.
			///</summary>
			bool existing() const;
			short int getCountIncludingInFaces() const { return CountIncludingInFaces; }
			void getPoints(Geometry::Point3D **Point1_i, Geometry::Point3D **Point2_i);
			Geometry::Vector3D getVector12() const;
			///<summary>
			///находит адрес адреса ребра в массиве ребер. В случае не нахождения вернет nullptr
			///</summary>
			friend Edge *searchEdge(const std::list<Edge*> &Edges, const Edge *Edge_key);
			///<summary>
			///найти общую точку всех ребер, если такая есть. В случае не нахождения вернет nullptr. Проверка по адресу!
			///</summary>
			friend Geometry::Point3D * getCommonPointInEdges(const std::list<Edge*> &Edges);

			///<summary>
			///проверка на равенство по значению
			///</summary>
			friend bool equalEdges(const Edge *point_left, const Edge *point_right);
			///<summary>
			///ребра равны, если равны их точки (1==1 && 2==2 || 1==2 && 2==1 соответственно)
			///</summary>
			const bool operator == (const Edge &edge_right) const;
			///<summary>
			///увеличивает кол-во вхождений в грани
			///</summary>
			Edge& operator ++ ();
			///<summary>
			///уменьшает кол-во вхождений в грани
			///</summary>
			Edge& operator -- ();
			///<summary>
			///увеличивает кол-во вхождений в грани на added
			///</summary>
			Edge& operator += (short int added);
			///<summary>
			///создает неполную копию ребра
			///</summary>
			Edge& operator = (const Edge &edge_right);
		private:
			bool check() const;

			void CopyNotUnique(const Geometry::Point3D *Point1_i, const Geometry::Point3D *Point2_i, short int count = 0);

			Geometry::Point3D *Point1 = nullptr, *Point2 = nullptr;
			//количество граней, которые содержат ребро. добавляется при формировании модели на этапе формирования массива граней. Сначала равна 0.
			short int CountIncludingInFaces = 0;
		};
	}
}