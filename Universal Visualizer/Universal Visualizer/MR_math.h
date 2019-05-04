#pragma once
#include "stdafx.h"

namespace MR
{
	class Point2D//MR 2D точка
	{
	private:
		double X, Y;
	public:
	};

	class Vector3D;
	class Line3D;
	class Plane3D;

	class Point3D//MR 3D точка
	{
	private:
		double X, Y, Z;
	public:
		Point3D();
		Point3D(double X_i, double Y_i, double Z_i);
		Point3D(Point3D &PointToCopy);
		~Point3D() {}//пустой деструктор.

		const bool operator == (const Point3D &point_right);
		Point3D operator = (const Point3D &point_right);
		Point3D operator + (const Point3D &point_right);
		Point3D operator - (const Point3D &point_right);

		bool check();
		double x() { return X; }
		double y() { return Y; }
		double z() { return Z; }
		void setX(double x_in) { X = x_in; }
		void setY(double y_in) { Y = y_in; }
		void setZ(double z_in) { Z = z_in; }
		void set(double X_i, double Y_i, double Z_i);
		void get(double &X_i, double &Y_i, double &Z_i);

		friend Point3D ** searchPoint(std::vector<Point3D**> Points, Point3D *Point_key);//находит адрес адреса точки в массиве точек

		friend Vector3D;
		friend Line3D;
		friend Plane3D;
	};

	class Vector3D
	{
	private:
		double Vx, Vy, Vz;
		double Length;

		void calculateLength();
	public:
		Vector3D();
		Vector3D(double Vx_i, double Vy_i, double Vz_i);
		Vector3D(Point3D *point1, Point3D *point2);
		Vector3D(Vector3D &vectorToCopy);
		~Vector3D() {}//пустой деструктор.

		void setVector(double Vx_i, double Vy_i, double Vz_i);
		void getVector(double &Vx_i, double &Vy_i, double &Vz_i);
		double getLength();

		bool istZero();//true- если вектор нулевой
		void normalize();//нормировать вектор

		friend double scalarProduct(Vector3D &vec1, Vector3D &vec2);
		friend Vector3D vectorProduct(Vector3D &vec1, Vector3D &vec2);
		friend double mixedProduct(Vector3D &vec1, Vector3D &vec2, Vector3D &vec3);

		friend bool compareAproximately(const Vector3D &left, const Vector3D &right);
		friend Vector3D operator - (const Vector3D &v);
		Vector3D operator = (const Vector3D & point_right);

		friend Line3D;
		friend Plane3D;
	};

	class Line3D//прямая в пространстве, заданная в каноническом виде
	{
	private:
		Vector3D *Direction;//направление прямой
		Point3D *Point;//точка, через которую проходит прямая
	public:
		Line3D();
		Line3D(Vector3D *Direction_i, Point3D *Point_i);
		Line3D(Point3D *Point1, Point3D *Point2);
		~Line3D();
	private:
		void deleteData();//!!!unused
	};

	class Plane3D
	{
	private:
		Vector3D *Normal;//нормаль плоскости
		Point3D *Point;//точка, через которую проходит плоскость
	public:
		Plane3D(Vector3D *Normal_i, Point3D *Point_i);//вектор нормали и точка на плоскости
		Plane3D(Vector3D *Vector1, Vector3D *Vector2, Point3D *Point_i);//два вектора, параллельные плоскости и точка.
		Plane3D(Point3D *Point1, Point3D *Point2, Point3D *Point3);//три точки на плоскости
		~Plane3D();

		double distanceFromPoint(Point3D *Point_i);
		short int whereIstDot(Point3D *Point_i);//1 - снаружи, 0 - на плоскости, -1 - внутри плоскости
		bool istDotsInBothSides(std::vector<Point3D*> Points);
	};

	class Array
	{
	private:
		double* Ptr;
		int size;
	public:
		Array();
		Array(double* Ptr_i, int size_i);
		Array(const Array & arrayToCopy);
		~Array();

		double & at(int k, bool isOk);//возвращает

		double operator[] (int k); // перегруженная операция взятия индекса
	};

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