#include "stdafx.h"
#include "MR_Matrix.h"
#include "global.h"

MR::Helpers::Matrix::Matrix()
{
	Rows = 0;
	Columns = 0;
	Ptr = nullptr;
	Determinant = 0;
}

MR::Helpers::Matrix::Matrix(int Rows_i, int Columns_i)
{
	Rows = Rows_i;
	Columns = Columns_i;
	Ptr = new double*[Rows];
	for (int i = 0; i < Rows; i++)
		Ptr[i] = new double[Columns];
	Determinant = 0;
}

MR::Helpers::Matrix::Matrix(const Matrix & matrixToCopy)
{
	Rows = 0;
	Columns = 0;
	Ptr = nullptr;
	setMatrix(matrixToCopy.Rows, matrixToCopy.Columns, matrixToCopy.Ptr);
	Determinant = matrixToCopy.Determinant;
}

MR::Helpers::Matrix::~Matrix()
{
	deleteData();
}

void MR::Helpers::Matrix::clear()
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			Ptr[i][j] = 0;
	Determinant = 0;
}

void MR::Helpers::Matrix::deleteData()
{
	if (Ptr != nullptr)
	{
		for (int i = 0; i < Rows; i++)
			delete[]Ptr[i];
		delete Ptr;
		Ptr = nullptr;
	}
	Rows = 0;
	Columns = 0;
	Determinant = 0;
}

void MR::Helpers::Matrix::calculate_determinant()
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

void MR::Helpers::Matrix::getSize(int & Rows_i, int & Columns_i)
{
	Rows_i = Rows;
	Columns_i = Columns;
}

double ** MR::Helpers::Matrix::getPtr()
{
	return Ptr;
}

MR::Helpers::Array MR::Helpers::Matrix::operator[](int Rows_i)
{
	if (Rows_i < 0 || Rows_i >= Rows)
		return Array(Ptr[0], 0);
	else
		return Array(Ptr[Rows_i], Columns);
}

void MR::Helpers::Matrix::setMatrix(int Rows_i, int Columns_i, double ** Data)
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

const double * MR::Helpers::Matrix::search(const double & key)
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (Ptr[i][j]==key)
				return &Ptr[i][j];
	return nullptr;
}

MR::Helpers::Matrix MR::Helpers::Matrix::operator+(const Matrix & right)
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

MR::Helpers::Matrix MR::Helpers::Matrix::operator+=(const Matrix & right)
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

MR::Helpers::Matrix MR::Helpers::Matrix::operator-(const Matrix & right)
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

MR::Helpers::Matrix MR::Helpers::Matrix::operator*(const Matrix & right)
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

const MR::Helpers::Matrix & MR::Helpers::Matrix::operator=(const Matrix & right)
{
	if (&right != this) // чтобы не выполнялось самоприсваивание
		setMatrix(right.Rows, right.Columns, right.Ptr);
	Determinant = right.Determinant;

	return *this; // разрешает множественное присваивание, например x = t = e
}

const bool MR::Helpers::Matrix::operator==(const Matrix & right)
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

bool MR::Helpers::Matrix::istZero()
{
	if (Rows == 0 && Columns == 0 && Ptr == nullptr && Determinant == 0)
		return true;
	else
		return false;
}

MR::Helpers::Matrix MR::Helpers::Matrix::getMinorMatrix(int x, int y)
{
	if (Rows != Columns || Rows <= 1 || Columns <= 1 || !(x >= 0 && x < Rows && y >= 0 && y < Columns))
		return *new Matrix();
	else
	{
		double** New_Ptr = new double*[Rows - 1];
		for (int i = 0; i < Rows - 1; i++)
			New_Ptr[i] = new double[Columns - 1];

		for (int i = 0, i_new = 0; i < Rows && i_new < Rows - 1; i++)
			if (i != x)
			{
				for (int j = 0, j_new = 0; j < Columns && j_new < Columns - 1; j++)
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

double MR::Helpers::Matrix::getDeterminant()
{
	return Determinant;
}