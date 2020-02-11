#include "stdafx.h"
#include "MR_Angle2D.h"
#include "MR_Vector3D.h"

MR::Geometry::Angle2D::Angle2D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType)
{
	angleDegree = MR::Helpers::DoublePreciseApproximate(0.0, smallV, accuracyType);
}

MR::Geometry::Angle2D::~Angle2D()
{
}

MR::Geometry::Angle2D::Angle2D(double angle, AngleType angleType, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType)
{
	angleDegree = MR::Helpers::DoublePreciseApproximate(0.0, smallV, accuracyType);
	switch (angleType)
	{
	case AngleType::Degrees:
		setAngleDegree(angle);
		break;
	case AngleType::Radians:
		setAngleRadians(angle);
		break;
	}
}

MR::Geometry::Angle2D::Angle2D(const MR::Helpers::DoublePreciseApproximate &angle, AngleType angleType)
{
	this->angleDegree = angle;
	switch (angleType)
	{
	case AngleType::Degrees:
		setAngleDegree(angle());
		break;
	case AngleType::Radians:
		setAngleRadians(angle());
		break;
	}
}

MR::Geometry::Angle2D::Angle2D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType)
{
	setAngleFromDirectVector(vector);
}

double MR::Geometry::Angle2D::getAngleDegree() const
{
	return angleDegree();
}

void MR::Geometry::Angle2D::setAngleDegree(double angleDegree)
{
	this->angleDegree = MR::Helpers::Math::ValueToDiapazon(angleDegree, 0, 360);
}

double MR::Geometry::Angle2D::getAngleRadians() const
{
	return MR::Helpers::Math::DegreesToRadians(getAngleDegree());
}

void MR::Geometry::Angle2D::setAngleRadians(double angleRadians)
{
	setAngleDegree(MR::Helpers::Math::RadiansToDegrees(angleRadians));
}

MR::Geometry::Vector3D MR::Geometry::Angle2D::getDirectVector() const
{
	return Vector3D(std::cos(getAngleRadians()),
					std::sin(getAngleRadians()), 0.0);
}

void MR::Geometry::Angle2D::setAngleFromDirectVector(const Vector3D & vectorDirect)
{
	setAngleRadians(std::atan2(vectorDirect.vy(), vectorDirect.vx()));
}

MR::Geometry::Vector3D MR::Geometry::Angle2D::getUpVector() const
{
	return Vector3D(-std::sin(getAngleRadians()),
					std::cos(getAngleRadians()), 0.0f);
}

MR::Geometry::Vector3D MR::Geometry::Angle2D::getDownVector() const
{
	return -getUpVector();
}

MR::Geometry::Angle2D & MR::Geometry::Angle2D::operator=(const Angle2D & right)
{
	if (&right == this)
		return *this;
	angleDegree = right.angleDegree;
	return *this;
}

MR::Geometry::Angle2D MR::Geometry::Angle2D::operator+(const Angle2D & right) const
{
	return Angle2D(this->angleDegree + right.angleDegree);
}

MR::Geometry::Angle2D MR::Geometry::Angle2D::operator-(const Angle2D & right) const
{
	return Angle2D(this->angleDegree - right.angleDegree);
}

const bool MR::Geometry::Angle2D::operator==(const Angle2D & right) const
{
	return this->angleDegree == right.angleDegree;
}

const bool MR::Geometry::Angle2D::operator!=(const Angle2D & right) const
{
	return this->angleDegree != right.angleDegree;
}