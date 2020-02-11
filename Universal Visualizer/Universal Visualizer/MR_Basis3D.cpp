#include "stdafx.h"
#include "MR_Basis3D.h"

MR::Geometry::Basis3D::Basis3D()
{
	Ex = MR::Geometry::Vector3D(1.0, 0.0, 0.0);
	Ey = MR::Geometry::Vector3D(0.0, 1.0, 0.0);
	Ez = MR::Geometry::Vector3D(0.0, 0.0, 1.0);
}

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

void MR::Geometry::Basis3D::CartesianToSpherical(const MR::Helpers::DoublePreciseApproximate & x, const MR::Helpers::DoublePreciseApproximate & y, const MR::Helpers::DoublePreciseApproximate & z, Angle3D & spereAngle)
{
	Vector3D vec = Vector3D(x(), y(), z());
	spereAngle.setAngleFromDirectVector(vec);
}

void MR::Geometry::Basis3D::SphericalToCartesian(const Angle3D & spereAngle, MR::Helpers::DoublePreciseApproximate & x, MR::Helpers::DoublePreciseApproximate & y, MR::Helpers::DoublePreciseApproximate & z)
{
	Vector3D vec = spereAngle.getDirectVector();
	x = vec.vx(); y = vec.vy(); z = vec.vz();
}
