#pragma once
#include "stdafx.h"

namespace MR
{
	class Point2D//MR 2D �����
	{
	private:
		double X, Y;
	public:
	};

	class Vector3D;
	class Line3D;
	class Plane3D;

	class Point3D//MR 3D �����
	{
	private:
		double X, Y, Z;
	public:
		Point3D();
		Point3D(double X_i, double Y_i, double Z_i);
		Point3D(Point3D &PointToCopy);
		~Point3D() {}//������ ����������.

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

		friend Point3D ** searchPoint(std::vector<Point3D**> Points, Point3D *Point_key);//������� ����� ������ ����� � ������� �����

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
		~Vector3D() {}//������ ����������.

		void setVector(double Vx_i, double Vy_i, double Vz_i);
		void getVector(double &Vx_i, double &Vy_i, double &Vz_i);
		double getLength();

		bool istZero();//true- ���� ������ �������
		void normalize();//����������� ������

		friend double scalarProduct(Vector3D &vec1, Vector3D &vec2);
		friend Vector3D vectorProduct(Vector3D &vec1, Vector3D &vec2);
		friend double mixedProduct(Vector3D &vec1, Vector3D &vec2, Vector3D &vec3);

		friend bool compareAproximately(const Vector3D &left, const Vector3D &right);
		friend Vector3D operator - (const Vector3D &v);
		Vector3D operator = (const Vector3D & point_right);

		friend Line3D;
		friend Plane3D;
	};

	class Line3D//������ � ������������, �������� � ������������ ����
	{
	private:
		Vector3D *Direction;//����������� ������
		Point3D *Point;//�����, ����� ������� �������� ������
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
		Vector3D *Normal;//������� ���������
		Point3D *Point;//�����, ����� ������� �������� ���������
	public:
		Plane3D(Vector3D *Normal_i, Point3D *Point_i);//������ ������� � ����� �� ���������
		Plane3D(Vector3D *Vector1, Vector3D *Vector2, Point3D *Point_i);//��� �������, ������������ ��������� � �����.
		Plane3D(Point3D *Point1, Point3D *Point2, Point3D *Point3);//��� ����� �� ���������
		~Plane3D();

		double distanceFromPoint(Point3D *Point_i);
		short int whereIstDot(Point3D *Point_i);//1 - �������, 0 - �� ���������, -1 - ������ ���������
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

		double & at(int k, bool isOk);//����������

		double operator[] (int k); // ������������� �������� ������ �������
	};

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