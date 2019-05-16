#pragma once
#include "stdafx.h"

#include "texture.h"

using namespace std;

// ��������� 3D-�����
struct CV3{
    float x,y,z;
};

// ��������� 2D-�����
struct CV2{
    float x,y;
};
// ��� ��������� ��������. ��� ������������ ��� �������������� �������� ���������
// ������ � �������. ��� ���������� �������� ��� � ���, ����� ������ ������ � �������
// ������ �������� �����������. �� �� ����� �������� ���������� ���������.
struct tFace
{
    int vi[3];// vertex index
	int ti[3];// texture index
	int ni[3];// normal index
	int Id_tex;// ������ ��������
	//�������, ������
	//������� ��� ������� � ������ �������. �.�. ����������� �� ������ �� ������� ��� ���������.
	//!�� �������� ��������� ��������S
};

//��������� ��� �������
struct TK
{
	float rgb[3];//���� RGB
	bool ist;//���������� �� ���� ����
	//string  strFile;//��� �����
	bool fileist;//���������� �� ���� ����
	CTexture texture;//����������� ��������
};

// ��� ��������� ������ ���������� � ���������. ��� ����� ���� ���������� ����� �����.
struct tMaterialInfo
{
    string  strName;			// ��� ��������
    int   texureId;             // ID ��������

    TK Ka; // ambient
	TK Kd; // diffuse
	TK Ks; // specular (�� ������������)
	TK Ke; // ���� (�� ������������)

	float Ni; //�� ������������. ��� ���������� ���������
	float Ns; //�� ������������. ��� ����������� ���������� �� 0 �� 100
	float d; //������������ �� 0 �� 1 (�� ������������)
	int illum;//����? (�� ������������)
};

// �������� ��� ���������� �� �������.
struct t3DObject
{
	vector<tFace> pFaces;       // �������� �������
	int  numFaces;              // ����� ��������� �������
	string strName;             // ��� �������
};

class t3DModel
{
private:
	bool isto;					//��������� �� ������

	int  numVerts;              // ����� ������ � ������
    int  numTexVertex;          // ����� ���������� ���������
	int  numNormals;            // ����� ��������

	int  numTex;				// ����� �������
	vector<tMaterialInfo> Textures;  //�������� ������ ��������
	bool bHasTexture;           // TRUE ���� ���� ���������� ����� ��� ����� �������
	
	vector<CV3>   pVerts;		// ������ ������ �������
    vector<CV2>   pTexVerts;    // ���������� ����������
	vector<CV3>   pNormals;     // ������� �������

	int numOfObjects;           // ����� �������� � ������
    vector<t3DObject> Objects;  // �������� �������
public:
	//������������� ������
	t3DModel();

	//�������� ������
	void loadModel(const char * path);

	//����� �������
	void DrawObj(int posx, int posy, int posz);

	//���������� ������� ������. n - ���������� ��������� � ������ ������
	void Print_Objects(int n);

	// set/get
	//����������, ��������� �� ������
	bool GetLoadedModel();

	//������� ������
	void Return_Data(bool &isto_out,
		int &numVerts_out, vector<CV3> &pVerts_out,
		int &numOfObjects_out, vector<t3DObject> &Objects_out) const;
private:
	//������������� ���������� ������
	void InitMaterial(tMaterialInfo &mat);
	//�������� ���������� ������
	void LoadMaterial(const char * path);
	//���������� �������� ������� ������
	void Print_Obj_Faces(const t3DObject &obj, int n);
};

extern std::vector<t3DModel> MODELS_3D;