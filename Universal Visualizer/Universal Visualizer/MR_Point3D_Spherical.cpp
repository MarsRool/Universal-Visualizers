#include "stdafx.h"
#include "MR_Point3D_Spherical.h"
#include "MR_Point3D_Cartesian.h"
#include "global.h"

MR::Geometry::Point3DSpherical::Point3DSpherical() : Angle3D()
{
	setR(0.0);
}

MR::Geometry::Point3DSpherical::Point3DSpherical(const MR::Helpers::DoublePreciseApproximate &R, const Angle2D &Phi, const Angle2D &Theta) : Angle3D(Phi, Theta)
{
	setR(R);
	if (!check())
		throw std::exception("Wrong Spherical Point");
}

MR::Geometry::Point3DSpherical::Point3DSpherical(const MR::Helpers::DoublePreciseApproximate &R, const Angle3D &angle) : Angle3D(angle)
{
	setR(R);
	if (!check())
		throw std::exception("Wrong Spherical Point");
}

MR::Geometry::Point3DSpherical::Point3DSpherical(const Point3DSpherical & PointToCopy)
{
	set(PointToCopy.getR(), PointToCopy.getPhi(), PointToCopy.getTheta());
	if (!check())
		throw std::exception("Wrong Spherical Point");
}

bool MR::Geometry::equalPoints(const Point3DSpherical *point_left, const Point3DSpherical *point_right)
{
	return (point_left->getR() == point_right->getR() && point_left->getPhi() == point_right->getPhi() && point_left->getTheta() == point_right->getTheta());
}

MR::Geometry::Point3DSpherical &MR::Geometry::Point3DSpherical::operator=(const Point3DSpherical & point_right)
{
	if (&point_right == this)
		return *this;
	set(point_right.getR(), point_right.getPhi(), point_right.getTheta());
	if (!check())
		throw std::exception("Wrong Point");
	return *this;
}

MR::Geometry::Point3DSpherical MR::Geometry::Point3DSpherical::operator+(const Point3DSpherical & point_right) const
{
	return Point3DSpherical(this->getR() + point_right.getR(), this->getPhi() + point_right.getPhi(), this->getTheta() + point_right.getTheta());
}

MR::Geometry::Point3DSpherical MR::Geometry::Point3DSpherical::operator-(const Point3DSpherical & point_right) const
{
	return Point3DSpherical(this->getR() - point_right.getR(), this->getPhi() - point_right.getPhi(), this->getTheta() - point_right.getTheta());
}

MR::Geometry::Point3DSpherical &MR::Geometry::Point3DSpherical::operator++()
{
	CountIncludingInEdges++;
	return *this;
}

MR::Geometry::Point3DSpherical &MR::Geometry::Point3DSpherical::operator--()
{
	CountIncludingInEdges--;
	return *this;
}

MR::Geometry::Point3DSpherical &MR::Geometry::Point3DSpherical::operator+=(int added)
{
	this->CountIncludingInEdges += added;
	return *this;
}

MR::Geometry::Point3DSpherical *MR::Geometry::searchPoint(const std::list<Point3DSpherical*> &Points, Point3DSpherical *Point_key)
{
	for (std::list<Point3DSpherical*>::const_iterator iter = Points.cbegin(); iter != Points.cend(); iter++)
		if (*iter != nullptr && Point_key != nullptr)
			if (**iter == *Point_key)
				return *iter;
	return nullptr;
}

double MR::Geometry::Point3DSpherical::distance(const Point3DSpherical & point) const
{
	Point3DCartesian thisCart = this->toCartesian(), pointCart = point.toCartesian();
	return thisCart.distance(pointCart);
}

MR::Geometry::Point3DSpherical MR::Geometry::Point3DSpherical::getMiddlePoint(const Point3DSpherical & point1, const Point3DSpherical & point2)
{
	return Point3DSpherical((point1.getR() + point2.getR()) / 2.0, (point1.getPhi() + point2.getPhi()) / 2.0, (point1.getTheta() + point2.getTheta()) / 2.0);
}

MR::Geometry::Point3DCartesian MR::Geometry::Point3DSpherical::toCartesian() const
{
	return Point3DCartesian(getR().getValue()*sin(getTheta().getAngleRadians())*cos(getPhi().getAngleRadians()),
							getR().getValue()*sin(getTheta().getAngleRadians())*sin(getPhi().getAngleRadians()),
							getR().getValue()*cos(getTheta().getAngleRadians()));
}

bool MR::Geometry::Point3DSpherical::check()
{
	if (std::abs(getR().getValue()) > bigV)
		return false;
	return true;
}