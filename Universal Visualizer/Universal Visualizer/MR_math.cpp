#include "stdafx.h"
#include "MR_math.h"
#include "global.h"

MR::Point3D::Point3D()
{
	set(0.0, 0.0, 0.0);
}

MR::Point3D::Point3D(double X_i, double Y_i, double Z_i)
{
	set(X_i, Y_i, Z_i);
}

MR::Point3D::Point3D(Point3D & PointToCopy)
{
	set(PointToCopy.X, PointToCopy.Y, PointToCopy.Z);
}

const bool MR::Point3D::operator==(const Point3D & point_right)
{
	return (X == point_right.X && Y == point_right.Y && Z == point_right.Z);
}

MR::Point3D MR::Point3D::operator=(const Point3D & point_right)
{
	if (&point_right == this)
		return *this;
	return Point3D(this->X = point_right.X, this->Y = point_right.Y, this->Z = point_right.Z);
}

MR::Point3D MR::Point3D::operator+(const Point3D & point_right)
{
	return Point3D(this->X + point_right.X, this->Y + point_right.Y, this->Z + point_right.Z);
}

MR::Point3D MR::Point3D::operator-(const Point3D & point_right)
{
	return Point3D(this->X - point_right.X, this->Y - point_right.Y, this->Z - point_right.Z);
}

bool MR::Point3D::check()
{
	if (std::abs(X) < bigV && std::abs(Y) < bigV && std::abs(Z) < bigV)
		return true;
	return false;
}

void MR::Point3D::set(double X_i, double Y_i, double Z_i)
{
	X = X_i;
	Y = Y_i;
	Z = Z_i;
}

void MR::Point3D::get(double & X_i, double & Y_i, double & Z_i)
{
	X_i = X;
	Y_i = Y;
	Z_i = Z;
}

MR::Point3D ** MR::searchPoint(std::vector<Point3D**> Points, Point3D * Point_key)
{
	for (int i = 0; i < Points.size(); i++)
		if (Points[i] != NULL && (*Points[i]) != NULL)
			if (**Points[i] == *Point_key)
				return Points[i];
	return NULL;
}

void MR::Vector3D::calculateLength()
{
	Length = std::sqrt(Vx * Vx + Vy * Vy + Vz * Vz);
}

MR::Vector3D::Vector3D()
{
	Vx = 0;
	Vy = 0;
	Vz = 0;
	Length = 0;
}

MR::Vector3D::Vector3D(double Vx_i, double Vy_i, double Vz_i)
{
	setVector(Vx_i, Vy_i, Vz_i);
}

MR::Vector3D::Vector3D(Point3D *point1, Point3D *point2)
{
	Point3D delta = *point2 - *point1;
	Vx = delta.X;
	Vy = delta.Y;
	Vz = delta.Z;
	calculateLength();
}

MR::Vector3D::Vector3D(Vector3D & vectorToCopy)
{
	Vx = vectorToCopy.Vx;
	Vy = vectorToCopy.Vy;
	Vz = vectorToCopy.Vz;
	calculateLength();
}

void MR::Vector3D::setVector(double Vx_i, double Vy_i, double Vz_i)
{
	Vx = Vx_i;
	Vy = Vy_i;
	Vz = Vz_i;
	calculateLength();
}

void MR::Vector3D::getVector(double & Vx_i, double & Vy_i, double & Vz_i)
{
	Vx_i = Vx;
	Vy_i = Vy;
	Vz_i = Vz;
}

double MR::Vector3D::getLength()
{
	return Length;
}

bool MR::Vector3D::istZero()
{
	return (Vx == 0 && Vy == 0 && Vx == 0 && Length == 0) ? true : false;
}

void MR::Vector3D::normalize()
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

bool MR::compareAproximately(const Vector3D & left, const Vector3D & right)
{
	return ((std::abs(left.Vx - right.Vx) < smallV) &&
			(std::abs(left.Vy - right.Vy) < smallV) &&
			(std::abs(left.Vz - right.Vz) < smallV)) ? true : false;
}

