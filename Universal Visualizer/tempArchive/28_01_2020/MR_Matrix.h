#pragma once
#include "stdafx.h"
#include "MR_Array.h"

namespace MR
{
	namespace Helpers
	{
		class Matrix
		{
		private://Ptr[Rows, Columns]
			double **Ptr;//�������� �������
			int Rows, Columns;//����������� �������. ���������� �����, ��������
			double Determinant;//������������ �������W
		public:
			Matrix();//����������� �� ���������
			Matrix(int Rows_i, int Columns_i); // ����������� � �����������
			Matrix(const Matrix &matrixToCopy); // ����������� �����
			~Matrix(); // ����������� ������ MR_Matrix

		private:
			void clear();//�������� ������ ������
			void deleteData();//������� ������ �������
			void calculate_determinant();

		public:
			void getSize(int &Rows_i, int &Columns_i); //���������� ���������� ����� � ��������
			double **getPtr(); //������� ��������� �� ������
			Array operator[] (int Rows_i); //������������� �������� ������ �������

			void setMatrix(int Rows_i, int Columns_i, double **Data); //���������� �������
			//void getMatrix(); //����� �������
			const double *search(const double & key); //����� �� �����
			Matrix operator+ (const Matrix &right);
			Matrix operator+= (const Matrix &right);
			Matrix operator- (const Matrix &right);
			Matrix operator* (const Matrix &right);
			const Matrix &operator= (const Matrix &right); // �������� ������������
			const bool operator== (const Matrix &right);// �������� ���������

			bool istZero();
			Matrix getMinorMatrix(int x, int y);
			double getDeterminant();
		};
	}
}