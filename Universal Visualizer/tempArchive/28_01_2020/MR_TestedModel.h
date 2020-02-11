#pragma once
#pragma once
#include "stdafx.h"
#include "3DModel.h"
#include "MR_Model.h"
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
		///MR ������.
		///������������� - ���������� ������ �� ����� �����������, ���� ��� ���������� ���� ����� - ��������� ������� ������� �� ������.
		///��������� ������ �����: add -> getModelTested3DObjects.
		///���� TestedModel �� ����� ���� ��������������, ��� ���� �������� ���������������� ���� ��� �������.
		///</summary>
		class TestedModel : public Model
		{
		public:
			TestedModel();
			///<summary>
			///�������� ����� ������.
			///</summary>
			///<param name ="modelToCopy">������</param>
			///<param name ="fullCopy">true- ������ �����, false - ��������</param>
			TestedModel(const TestedModel &modelToCopy, bool fullCopy = true);

			MR::Model::TestedModel* getModelTested3DObjects();
		private:
		};
	}
}