MR::Vector3D MR::operator-(const Vector3D & v)
{
	return Vector3D(v.Vx * -1, v.Vy * -1, v.Vz * -1);
}

MR::Vector3D MR::Vector3D::operator=(const Vector3D & right)
{
	if (&right == this)
		return *this;
	return Vector3D(this->Vx = right.Vx, this->Vy = right.Vy, this->Vz = right.Vz);
}

double MR::scalarProduct(Vector3D & vec1, Vector3D & vec2)
{
	return double(vec1.Vx * vec2.Vx + vec1.Vy * vec2.Vy + vec1.Vz * vec2.Vz);
}

MR::Vector3D MR::vectorProduct(Vector3D & vec1, Vector3D & vec2)
{
	Vector3D result;
	double Vx_i = vec1.Vy * vec2.Vz - vec1.Vz * vec2.Vy;
	double Vy_i = vec1.Vz * vec2.Vx - vec1.Vx * vec2.Vz;
	double Vz_i = vec1.Vx * vec2.Vy - vec1.Vy * vec2.Vx;
	result.setVector(Vx_i, Vy_i, Vz_i);

	return result;
}

double MR::mixedProduct(Vector3D & vec1, Vector3D & vec2, Vector3D & vec3)
{
	double **Ptr = new double*[3];
	Ptr[0] = new double[3]{ vec1.Vx, vec1.Vy, vec1.Vz };
	Ptr[1] = new double[3]{ vec2.Vx, vec2.Vy, vec2.Vz };
	Ptr[2] = new double[3]{ vec3.Vx, vec3.Vy, vec3.Vz };
	Matrix temp(3, 3);
	temp.setMatrix(3, 3, Ptr);
	return temp.getDeterminant();
}

MR::Array::Array()
{
	size = 0;
	Ptr = NULL;
}

MR::Array::Array(double * Ptr_i, int size_i)
{
	size = size_i;
	Ptr = new double[size];
	for (int i = 0; i < size; i++)
		Ptr[i] = Ptr_i[i];
}

MR::Array::Array(const Array & arrayToCopy)
{
	size = arrayToCopy.size;
	Ptr = new double[size];
	for (int i = 0; i < size; i++)
		Ptr[i] = arrayToCopy.Ptr[i];
}

MR::Array::~Array()
{
	if (Ptr != NULL && size != 0)
	{
		size = 0;
		delete Ptr;
		Ptr = NULL;
	}
}

double & MR::Array::at(int k, bool isOk)
{
	if (k >= 0 && k < size)
	{
		return Ptr[k];
	}
	else
	{
		isOk = false;
		double a = 0;
		return a;
	}
}

double MR::Array::operator[] (int k)
{
	bool isOk = true;
	return at(k, isOk);
}

MR::Matrix::Matrix()
{
	Rows = 0;
	Columns = 0;
	Ptr = NULL;
	Determinant = 0;
}

MR::Matrix::Matrix(int Rows_i, int Columns_i)
{
	Rows = Rows_i;
	Columns = Columns_i;
	Ptr = new double*[Rows];
	for (int i = 0; i < Rows; i++)
		Ptr[i] = new double[Columns];
	Determinant = 0;
}

MR::Matrix::Matrix(const Matrix & matrixToCopy)
{
	Rows = 0;
	Columns = 0;
	Ptr = NULL;
	setMatrix(matrixToCopy.Rows, matrixToCopy.Columns, matrixToCopy.Ptr);
	Determinant = matrixToCopy.Determinant;
}

MR::Matrix::~Matrix()
{
	deleteData();
}

void MR::Matrix::clear()
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			Ptr[i][j] = 0;
	Determinant = 0;
}

void MR::Matrix::deleteData()
{
	if (Ptr != NULL)
	{
		for (int i = 0; i < Rows; i++)
			delete[]Ptr[i];
		delete Ptr;
		Ptr = NULL;
	}
	Rows = 0;
	Columns = 0;
	Determinant = 0;
}

