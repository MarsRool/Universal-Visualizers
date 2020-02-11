#include "stdafx.h"
#include "MR_Angle2D.h"

MR::Geometry::Angle2D::Angle2D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType)
{
	angleDegree = MR::Helpers::DoublePreciseApproximate(0.0, smallV, accuracyType);
}

MR::Geometry::Angle2D::Angle2D(const Angle2D & other)
{
	setAngleDegree(other.getAngleDegree());
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

MR::Geometry::Angle2D MR::Geometry::Angle2D::operator*(double right) const
{
	return Angle2D(this->angleDegree * right);
}

MR::Geometry::Angle2D MR::Geometry::Angle2D::operator/(double right) const
{
	return Angle2D(this->angleDegree / right);
}

const bool MR::Geometry::Angle2D::operator==(const Angle2D & right) const
{
	return this->angleDegree == right.angleDegree;
}

const bool MR::Geometry::Angle2D::operator!=(const Angle2D & right) const
{
	return this->angleDegree != right.angleDegree;
}

const bool MR::Geometry::Angle2D::operator<(const Angle2D & right) const
{
	return this->angleDegree < right.angleDegree;
}

const bool MR::Geometry::Angle2D::operator>(const Angle2D & right) const
{
	return this->angleDegree > right.angleDegree;
}

const bool MR::Geometry::Angle2D::operator<=(const Angle2D & right) const
{
	return this->angleDegree <= right.angleDegree;
}

const bool MR::Geometry::Angle2D::operator>=(const Angle2D & right) const
{
	return this->angleDegree >= right.angleDegree;
}
