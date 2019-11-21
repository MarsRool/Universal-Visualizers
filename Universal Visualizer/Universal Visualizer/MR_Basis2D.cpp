#include "stdafx.h"
#include "MR_Basis2D.h"

MR::Geometry::Basis2D::Basis2D(const Vector3D & vec1, const Vector3D & vec2)
{
	Ex = vec1; Ex.normalize();
	Ey = vec2 - Ex * scalarProduct(vec2, Ex) / scalarProduct(Ex, Ex); Ey.normalize();
}

double MR::Geometry::Basis2D::getAngleRad_0To2Pi(const Vector3D &vec, bool &isOk) const
{
	isOk = isVectorsInPlane(vec);
	double angle = Ex.getAngleRad(vec);
	if (Ey.getAngleRad(vec) > (PI / 2))	//если угол между вертикалью больше 90 градусов,
		angle = 2 * PI - angle;			//то угол отражается по горизонтали
	return angle;
}

double MR::Geometry::Basis2D::getAngleRad_NegPiToPi(const Vector3D &vec, bool &isOk) const
{
	double angle = getAngleRad_0To2Pi(vec, isOk);
	if (angle > PI)		//если угол больше Pi,
		angle -= 2 * PI;//то вычитаем 2Pi
	return angle;
}

double MR::Geometry::Basis2D::getAngleRad_0ToPi(const Vector3D &left, const Vector3D &right, bool &isOk) const
{
	return left.getAngleRad(right);
}

double MR::Geometry::Basis2D::getAngleRad_0To2Pi(const Vector3D &left, const Vector3D &right, bool &isOk) const
{
	bool isOk1, isOk2;
	double angleLeft = getAngleRad_0To2Pi(left, isOk1);
	double angleRight = getAngleRad_0To2Pi(right, isOk2);
	isOk = isOk1 && isOk2;
	double angle = angleLeft - angleRight;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return angle;
}

double MR::Geometry::Basis2D::getAngleRad_NegPiToPi(const Vector3D &left, const Vector3D &right, bool &isOk) const
{
	double angle = getAngleRad_0To2Pi(left, right, isOk);
	if (angle > PI)		//если угол больше Pi,
		angle -= 2 * PI;//то вычитаем 2Pi
	return angle;
}

bool MR::Geometry::Basis2D::isVectorsInPlane(const Vector3D &vec) const
{
	return (Ex.mixedProduct(Ey, vec) < smallV);
}
