#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Vector3D.h"
#include "MR_Angle2D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///����� ������� �����/���������� �� ���������, ����������� � ������� ���� �����: 
		///angle1 < angle2, ���� ���� �� angle1 �� angle2(����������), � 
		///angle1 > angle2, ���� ���� �� angle2 �� angle1(�������)
		///</summary>
		class Sector2D
		{
		public:
			///<summary>
			///������� ������ �����/���������� �� ���� ������ � ����� ����� ���� ��� �������������
			///</summary>
			Sector2D(const Angle2D &angle1, const Angle2D &angle2, const Angle2D &angleMiddle);

			///<summary>
			///true- ���� ������ ����� ���� (��������������)
			///</summary>
			bool isZero();
			///<summary>
			///true- ���� ������ ����� ������� ����� (��������������)
			///</summary>
			bool isFullCircle();
			///<summary>
			///true- ���� ������ ������ � ������ ��������, �.�. ���������� ��� �������� ������� �������
			///��� ����, ����� ����������, ����� �� �� ����������.
			///</summary>
			bool isSectorAdjacent(const Sector2D &sec) const { return (isSectorIntersect(sec) || isSectorTangential(sec)); }
			///<summary>
			///true- ���� ������ ���������� ������ ������.
			///</summary>
			bool isSectorIntersect(const Sector2D &sec) const;
			///<summary>
			///true- ���� ������ �������� ������� ������� (������ � ���).
			///�.�. ����� �����(-��) ��������� �����
			///</summary>
			bool isSectorTangential(const Sector2D &sec) const;

			///<summary>
			///���������� ��� �������, ���� ��� ��������, ����� ���������� nullptr
			///</summary>
			static Sector2D *integrateSectors(const Sector2D &sec1, const Sector2D &sec2);
			///<summary>
			///���������� �������. �������� sectors.
			///</summary>
			static void integrateSectors(std::list<Sector2D*> &sectors);
		private:
			///<summary>
			///������������ ��� ���� � �������� [angle1Out, angle2Out], ���
			///angle2Out &lt; 360, angle1Out &lt; angle2Out,
			///-360 &lt; angle1Out &lt; 360, angle2Out - angle1Out &lt;= 360
			///</summary>
			void AngleToDegreeDiapazon(MR::Helpers::DoublePreciseApproximate &angle1Out, MR::Helpers::DoublePreciseApproximate &angle2Out) const;
			///<summary>
			///������������ �������� [angle1In, angle2In] � ��� ����, ���
			///angle2Out &lt; 360, angle1Out &lt; angle2Out,
			///-360 &lt; angle1Out &lt; 360, angle2Out - angle1Out &lt;= 360
			///</summary>
			void DegreeDiapazonToAngle(MR::Helpers::DoublePreciseApproximate angle1In, MR::Helpers::DoublePreciseApproximate angle2In);
			void correct(const Angle2D &angleMiddle);
			Angle2D angle1, angle2;
		};
	}
}