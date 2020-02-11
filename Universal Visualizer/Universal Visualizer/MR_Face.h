#pragma once
#include "stdafx.h"
#include "MR_Vector3D.h"
#include "3DModel.h"
#include "MR_Edge.h"
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
		///MR грань
		///осторожно использовать конструкторы из ребер, так как это увеличивает кол-во смежных граней ребер
		class Face
		{
		public:
			Face(const std::list<Edge*> &Edges_i);
			///<summary>
			///создает неполную копию грани
			///</summary>
			Face(const Face & faceToCopy);
			///<summary>
			///при удалении грани, уменьшается кол-во смежных граней ребер.
			///</summary>
			~Face();
			//Face(std::vector<Point3D*> Points_i);//недоступно, потому что перед тем как добавить грань, сначала добавляются точки, потом ребра, а значит ребра уже есть.
			
			///<summary>
			///true- если ребра находятся в одной плоскости
			///</summary>
			static bool istEdgesInPlane(const std::list<Edge*> &Edges_i);
			void getEdges(std::list<Edge*> &Edges_out) const { Edges_out = Edges; }
			void setEdges(const std::list<Edge*> &Edges_in) { Edges = Edges_in; }
			void getPoints(std::list<Geometry::Point3DCartesian*> &Points_out) const { Points_out = Points; }
			void setEdges(const std::list<Geometry::Point3DCartesian*> &Points_in) { Points = Points_in; }
			const Geometry::Vector3D &getNormal() const { return Normal; }
			const Geometry::Point3DCartesian &getCenterOfMass() { return CenterOfMass; }
			void getPointsPath(std::list<MR::Geometry::Point3DCartesian*> &points) const;

			bool flag() const { return Flag; }
			void setFlag(bool flag_i) { Flag = flag_i; }
			bool isBoundary();

			///<summary>
			///ребра равны, если равны их точки (1==1, 2==2 || 1==2, 2==1 соответственно)
			///</summary>
			friend bool equalFaces(const Face &face_left, const Face &face_right);
			///ребра равны, если равны их точки (1==1, 2==2 || 1==2, 2==1 соответственно)
			bool operator == (const Face &face_right);
			///<summary>
			///создает неполную копию грани
			///</summary>
			Face& operator = (const Face &faceToCopy);
		private:
			bool check();

			void CopyNotUnique(const Face &faceToCopy);

			void calculateNormal();
			void calculateArea();//надо вычислить
			void calculateCenterOfMass();

			///<summary>
			///массив вершин
			///<summary>
			std::list<Geometry::Point3DCartesian*> Points;
			///<summary>
			///массив ребер
			///<summary>
			std::list<Edge*> Edges;
			///<summary>
			///нормаль
			///<summary>
			Geometry::Vector3D Normal = { 0.0, 0.0, 0.0 };
			///<summary>
			///площадь
			///<summary>
			double Area = 0;
			///<summary>
			///центр масс
			///<summary>
			Geometry::Point3DCartesian CenterOfMass;
			///<summary>
			///true- если уже участвовал в рекурсивном тесте на 3D модель
			///<summary>
			bool Flag = false;
		};
	}
}