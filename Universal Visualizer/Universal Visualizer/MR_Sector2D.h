#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"

namespace MR
{
	namespace Geometry
	{
		class Sector2D
		{
		public:
			//!!! ���������������, �������� ������ �����!
			Sector2D(double angle1, double angle2, double angleMiddle);

			bool isZero();
			bool isFullCircle();
			bool isSectorIntersect(const Sector2D &sec) const;

			static bool compareSectors(const Sector2D *a, const Sector2D *b);
			///<summary>
			///���������� ��� �������, ���� ��� ��������, ����� ���������� nullptr
			///</summary>
			static Sector2D *integrateSectors(const Sector2D &sec1, const Sector2D &sec2);
			///<summary>
			///���������� ��������������� �������
			///</summary>
			static void integrateSectors(std::list<Sector2D*> &sectors);
			///<summary>
			///���������� ������ �������� �� ����������� angle1
			///</summary>
			static void sortSectors(std::list<Sector2D*> &sectors);
		private:
			void correct(double angleMiddle);
			bool check();
			double angle1, angle2;
		};
	}
}