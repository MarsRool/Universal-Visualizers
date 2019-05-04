#include "stdafx.h"
#include "3DModel.h"

t3DModel::t3DModel()
{
	numVerts=0;
	numTexVertex=0;
	numNormals=0;
	numTex=0;
	bHasTexture=false;
	numOfObjects=0;
}

bool t3DModel::GetLoadedModel()
{
	return isto;
}

void t3DModel::Print_Obj_Faces(const t3DObject &obj,int n)
{
	cout << obj.numFaces << endl;
	for (int i=1;i<=n;i++)
	{
		float elem[3];
		cout << i << endl;
		for(int j=0;j<3;j++)
		{
			elem[0]=obj.pFaces[i].vi[j];
			elem[1]=obj.pFaces[i].ti[j];
			elem[2]=obj.pFaces[i].ni[j];
			cout << elem[0] << "/" << elem[1] << "/" << elem[2] << " ";
		}
		cout << obj.pFaces[i].Id_tex << endl;
	}
}

void t3DModel::Return_Data(bool &isto_out,
	int &numVerts_out, vector<CV3> &pVerts_out,
	int &numOfObjects_out, vector<t3DObject> &Objects_out) const
{
	isto_out = isto;					//��������� �� ������

	numVerts_out = numVerts;              // ����� ������ � ������

	pVerts_out = pVerts;		// ������ ������ �������

	numOfObjects_out = numOfObjects;           // ����� �������� � ������
	Objects_out = Objects;  // �������� �������
}

void t3DModel::Print_Objects(int n)
{
	setlocale( LC_ALL,"Russian");
	cout << "���������� ��������: " << numOfObjects << endl;
	for (int i=1;i<=numOfObjects;i++)
	{
		cout << "��� �������: " << Objects[i].strName << endl;
		cout << "���-�� ��������� � ���:";
		Print_Obj_Faces(Objects[i],n);
		cout<<endl;
	}
	setlocale( LC_ALL,"C");
}