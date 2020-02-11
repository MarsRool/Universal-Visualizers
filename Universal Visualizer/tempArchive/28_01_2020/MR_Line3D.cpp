#include "stdafx.h"
#include "MR_Line3D.h"
#include "global.h"

MR::Geometry::Line3D::Line3D()
{
}

MR::Geometry::Line3D::Line3D(const Vector3D &Direction_i, const Point3D &Point_i)
{
	Direction = Direction_i;
	Point = Point_i;
}

MR::Geometry::Line3D::Line3D(const Point3D &Point1, const Point3D &Point2)
{
	Direction.setVector(Point1, Point2);
	Point = Point1;
}

MR::Geometry::Line3D::~Line3D()
{
}

MR::Geometry::Line3D & MR::Geometry::Line3D::operator=(const Line3D & right)
{
	if (&right == this)
		return *this;
	this->Direction = right.Direction;
	this->Point = right.Point;

	return *this;
}

bool MR::Geometry::Line3D::operator==(const Line3D & right) const
{
	return ((parallelAproximately(this->Direction, right.Direction) == true) &&
		(distance(right) < smallV));
}

double MR::Geometry::Line3D::distance(const Point3D & point) const
{
	return (vectorProduct(Geometry::Vector3D(Point, point), Direction).getLength() / Direction.getLength());
}

double MR::Geometry::Line3D::distance(const Line3D & line) const
{
	if (isParallel(line))//если параллельны
	{
		return distance(Point - line.Point);
	}
	else//если скрещивающиеся
	{
		return std::abs(mixedProduct(Geometry::Vector3D(line.Point, Point), this->Direction, line.Direction) /
			vectorProduct(this->Direction, line.Direction).getLength());
	}
}

MR::Geometry::Point3D MR::Geometry::Line3D::calculateX(double x) const
{
	return calculateT((x - Point.x()) / Direction.vx());
}

MR::Geometry::Point3D MR::Geometry::Line3D::calculateY(double y) const
{
	return calculateT((y - Point.y()) / Direction.vy());
}

MR::Geometry::Point3D MR::Geometry::Line3D::calculateZ(double z) const
{
	return calculateT((z - Point.z()) / Direction.vz());
}

MR::Geometry::Point3D MR::Geometry::Line3D::calculateT(double t) const
{
	return Point3D(
		t*Direction.vx() + Point.x(),
		t*Direction.vy() + Point.y(),
		t*Direction.vz() + Point.z()
	);
}

bool MR::Geometry::Line3D::isParallel(const Line3D & line) const
{
	return parallelAproximately(this->Direction, line.Direction);
}

double MR::Geometry::Line3D::getAngleRad(const Line3D & line) const
{
	return this->Direction.getAngleRad(line.Direction);
}

bool MR::Geometry::compareAproximately(const Line3D & left, const Line3D & right)
{
	if (left.isParallel(right) && left.distance(right) < smallV)
			return true;
	return false;
}

MR::Geometry::Line3D MR::Geometry::operator-(const Line3D & v)
{
	return Line3D(-v.Direction,v.Point);
}
