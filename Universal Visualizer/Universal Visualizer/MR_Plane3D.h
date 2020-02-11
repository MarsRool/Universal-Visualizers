#pragma once
#include "MR_Line3D.h"

namespace MR
{
	namespace Model
	{
		class Face;
	}
	namespace Geometry
	{
		class Plane3D
		{
		public:
			Plane3D(const Vector3D &Normal_i, const Point3DCartesian &Point_i);//������ ������� � ����� �� ���������
			Plane3D(const Vector3D &Vector1, const Vector3D &Vector2, const Point3DCartesian &Point_i);//��� �������, ������������ ��������� � �����.
			Plane3D(const Point3DCartesian &Point1, const Point3DCartesian &Point2, const Point3DCartesian &Point3);//��� ����� �� ���������
			Plane3D(const Model::Face &face);
			Plane3D(const Plane3D &planeToCopy);
			~Plane3D();

			Vector3D getNormal() const { return Normal; }
			bool operator==(const Plane3D &plane);
			bool operator!=(const Plane3D &plane) { return !(operator==(plane)); }
			
			double distance(const Point3DCartesian &Point_i) const;
			///<summary>
			///���������� ��� ��������� �����: 
			///1 - �������, 0 - �� ���������, -1 - ������ ���������
			///</summary>
			short int whereIsPoint(const Point3DCartesian &Point_i) const;
			///<summary>
			///true- ���� ����� ��������� � ����� �������� �� ���������
			///</summary>
			bool istDotsInBothSides(const std::list<Point3DCartesian*> &Points) const;

			bool isInPlane(const Point3DCartesian &point);
			bool isInPlane(const Line3D &line);
		private:
			///<summary>
			///������� ���������
			///<summary>
			Vector3D Normal;
			///<summary>
			///�����, ����� ������� �������� ���������
			///<summary>
			Point3DCartesian Point;
		};
	}
}