void MR::Matrix::calculate_determinant()
{
	short int znak = 1;
	Determinant = 0;
	if (Rows == Columns)
	{
		if (Rows > 2)
			for (int i = 0; i < Rows; i++)
			{
				Determinant += znak * Ptr[i][0] * getMinorMatrix(i, 0).getDeterminant();
				znak *= -1;
			}
		else if (Rows == 2)
		{
			Determinant = Ptr[0][0] * Ptr[1][1] - Ptr[1][0] * Ptr[0][1];
		}
		else if (Rows == 1)
		{
			Determinant = Ptr[0][0];
		}
	}
}

void MR::Matrix::getSize(int & Rows_i, int & Columns_i)
{
	Rows_i = Rows;
	Columns_i = Columns;
}

double ** MR::Matrix::getPtr()
{
	return Ptr;
}

MR::Array MR::Matrix::operator[](int Rows_i)
{
	if (Rows_i < 0 || Rows_i >= Rows)
		return Array(Ptr[0], 0);
	else
		return Array(Ptr[Rows_i], Columns);
}

void MR::Matrix::setMatrix(int Rows_i, int Columns_i, double ** Data)
{
	if (Rows != Rows_i && Columns != Columns_i)
	{
		deleteData();
		Rows = Rows_i;
		Columns = Columns_i;
		Ptr = new double*[Rows];
		for (int i = 0; i < Rows; i++)
			Ptr[i] = new double[Columns];
	}
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			Ptr[i][j] = Data[i][j];
	calculate_determinant();
}

const double * MR::Matrix::search(const double & key)
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (Ptr[i][j]==key)
				return &Ptr[i][j];
	return NULL;
}

MR::Matrix MR::Matrix::operator+(const Matrix & right)
{
	if (Rows != right.Rows || Columns != right.Columns)
	{
		return *this;
	}
	else
	{
		Matrix result(Rows, Columns);
		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
				result.Ptr[i][j] = Ptr[i][j] + right.Ptr[i][j];
		result.calculate_determinant();

		return result; // вернуть сумму
	}
}

MR::Matrix MR::Matrix::operator+=(const Matrix & right)
{
	if (Rows != right.Rows || Columns != right.Columns)
	{
		return *this;
	}
	else
	{
		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
				Ptr[i][j] += right.Ptr[i][j];
		calculate_determinant();

		return *this; // вернуть сумму
	}
}

MR::Matrix MR::Matrix::operator-(const Matrix & right)
{
	if (Rows != right.Rows || Columns != right.Columns)
	{
		return *this;
	}
	else
	{
		Matrix result(Rows, Columns);
		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
				result.Ptr[i][j] = Ptr[i][j] - right.Ptr[i][j];
		calculate_determinant();

		return result; // вернуть сумму
	}
}

MR::Matrix MR::Matrix::operator*(const Matrix & right)
{//A[ab]*B[cd].	b==c
	if (Columns != right.Rows)
		return *this;
	else
	{
		Matrix result(Rows, right.Columns);
		for (int i=0; i<Rows; i++)
			for (int j = 0; j < right.Columns; j++)
			{
				result.Ptr[i][j] = 0;
				for (int l = 0; l < Columns; l++)
					result.Ptr[i][j] += Ptr[i][l] * right.Ptr[l][j];
			}

		return result;
	}
}

const MR::Matrix & MR::Matrix::operator=(const Matrix & right)
{
	if (&right != this) // чтобы не выполнялось самоприсваивание
		setMatrix(right.Rows, right.Columns, right.Ptr);
	Determinant = right.Determinant;

	return *this; // разрешает множественное присваивание, например x = t = e
}

const bool MR::Matrix::operator==(const Matrix & right)
{
	if (Rows != right.Rows || Columns != right.Columns)
		return false; // матрицы с разным количеством элементов

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (Ptr[i][j] != right.Ptr[i][j])
				return false; // матрицы не равны

	if (Determinant != right.Determinant)
		return false;

	return true; // матрицы равны
}

bool MR::Matrix::istZero()
{
	if (Rows == 0 && Columns == 0 && Ptr == NULL && Determinant == 0)
		return true;
	else
		return false;
}

