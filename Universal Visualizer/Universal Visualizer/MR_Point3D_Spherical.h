#pragma once
#include "stdafx.h"
#include "MR_Angle3D.h"

namespace MR
{
	namespace Geometry
	{
		class Point3DCartesian;
		///<summary>
		///MR 3D точка
		///</summary>
		class Point3DSpherical : public Angle3D
		{
		public:
			Point3DSpherical();
			Point3DSpherical(const MR::Helpers::DoublePreciseApproximate &R, const Angle2D &Phi, const Angle2D &Theta);
			Point3DSpherical(const MR::Helpers::DoublePreciseApproximate &R, const Angle3D &angle);
			Point3DSpherical(const Point3DSpherical &PointToCopy);
			~Point3DSpherical() {}//пустой деструктор.

			friend bool equalPoints(const Point3DSpherical *point_left, const Point3DSpherical *point_right);
			bool operator == (const Point3DSpherical &point_right) const { return equalPoints(this, &point_right); }
			Point3DSpherical &operator = (const Point3DSpherical &point_right);
			Point3DSpherical operator + (const Point3DSpherical &point_right) const;
			Point3DSpherical operator - (const Point3DSpherical &point_right) const;
			///<summary>
			///увеличивает кол-во вхождений в ребра
			///</summary>
			Point3DSpherical &operator ++ ();
			///<summary>
			///уменьшает кол-во вхождений в ребра
			///</summary>
			Point3DSpherical &operator -- ();
			Point3DSpherical &operator += (int added);

			///<summary>
			///true- если количество ребер, которые содержат точку, больше 0.
			///</summary>
			bool existing() const { return CountIncludingInEdges; }
			int getCountIncludingInEdges() const { return CountIncludingInEdges; }

			const MR::Helpers::DoublePreciseApproximate &getR() const { return R; }
			void setR(double R) { this->R = R; }
			void setR(MR::Helpers::DoublePreciseApproximate R) { this->R = R; }
			void set(MR::Helpers::DoublePreciseApproximate R, const Angle2D &Phi, const Angle2D &Theta) { setR(R); setPhi(Phi); setTheta(Theta); }
			void get(MR::Helpers::DoublePreciseApproximate &R, Angle2D &Phi, Angle2D &Theta) const { R = getR(); Phi = getPhi(); Theta = getTheta(); }

			friend Point3DSpherical *searchPoint(const std::list<Point3DSpherical*> &Points, Point3DSpherical *Point_key);//находит адрес адреса точки в массиве точек

			///<summary>
			///вычисляет расстояние между точками в сферическом пространстве.
			///лучше не использовать, так как вызывает дважды метод toCartesian() - для себя и point
			///</summary>
			double distance(const Point3DSpherical &point) const;
			static Point3DSpherical getMiddlePoint(const Point3DSpherical &point1, const Point3DSpherical &point2);
			Point3DSpherical getMiddlePoint(const Point3DSpherical &point) { return getMiddlePoint(*this, point); }
			Point3DCartesian toCartesian() const;
		private:
			bool check();

			MR::Helpers::DoublePreciseApproximate R;
			///<summary>
			///количество ребер, которые содержат точку. добавляется при формировании модели на этапе формирования массива ребер. Сначала равна 0.
			///</summary>
			int CountIncludingInEdges = 0;
		};
	}
}