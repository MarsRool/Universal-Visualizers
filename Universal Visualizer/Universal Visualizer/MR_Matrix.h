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
			double **Ptr;//значения матрицы
			int Rows, Columns;//размерность матрицы. количество строк, столбцов
			double Determinant;//определитель матрицыW
		public:
			Matrix();//конструктор по умолчанию
			Matrix(int Rows_i, int Columns_i); // конструктор с параметрами
			Matrix(const Matrix &matrixToCopy); // конструктор копии
			~Matrix(); // десструктор класса MR_Matrix

		private:
			void clear();//очистить нулями данные
			void deleteData();//удалить данные матрицы
			void calculate_determinant();

		public:
			void getSize(int &Rows_i, int &Columns_i); //возвратить количество строк и столбцов
			double **getPtr(); //вернуть указатель на объект
			Array operator[] (int Rows_i); //перегруженная операция взятия индекса

			void setMatrix(int Rows_i, int Columns_i, double **Data); //заполнение матрицы
			//void getMatrix(); //вывод матрицы
			const double *search(const double & key); //поиск по ключу
			Matrix operator+ (const Matrix &right);
			Matrix operator+= (const Matrix &right);
			Matrix operator- (const Matrix &right);
			Matrix operator* (const Matrix &right);
			const Matrix &operator= (const Matrix &right); // оператор присваивания
			const bool operator== (const Matrix &right);// оператор сравнения

			bool istZero();
			Matrix getMinorMatrix(int x, int y);
			double getDeterminant();
		};
	}
}