#pragma once
#include "stdafx.h"
#include "global.h"

#include "ListOfFuncs.h"
#include "RGB.h"
#include "graph_data.h"
#include "graph_func.h"

#pragma pack(push, 1)
class graph
{
public:
	int ngrid;//���������� ��������� / ���� ����� (���������� ����� �� 1 ������)
	double xsha,ysha,tsha;//��� ����� �� x � y. ��� �������
	bool IsTimeStartedNow;//true - ���� ������� ������� ������
	double ti;//������� �����
	int t1, t2;//��������� � �������� ����� � ��������

	bool isinitOpenGl;//��������������� OpenGL
	short int modecolor;/*��� ��������� �������.
				  1-������� ������� ������ �������(���������)
				  2-������� ������� ������ �������(����������)
				  3-��������� 4 ������� �� dl,dr,ul,ur.
				  4-��������.*/
	int modeoses;//��� ������������ ����
	int ndeloses;//���������� ������� �� ��� (��� ������ �������������, �.�. �� ��� ���� � ��� ���������)
	bool moderot;//��������� �� ������
	bool modegridgr;//���� �� ����� �� �������
	bool modeistoses;//���� �� ���
	bool modepokaz;//���� �� ��������� ���������� � ���������
	bool istDynamic;//���� �� ���� ���� ������������ �������
	unsigned int fps,ffs;//fps, ������ ������ �����
	RGB_MR color_type1[4];//�� ������ �����. downleft, downright, upleft, upright colors (�� 0.0 �� 1.0)
	RGB_MR color_type2[7];//�� ������ �����. ������ �� �������� �� ����������� ������ ����.
	bool isLoaded;//��������� �� �������� �� �����(���� ��, �� �������� �������� Form1 � ���������� ������ false)

	double Xmin,Xmax,Ymin,Ymax,Zmin,Zmax;//����������� � ������������ �������� x,y,z
	bool isautozmin, isautozmax;//���� �� auto � zmin � zmax

	int nfuncs;//���������� �������.
	graph_func *funcs;//������� � �� ������
	
	bool Failed;//true- ���� ����������� ������� ��������� �� �����

	int scrw, scrh;//������ � ������ ������

	std::string *ErrorsGlobal;//������ ������ ��� �������
	int nvsego_ErrorsGlobal, k_ErrorsGlobal;//����� ��������������� ������, ������� ������ � ��������(��� ��.)
	int mode_Now;//����������, ����� ������ ����

	ListOfFuncs listOfFuncs;//��� �������� (!FileInfo.info)�������� ������ ���������� � �� ������� � ��������� ����
public:
	graph();
	void AddFunc(char *instr, int len, const RGB_MR &colori, System::Windows::Forms::ProgressBar^ ProgBar);
	bool DeleteFunc(int k);//������� ������� ��� ������� k
	bool ReInitFunc(int k, char *instr, int len, const RGB_MR &colori, System::Windows::Forms::ProgressBar^ ProgBar);//������������������ ������� ��� ������� k
	
	void InitErrorsGlobal(int n);
	void SetError(int num);//�������� ������ � ������ ������ GRAPHICS::ErrorsGlobal. n_func-����� ��������� �������(��������� � ����(� ����� ������� ������������ 1)). num-����� ������
	void ShowErrors(System::Windows::Forms::TextBox^ txtb);//������� ������ � TextBox ����� Form_Process
	
	void TestOnDynamics();//�������� �� ������������� ������������ �������
	void FuncsReOut();//���������� ������� � ������(�������� ������������� ������)
	void ReInitColors();//������������� ����� ������� � ���� ���������
	void SetDrawData(unsigned int fpsi);
	void RedrawAll();

	void SaveToFile(const char * name);//��������� �������
	void LoadFromFile(const char * name);//��������� �������
	void SaveToFileInfo(System::String^ FileInfo, char* name);
private:
};
#pragma pack(pop)

extern graph GRAPHICS;