MR::Matrix MR::Matrix::getMinorMatrix(int x, int y)
{
	if (Rows != Columns || Rows <= 1 || Columns <= 1 || !(x >= 0 && x < Rows && y >= 0 && y < Columns))
		return *new Matrix();
	else
	{
		double** New_Ptr = new double*[Rows - 1];
		for (int i = 0; i < Rows - 1; i++)
			New_Ptr[i] = new double[Columns - 1];

		for (int i = 0, i_new = 0; i < Rows, i_new < Rows - 1; i++)
			if (i != x)
			{
				for (int j = 0, j_new = 0; j < Columns, j_new < Columns - 1; j++)
				{
					if (j != y)
					{
						New_Ptr[i_new][j_new] = Ptr[i][j];
						j_new++;
					}
				}
				i_new++;
			}

		Matrix result(Rows - 1, Columns - 1);
		result.setMatrix(Rows - 1, Columns - 1, New_Ptr);
		result.calculate_determinant();

		return result;
	}
}

double MR::Matrix::getDeterminant()
{
	return Determinant;
}

MR::Line3D::Line3D()
{
	Direction = NULL;
	Point = NULL;
}

MR::Line3D::Line3D(Vector3D *Direction_i, Point3D *Point_i)
{
	*Direction = *Direction_i;
	*Point = *Point_i;
}

MR::Line3D::Line3D(Point3D *Point1, Point3D *Point2)
{
	Direction = new Vector3D(Point1, Point2);
	*Point = *Point1;
}

MR::Line3D::~Line3D()
{
	delete Direction;
	delete Point;
}

void MR::Line3D::deleteData()
{
	if (Direction != NULL)
	{
		delete Direction;
		Direction = NULL;
	}
	if (Point!=NULL)
	{
		delete Point;
		Point = NULL;
	}
}

MR::Plane3D::Plane3D(Vector3D * Normal_i, Point3D * Point_i)
{
	*Normal = *Normal_i;
	*Point = *Point_i;
}

MR::Plane3D::Plane3D(Vector3D * Vector1, Vector3D * Vector2, Point3D * Point_i)
{
	*Normal = vectorProduct(*Vector1, *Vector2);
	*Point = *Point_i;
}

MR::Plane3D::Plane3D(Point3D * Point1, Point3D * Point2, Point3D * Point3)
{
	*Normal = vectorProduct(Vector3D(Point1, Point2), Vector3D(Point1, Point3));
	*Point = *Point1;
}

MR::Plane3D::~Plane3D()
{
	delete Normal;
	delete Point;
}

double MR::Plane3D::distanceFromPoint(Point3D * Point_i)
{
	double D = -(Normal->Vx * Point->X) - (Normal->Vy * Point->Y) - (Normal->Vz * Point->Z);
	return (std::abs((Normal->Vx * Point_i->X) +
					 (Normal->Vy * Point_i->Y) +
					 (Normal->Vz * Point_i->Z) + D)) /
					 (Normal->getLength());
}

short int MR::Plane3D::whereIstDot(Point3D * Point_i)
{//1 - снаружи, 0 - на плоскости, -1 - внутри плоскости
	double result;
	double D = -(Normal->Vx * Point->X) - (Normal->Vy * Point->Y) - (Normal->Vz * Point->Z);
	result = ((Normal->Vx * Point_i->X) +
		(Normal->Vy * Point_i->Y) +
		(Normal->Vz * Point_i->Z) + D);
	if (result > 0)
		return 1;
	else if (result < 0)
		return -1;
	else
		return 0;
}

bool MR::Plane3D::istDotsInBothSides(std::vector<Point3D*> Points)
{
	bool ist_outside = false, ist_inside = false;
	for (int i = 0; i < Points.size(); i++)
		if (ist_outside && ist_inside)
			break;
		else
		{
			if (whereIstDot(Points[i]) == -1)//inside
				ist_inside = true;
			if (whereIstDot(Points[i]) == 1)
				ist_outside = true;
		}
	return (ist_outside && ist_inside);
}
