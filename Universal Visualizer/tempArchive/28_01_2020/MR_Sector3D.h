#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///����� ������� ����� � ������������, ����������� � ������� ��������� ��������������� ��������� ����� �� ��������� �����
		///</summary>
		class Sector3D
		{
		public:
			Sector3D(double angle1, double angle2, double angleMiddle);

			//bool isZero(); - ��������� ��������, ����� ����� ����������� ����������� ������������ ������� ����.������, ����� ������� ������� � �������� ���� ��� ��������� ������� � �������
			//bool isFullCircle(); - ����������
			bool isSectorIntersect(const Sector3D &sec) const;

			static bool compareSectors(const Sector3D *a, const Sector3D *b);
			///<summary>
			///���������� ��� �������, ���� ��� ��������, ����� ���������� nullptr
			///</summary>
			static Sector3D *integrateSectors(const Sector3D &sec1, const Sector3D &sec2);
			///<summary>
			///���������� ��������������� �������
			///</summary>
			static void integrateSectors(std::list<Sector3D*> &sectors);
			///<summary>
			///���������� ������ �������� �� ����������� angle1
			///</summary>
			static void sortSectors(std::list<Sector3D*> &sectors);
		private:
			void correct(double angleMiddle);
			bool check();
			double angle1, angle2;
		};
	}
}