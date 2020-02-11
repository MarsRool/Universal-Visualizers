#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_Object.h"
#include "graph.h"

namespace MR
{
	namespace Model
	{
		///<summary>
		///MR ������������� ������.
		///��������� Object.
		///������������ ���������� �� ���������������� �������.
		///���������������� ������� ���������� ������ �����(������������ ��� �����������) getTested3dObjects
		///</summary>
		class TestedObject : public Object
		{
		public:
			///<summary>
			///�������� ������� �������(��� ������������)
			///</summary>
			TestedObject();
			///<summary>
			///������ ������ ��� �������� ����� ��� �������. �������: ����� ������ ���� ��������� �� ������. (��� ������������)
			///</summary>
			TestedObject(const std::list<Face*> &Faces_i, string name = "");
			///<summary>
			///������ ������ ��� �������� ����� ��� �������. �������: ����� ������ ���� ��������� �� ������. (��� ������������)
			///</summary>
			TestedObject(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i, string name = "");
			///<summary>
			///������� ������ ����� �������(���� ���������� ������ �������������, ����� ��������� ����������������, ��� - ���)
			///</summary>
			TestedObject(const TestedObject &objectToCopy);
			~TestedObject();
			///<summary>
			///������� ������ ����� �������(���� ���������� ������ �������������, ����� ��������� ����������������, ��� - ���)
			///</summary>
			TestedObject& operator = (const TestedObject &objToCopy);

			///<summary>
			///���������� ��������� ���������������� �������� �� object(����������)
			///</summary>
			static std::list<TestedObject*>* getTested3dObjects(const TestedObject &object);
			///<summary>
			///���������� ��������� ���������������� �������� �� �������� �������
			///</summary>
			std::list<TestedObject*>* getTested3dObjects();
			///<summary>
			///true- ������ �������������
			///</summary>
			bool isTested() { return IsTested; }

			///<summary>
			///�������� Object �� TestedObject, ��� ���� �������� objectToCopy ���������
			///</summary>
			static TestedObject* ToTestedObject(Object* objectToCopy);
		private:
			///<summary>
			///���� �� ��������� �����, ������� ���������.
			///���������� �� �������� ������� ������ ����������� ������, � ������� ���� ���� ��� ����� �������������� ����
			///�������� ������ ��� ����� ������
			///</summary>
			static TestedObject* getObjCleanedBoundaryFaces(const TestedObject & object);

			///<summary>
			///������� ������� ������ �� �������, ���� �� ��������� � ������ �������.
			///���������� ������ ������ ����������� �������� �������� (������, ���� �� ����)
			///� ������ ������/������ ������, ������ ������ ������
			///�������� ������ ��� ����� �������.
			///�������� ������� ���������� ��������!!!
			///</summary>
			///<param name="object">
			///�������� ������� ���������� ��������!!!
			///</param>
			static std::list<TestedObject*>* get3DObjects(TestedObject & object);

			bool IsTested = false;
		};
	}
}