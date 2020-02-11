#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_TestedObject.h"
#include "graph.h"
//�������� ��������� ������� ������ ���������: Points � Edges.
//� ���� ������:
//�� �������� ������� ����� ����������, �������������� ��������� ������
//���������� �������� � ��������������� �����������, ����� ���-�� ����� ������������, ��� ���������� �����������, ��� ���������� ����

//Type **element �������� ����� �� �������, ������� ������ ���� ������ � ������������ � ��������� � �����������
//*element �������� ����� �� ��� �������. ��� ������� � ����� ������� ����������� ��������� �������� ��� ���������� ���������

namespace MR
{
	namespace Model
	{
		///<summary>
		///MR ������
		///</summary>
		class Model
		{
		public:
			Model();
			///<summary>
			///�������� ����� ������.
			///</summary>
			///<param name ="modelToCopy">������</param>
			///<param name ="fullCopy">true- ������ �����, false - ��������</param>
			Model(const Model &modelToCopy, bool fullCopy = true);
			///<summary>
			///������ ������������� �������������
			///</summary>
			void addFrom3DModel(const t3DModel & Model);
			///<summary>
			///������ ������������� �������������
			///</summary>
			void addFromGraph(const graph &Graph);
			void addObject(const Object &object);
			void drawModel();

			void getObjects(std::list<Object*> &Objects_out) const { Objects_out = Objects; }
		protected:
			std::list<Object*> Objects;
		};
	}
}