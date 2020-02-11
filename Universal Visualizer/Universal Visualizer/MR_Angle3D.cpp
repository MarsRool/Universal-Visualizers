#include "stdafx.h"
#include "MR_Angle3D.h"

MR::Geometry::Angle3D::Angle3D(MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType)
{
	phi = MR::Helpers::DoublePreciseApproximate(0.0, smallV, accuracyType);
	theta = MR::Helpers::DoublePreciseApproximate(0.0, smallV, accuracyType);
}

MR::Geometry::Angle3D::Angle3D(const Angle3D & other)
{
	this->phi = other.phi;
	this->theta = other.theta;
}

MR::Geometry::Angle3D::Angle3D(const Angle2D &phi, const Angle2D &theta)
{
	setPhi(phi);
	setTheta(theta);
}

MR::Geometry::Angle3D::Angle3D(const Vector3D &vector, MR::Helpers::DoublePreciseApproximate::AccuracyType accuracyType)
{
	setAngleFromDirectVector(vector);
}

MR::Geometry::Angle3D & MR::Geometry::Angle3D::operator=(const Angle3D & right)
{
	if (&right == this)
		return *this;
	setPhi(right.getPhi());
	setTheta(right.getTheta());
	return *this;
}

MR::Geometry::Angle3D __declspec(deprecated) MR::Geometry::Angle3D::operator+(const Angle3D & right) const
{
	return Angle3D(this->phi + right.phi, this->theta + right.theta);
}

MR::Geometry::Angle3D __declspec(deprecated) MR::Geometry::Angle3D::operator-(const Angle3D & right) const
{
	return Angle3D(this->phi - right.phi, this->theta - right.theta);
}

const bool MR::Geometry::Angle3D::operator==(const Angle3D & right) const
{
	return (this->phi == right.phi) && (this->theta == right.theta);
}

const bool MR::Geometry::Angle3D::operator!=(const Angle3D & right) const
{
	return !(*this == right);
}
