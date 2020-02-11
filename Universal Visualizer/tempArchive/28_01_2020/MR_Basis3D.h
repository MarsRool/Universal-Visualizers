#pragma once
#include "stdafx.h"
#include "MR_Vector3D.h"

namespace MR
{
	namespace Geometry
	{
		class Basis3D
		{
		public:
			Basis3D(const Vector3D &vec1, const Vector3D &vec2, const Vector3D &vec3);
			Basis3D(const Vector3D &vec1, const Vector3D &vec2);
			/*
			///<summary>
			///���������� ���� ����� ��������� � ��������. �� 0 �� Pi
			///</summary>
			double getAngleRad_0ToPi(const Vector3D vec) const;
			///<summary>
			///���������� ���� ����� ��������� � ��������. �� 0 �� 2Pi
			///</summary>
			double getAngleRad_0To2Pi(const Vector3D vec) const;
			///<summary>
			///���������� ���� ����� ��������� � ��������. �� -Pi �� Pi
			///</summary>
			double getAngleRad_NegPiToPi(const Vector3D vec) const;

			///<summary>
			///���������� ���� ����� ��������� � ��������. �� 0 �� Pi
			///</summary>
			double getAngleRad_0ToPi(const Vector3D left, const Vector3D & right) const;
			///<summary>
			///���������� ���� ����� ��������� � ��������. �� 0 �� 2Pi
			///</summary>
			double getAngleRad_0To2Pi(const Vector3D left, const Vector3D & right) const;
			///<summary>
			///���������� ���� ����� ��������� � ��������. �� -Pi �� Pi
			///</summary>
			double getAngleRad_NegPiToPi(const Vector3D left, const Vector3D & right) const;*/
		private:
			Vector3D Ex, Ey, Ez;
		};
	}
}