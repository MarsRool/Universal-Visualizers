#include "stdafx.h"
#include "MR_Vector3D.h"
#include "MR_Matrix.h"
#include "global.h"

MR::Geometry::Vector3D::Vector3D()
{
	setVector(0.0, 0.0, 0.0);
	if (!check())
		throw std::exception("Wrong Vector");
}

MR::Geometry::Vector3D::Vector3D(double Vx_i, double Vy_i, double Vz_i)
{
	setVector(Vx_i, Vy_i, Vz_i);
	if (!check())
		throw std::exception("Wrong Vector");
}

MR::Geometry::Vector3D::Vector3D(const Point3D &point1, const Point3D &point2)
{
	setVector(point1, point2);
	if (!check())
		throw std::exception("Wrong Vector");
}

MR::Geometry::Vector3D::Vector3D(const Vector3D & vectorToCopy)
{
	setVector(vectorToCopy.Vx, vectorToCopy.Vy, vectorToCopy.Vz);
	if (!check())
		throw std::exception("Wrong Vector");
}

MR::Geometry::Vector3D::~Vector3D()
{
}

void MR::Geometry::Vector3D::setVector(const Point3D &point1, const Point3D &point2)
{
	Point3D delta = point2 - point1;
	setVector(delta.x(), delta.y(), delta.z());
}

void MR::Geometry::Vector3D::setVector(double Vx_i, double Vy_i, double Vz_i)
{
	Vx = Vx_i;
	Vy = Vy_i;
	Vz = Vz_i;
	calculateLength();
}

void MR::Geometry::Vector3D::getVector(double & Vx_i, double & Vy_i, double & Vz_i) const
{
	Vx_i = Vx;
	Vy_i = Vy;
	Vz_i = Vz;
}

double MR::Geometry::Vector3D::getLength() const
{
	return Length;
}

bool MR::Geometry::Vector3D::istZero()
{
	return ((Vx == 0 && Vy == 0 && Vx == 0 && Length == 0) ? true : false);
}

void MR::Geometry::Vector3D::normalize()
{
	calculateLength();
	if (Length != 0)
	{
		Vx /= Length;
		Vy /= Length;
		Vz /= Length;
		Length = 1;
	}
}

bool MR::Geometry::parallelAproximately(const Vector3D & left, const Vector3D & right)
{
	return (compareAproximately(left, right) || compareAproximately(-left, right));
}

bool MR::Geometry::compareAproximately(const Vector3D & left, const Vector3D & right)
{
	return ((std::abs(left.Vx - right.Vx) < smallV) &&
		(std::abs(left.Vy - right.Vy) < smallV) &&
		(std::abs(left.Vz - right.Vz) < smallV)) ? true : false;
}

MR::Geometry::Vector3D MR::Geometry::operator-(const Vector3D & v)
{
	return Vector3D(v.Vx * -1, v.Vy * -1, v.Vz * -1);
}

MR::Geometry::Vector3D &MR::Geometry::Vector3D::operator=(const Vector3D & right)
{
	if (&right == this)
		return *this;
	setVector(right.Vx, right.Vy, right.Vz);
	if (!check())
		throw std::exception("Wrong Vector");
	return *this;
}

MR::Geometry::Vector3D MR::Geometry::Vector3D::operator+(const Vector3D & right) const
{
	return Vector3D(this->Vx + right.Vx, this->Vy + right.Vy, this->Vz + right.Vz);
}

MR::Geometry::Vector3D MR::Geometry::Vector3D::operator-(const Vector3D & right) const
{
	return Vector3D(this->Vx - right.Vx, this->Vy - right.Vy, this->Vz - right.Vz);
}

MR::Geometry::Vector3D MR::Geometry::Vector3D::operator*(double a) const
{
	return Vector3D(this->Vx * a, this->Vy * a, this->Vz * a);
}

MR::Geometry::Vector3D MR::Geometry::Vector3D::operator/(double a) const
{
	return Vector3D(this->Vx / a, this->Vy / a, this->Vz / a);
}

bool MR::Geometry::Vector3D::operator==(const Vector3D & right) const
{
	return compareAproximately(*this, right);
}

double MR::Geometry::scalarProduct(const Vector3D & vec1, const Vector3D & vec2)
{
	return double(vec1.Vx * vec2.Vx + vec1.Vy * vec2.Vy + vec1.Vz * vec2.Vz);
}

MR::Geometry::Vector3D MR::Geometry::vectorProduct(const Vector3D & vec1, const Vector3D & vec2)
{
	Vector3D result;
	double Vx_i = vec1.Vy * vec2.Vz - vec1.Vz * vec2.Vy;
	double Vy_i = vec1.Vz * vec2.Vx - vec1.Vx * vec2.Vz;
	double Vz_i = vec1.Vx * vec2.Vy - vec1.Vy * vec2.Vx;
	result.setVector(Vx_i, Vy_i, Vz_i);
	return result;
}

double MR::Geometry::mixedProduct(const Vector3D & vec1, const Vector3D & vec2, const Vector3D & vec3)
{
	//!!! проверить освобождение памяти
	double **Ptr = new double*[3];
	Ptr[0] = new double[3]{ vec1.Vx, vec1.Vy, vec1.Vz };
	Ptr[1] = new double[3]{ vec2.Vx, vec2.Vy, vec2.Vz };
	Ptr[2] = new double[3]{ vec3.Vx, vec3.Vy, vec3.Vz };
	MR::Helpers::Matrix temp(3, 3);
	temp.setMatrix(3, 3, Ptr);
	return temp.getDeterminant();
}

double MR::Geometry::Vector3D::getAngleRad(const Vector3D & right) const
{
	double cos = scalarProduct(right) / this->getLength() / right.getLength();
	if (cos > 1)
		cos = 1;
	if (cos < -1)
		cos = -1;
	return std::acos(cos);
}

bool MR::Geometry::Vector3D::check()
{
	if (std::abs(Vx) > bigV || std::abs(Vy) > bigV || std::abs(Vz) > bigV || std::abs(Length) > bigV)
		return false;
	return true;
}

void MR::Geometry::Vector3D::calculateLength()
{
	Length = std::sqrt(Vx * Vx + Vy * Vy + Vz * Vz);
}