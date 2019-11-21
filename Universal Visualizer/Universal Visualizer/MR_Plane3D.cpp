#include "stdafx.h"
#include "MR_Plane3D.h"
#include "global.h"

MR::Geometry::Plane3D::Plane3D(const Vector3D &Normal_i, const Point3D &Point_i)
{
	Normal = Normal_i;
	Point = Point_i;
	Normal.normalize();
}

MR::Geometry::Plane3D::Plane3D(const Vector3D &Vector1, const Vector3D &Vector2, const Point3D &Point_i)
{
	Normal = vectorProduct(Vector1, Vector2);
	Point = Point_i;
	Normal.normalize();
}

MR::Geometry::Plane3D::Plane3D(const Point3D &Point1, const Point3D &Point2, const Point3D &Point3)
{
	Normal = vectorProduct(Vector3D(Point1, Point2), Vector3D(Point1, Point3));
	Point = Point1;
	Normal.normalize();
}

MR::Geometry::Plane3D::Plane3D(const Plane3D & planeToCopy)
{
	this->Normal = planeToCopy.Normal;
	this->Point = planeToCopy.Point;
}

MR::Geometry::Plane3D::~Plane3D()
{
}

double MR::Geometry::Plane3D::distance(const Point3D &Point_i) const
{
	double D = -(Normal.vx() * Point.x()) - (Normal.vy() * Point.y()) - (Normal.vz() * Point.z());
	return ((std::abs((Normal.vx() * Point_i.x()) +
		(Normal.vy() * Point_i.y()) +
		(Normal.vz() * Point_i.z()) + D)) /
		Normal.getLength());
}

short int MR::Geometry::Plane3D::whereIsPoint(const Point3D &Point_i) const
{//1 - снаружи, 0 - на плоскости, -1 - внутри плоскости
	double result;
	double D = -(Normal.vx() * Point.x()) - (Normal.vy() * Point.y()) - (Normal.vz() * Point.z());
	result = ((Normal.vx() * Point_i.x()) +
		(Normal.vy() * Point_i.y()) +
		(Normal.vz() * Point_i.z()) + D);
	if (std::abs(result) < smallV)
		return 0;
	else if (result > 0)
		return 1;
	else if (result < 0)
		return -1;
	return 0;
}

bool MR::Geometry::Plane3D::istDotsInBothSides(const std::list<Point3D*> &Points) const
{
	bool ist_outside = false, ist_inside = false;
	for (Point3D *p: Points)
		if (ist_outside && ist_inside)
			break;
		else
		{
			if (whereIsPoint(*p) == -1)//inside
				ist_inside = true;
			if (whereIsPoint(*p) == 1)
				ist_outside = true;
		}
	return (ist_outside && ist_inside);
}

bool MR::Geometry::Plane3D::isInPlane(const Point3D & point)
{
	return (distance(point) < smallV);
}

bool MR::Geometry::Plane3D::isInPlane(const Line3D & line)
{
	return ((distance(line.getPoint()) < smallV) && (distance(line.getPoint() + Point3D(1.0, 1.0, 1.0)) < smallV));
}

bool MR::Geometry::Plane3D::operator==(const Plane3D & plane)
{
	return ((parallelAproximately(this->Normal,plane.Normal) == true) &&
		(this->distance(plane.Point) < smallV));
}
