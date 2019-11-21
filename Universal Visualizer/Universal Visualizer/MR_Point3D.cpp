#include "stdafx.h"
#include "MR_Point3D.h"
#include "global.h"

MR::Geometry::Point3D::Point3D()
{
	set(0.0, 0.0, 0.0);
}

MR::Geometry::Point3D::Point3D(double X_i, double Y_i, double Z_i)
{
	set(X_i, Y_i, Z_i);
	if (!check())
		throw std::exception("Wrong Point");
}

MR::Geometry::Point3D::Point3D(const Point3D & PointToCopy)
{
	set(PointToCopy.X, PointToCopy.Y, PointToCopy.Z);
	if (!check())
		throw std::exception("Wrong Point");
}

bool MR::Geometry::equalPoints(const Point3D *point_left, const Point3D *point_right)
{
	return (point_left->X == point_right->X && point_left->Y == point_right->Y && point_left->Z == point_right->Z);
}

const bool MR::Geometry::Point3D::operator==(const Point3D &point_right)
{
	int test = 0;
	bool result = equalPoints(this, &point_right);
	if (this->x() < 0 && this->y() < 0 && this->z() > 0)
		test = 5;
	if (result)
		test = 1;
	return result;
}

MR::Geometry::Point3D &MR::Geometry::Point3D::operator=(const Point3D & point_right)
{
	if (&point_right == this)
		return *this;
	set(point_right.X, point_right.Y, point_right.Z);
	if (!check())
		throw std::exception("Wrong Point");
	return *this;
}

MR::Geometry::Point3D MR::Geometry::Point3D::operator+(const Point3D & point_right) const
{
	return Point3D(this->X + point_right.X, this->Y + point_right.Y, this->Z + point_right.Z);
}

MR::Geometry::Point3D MR::Geometry::Point3D::operator-(const Point3D & point_right) const
{
	return Point3D(this->X - point_right.X, this->Y - point_right.Y, this->Z - point_right.Z);
}

MR::Geometry::Point3D &MR::Geometry::Point3D::operator++()
{
	CountIncludingInEdges++;
	return *this;
}

MR::Geometry::Point3D &MR::Geometry::Point3D::operator--()
{
	CountIncludingInEdges--;
	return *this;
}

MR::Geometry::Point3D &MR::Geometry::Point3D::operator+=(short int added)
{
	this->CountIncludingInEdges += added;
	return *this;
}

void MR::Geometry::Point3D::set(double X_i, double Y_i, double Z_i)
{
	X = X_i;
	Y = Y_i;
	Z = Z_i;
}

void MR::Geometry::Point3D::get(double & X_i, double & Y_i, double & Z_i)
{
	X_i = X;
	Y_i = Y;
	Z_i = Z;
}

MR::Geometry::Point3D *MR::Geometry::searchPoint(const std::list<Point3D*> &Points, Point3D *Point_key)
{
	for (std::list<Point3D*>::const_iterator iter = Points.cbegin(); iter != Points.cend(); iter++)
		if (*iter != nullptr && Point_key != nullptr)
			if (**iter == *Point_key)
				return *iter;
	return nullptr;
}

double MR::Geometry::Point3D::distance(const Point3D & point) const
{
	return sqrt(pow(this->x() - point.x(), 2) + pow(this->y() - point.y(), 2) + pow(this->z() - point.z(), 2));
}

MR::Geometry::Point3D MR::Geometry::Point3D::getMiddlePoint(const Point3D & point1, const Point3D & point2)
{
	return Point3D((point1.x() + point2.x()) / 2.0, (point1.y() + point2.y()) / 2.0, (point1.z() + point2.z()) / 2.0);
}

bool MR::Geometry::Point3D::check()
{
	if (std::abs(X) > bigV || std::abs(Y) > bigV || std::abs(Z) > bigV)
		return false;
	return true;
}