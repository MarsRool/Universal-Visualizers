#pragma once
#include "stdafx.h"
#include "global.h"
#include "MR_Model.h"
#include "MR_Basis3D.h"
#include "MR_Sector3D.h"
#include "MR_Plane3D.h"

namespace MR
{
	namespace Geometry
	{
		///<summary>
		///����� ��� ������������ ���������� ����� ������ ��� ������� ������� ��� ������ (������������ ��������)
		///<summary>
		class SphereTest
		{
		public:
			///<summary>
			///�������� ����� ����� ��� ������
			///<summary>
			SphereTest(const MR::Model::Model &model, const Geometry::Point3D &point, double radius = smallV);
			///<summary>
			///true- ���� ����� ������
			///<summary>
			bool isInside() { return IsInside; }
			///<summary>
			///true- ���� ����� �������
			///<summary>
			bool isOutside() { return (!isInside()); }
			/*///<summary>
			///!!!���������. ������� ������, � ������� ������ �����. ���� ����� �������, ��������� nullptr
			///<summary>
			MR::Model::Object *getIncludingObject();*/
		private:
			///<summary>
			///�������� �� ������������ SphereTest
			///<summary>
			bool check();
			///<summary>
			///�������� �� ����������� ������ ������. true- ���� ���������� � ������ ���� ��������.
			///<summary>
			bool isSphereIntersectModel();
			///<summary>
			///���� ����� �� ��������� � ������
			///<summary>
			void test();
			///<summary>
			///������ ����������� �����
			///<summary>
			double Radius = smallV;
			///<summary>
			///�������� ������, ������������ ������� ���������� ���������� �����
			///</summary>
			const MR::Model::Model TestModel;
			///<summary>
			///����������� �����
			///</summary>
			const Geometry::Point3D TestPoint;
			///<summary>
			///true- ���� ����� ������. �� ���������, ��� �������
			///<summary>
			bool IsInside = false;
			///<summary>
			///true- ���� ���� ����������.
			///<summary>
			bool isOk;
			/*///<summary>
			///!!!���������. �������, � ������� ������ �����
			///<summary>
			list<MR::Model::Object*> IncludingObjects;*/
		};
	}
}