#include "stdafx.h"
#include "MR_Basis3D.h"

MR::Geometry::Basis3D::Basis3D(const Vector3D & vec1, const Vector3D & vec2, const Vector3D & vec3)
{
	Ex = vec1; Ex.normalize();
	Ey = vec2 - Ex * scalarProduct(vec2, Ex) / scalarProduct(Ex, Ex); Ey.normalize();
	Ez = vec3 -
		Ex * scalarProduct(vec3, Ex) / scalarProduct(Ex, Ex) -
		Ey * scalarProduct(vec3, Ey) / scalarProduct(Ey, Ey); Ez.normalize();
}

MR::Geometry::Basis3D::Basis3D(const Vector3D & vec1, const Vector3D & vec2)
{
	Ex = vec1; Ex.normalize();
	Ey = vec2 - Ex * scalarProduct(vec2, Ex) / scalarProduct(Ex, Ex); Ey.normalize();
	Ez = vectorProduct(Ex, Ey); Ez.normalize();
}

/*double MR::Geometry::Basis3D::getAngleRad_0ToPi(const Vector3D vec) const
{
	return left.getAngleRad(right);
}

double MR::Geometry::Basis3D::getAngleRad_0To2Pi(const Vector3D vec) const
{
	return std::acos(left.scalarProduct(right) / left.getLength() / right.getLength());
}

double MR::Geometry::Basis3D::getAngleRad_NegPiToPi(const Vector3D vec) const
{
	return std::acos(left.scalarProduct(right) / left.getLength() / right.getLength());
}

double MR::Geometry::Basis3D::getAngleRad_0ToPi(const Vector3D left, const Vector3D & right) const
{
	return left.getAngleRad(right);
}

double MR::Geometry::Basis3D::getAngleRad_0To2Pi(const Vector3D left, const Vector3D & right) const
{
	return std::acos(left.scalarProduct(right) / left.getLength() / right.getLength());
}

double MR::Geometry::Basis3D::getAngleRad_NegPiToPi(const Vector3D left, const Vector3D & right) const
{
	return std::acos(left.scalarProduct(right) / left.getLength() / right.getLength());
}*/