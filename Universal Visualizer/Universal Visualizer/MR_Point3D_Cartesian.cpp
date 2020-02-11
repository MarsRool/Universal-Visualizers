#include "stdafx.h"
#include "MR_Point3D_Cartesian.h"
#include "MR_Point3D_Spherical.h"
#include "global.h"

MR::Geometry::Point3DCartesian::Point3DCartesian()
{
	set(0.0, 0.0, 0.0);
}

MR::Geometry::Point3DCartesian::Point3DCartesian(double X_i, double Y_i, double Z_i)
{
	set(X_i, Y_i, Z_i);
	if (!check())
		throw std::exception("Wrong Cartesian Point");
}

MR::Geometry::Point3DCartesian::Point3DCartesian(const Point3DCartesian & PointToCopy)
{
	set(PointToCopy.x(), PointToCopy.y(), PointToCopy.z());
	if (!check())
		throw std::exception("Wrong Cartesian Point");
}

bool MR::Geometry::equalPoints(const Point3DCartesian *point_left, const Point3DCartesian *point_right)
{
	return (point_left->x() == point_right->x() && point_left->Y == point_right->Y && point_left->Z == point_right->Z);
}

MR::Geometry::Point3DCartesian &MR::Geometry::Point3DCartesian::operator=(const Point3DCartesian & point_right)
{
	if (&point_right == this)
		return *this;
	set(point_right.x(), point_right.y(), point_right.z());
	if (!check())
		throw std::exception("Wrong Cartesian Point");
	return *this;
}

MR::Geometry::Point3DCartesian MR::Geometry::Point3DCartesian::operator+(const Point3DCartesian & point_right) const
{
	return Point3DCartesian(this->x() + point_right.x(), this->y() + point_right.y(), this->z() + point_right.z());
}

MR::Geometry::Point3DCartesian MR::Geometry::Point3DCartesian::operator-(const Point3DCartesian & point_right) const
{
	return Point3DCartesian(this->x() - point_right.x(), this->y() - point_right.y(), this->z() - point_right.z());
}

MR::Geometry::Point3DCartesian &MR::Geometry::Point3DCartesian::operator++()
{
	CountIncludingInEdges++;
	return *this;
}

MR::Geometry::Point3DCartesian &MR::Geometry::Point3DCartesian::operator--()
{
	CountIncludingInEdges--;
	return *this;
}

MR::Geometry::Point3DCartesian &MR::Geometry::Point3DCartesian::operator+=(int added)
{
	this->CountIncludingInEdges += added;
	return *this;
}

MR::Geometry::Point3DCartesian *MR::Geometry::searchPoint(const std::list<Point3DCartesian*> &Points, Point3DCartesian *Point_key)
{
	for (std::list<Point3DCartesian*>::const_iterator iter = Points.cbegin(); iter != Points.cend(); iter++)
		if (*iter != nullptr && Point_key != nullptr)
			if (**iter == *Point_key)
				return *iter;
	return nullptr;
}

double MR::Geometry::Point3DCartesian::distance(const Point3DCartesian & point) const
{
	return sqrt(pow(this->x() - point.x(), 2) + pow(this->y() - point.y(), 2) + pow(this->z() - point.z(), 2));
}

MR::Geometry::Point3DCartesian MR::Geometry::Point3DCartesian::getMiddlePoint(const Point3DCartesian & point1, const Point3DCartesian & point2)
{
	return Point3DCartesian((point1.x() + point2.x()) / 2.0, (point1.y() + point2.y()) / 2.0, (point1.z() + point2.z()) / 2.0);
}

MR::Geometry::Point3DSpherical MR::Geometry::Point3DCartesian::toSpherical() const
{
	return Point3DSpherical(MR::Helpers::DoublePreciseApproximate(sqrt(x()*x()+y()*y()+z()*z())),
							Angle3D(Vector3D(x(),y(),z())));
}

bool MR::Geometry::Point3DCartesian::check()
{
	if (std::abs(x()) > bigV || std::abs(y()) > bigV || std::abs(z()) > bigV)
		return false;
	return true;
}