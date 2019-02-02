#pragma once
#include "stdafx.h"
#include "global.h"

#pragma pack(push, 1)
class graph_func;
class ListOfFuncs
{
private:
	std::vector<char *> names;
	std::vector<char **> Funcs;
public:
	ListOfFuncs();
	void AddFunc(char* namei, char **Funcs_i);
	void Clear();
	char* GetName(int k);
};

class RGB_MR
{
private:
	double color3[3];
public:
	RGB_MR();
	RGB_MR(double colori[3]);
	RGB_MR(double c1, double c2, double c3);
	double getColor(int k);
	void setColor(int k, double colori);
	void operator=(const RGB_MR& right);
};

class graph_data
{
private:
	int k;//���������� �����;
	double **Matr, **nMatr;//�������� ������� z=f(x,y,t), ���������� �����
	bool **Matrnorm;//���������� �� ��������

	friend graph_func;
public:
	graph_data();
	~graph_data();

	void reinit(int i);	
};

class graph_func
{
public:
	//������(1)
	bool failed;//true, ���� �������������� � �������
	bool isFuncDynamic;//true-���� ������� ������������
	bool isfunc;//���� �� ������� �� ���������
	bool isFuncVisible;//true-���� ���� ���������� �������
	
	//�������(2)
	int outsch;//������� �������� � �������� ������
	char str[sostr];//��������� ������
	char strpr[sostr];//��������������� ������
	char outstr[sostr];//�������� ������
	double zmin,zmax;//����������� � ������������ �������� x,y,z

	short int type_of_color;//��� ��������� �������. ��� � GRAPHICS
	RGB_MR color;//�����������(����������) ���� �������
	RGB_MR color_grad[4];//����������� ���� downleft, downright, upleft, upright colors (�� 0.0 �� 1.0)
	RGB_MR color_grad_land[7];//��������. �� ������ �����. ������ �� �������� �� ����������� ������ ����.

	//unsigned int TimeCalcMatrs, TimeCalcChoords;//������� ������� CalculateMatrix � CalculateMatrixOut

private:
	//�������� �����(3)
	graph_data *data;//������ �������.
	int ndata;//���������� ������ �������� �������

public:
	graph_func();
	void Translate(char *instr, int len);
	void testFuncOnDymanic();
	void ClearData();
	void CalculateMatrix(int ngrid, double &xsha, double &ysha, double &tsha, double xmin, double xmax, double ymin, double ymax, int t1, int t2, unsigned int fps, System::Windows::Forms::ProgressBar^ ProgBar);
	void CalculateMatrixOut(int ngrid, bool isautozmax, bool isautozmin);
	void RedrawFunc(int ngrid, const int &modecolor);

	double Min(int ngrid);//������ �����������
	double Max(int ngrid);//�� ���� ������ ���� ������

	void SaveData(FILE *file);
	void LoadData(FILE *file, int ngrid);
private:
	void TranslatingToEquvalentOp();
	void stackmachine();
	double calculate(char inpoutstr[sostr],int sch, double x, double y, double t, int tii, int indi, int indj);
	double counticolor(double a, double b, int c, int k);

	bool CheckOutOfLims(int i, int j, double zmini, double zmaxi);//true - ���� 4 ����� �� ������� �� ������� zmin � zmax {[i,j], [i+1,j], [i,j+1], [i+1,j+1]}
};

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
	/*useless*/bool ClearDataFunc(int k);//�������� ������ �������� ��� ������� k
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