#pragma once
#include "global.h"

#include "RGB.h"
#include "graph_data.h"

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
	double zmin, zmax;//����������� � ������������ �������� x,y,z

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
	double counticolor(double a, double b, int c, int k);
	void TranslatingToEquvalentOp();
	void stackmachine();
	double calculate(char inpoutstr[sostr], int sch, double x, double y, double t, int tii, int indi, int indj);

	bool CheckOutOfLims(int i, int j, double zmini, double zmaxi);//true - ���� 4 ����� �� ������� �� ������� zmin � zmax {[i,j], [i+1,j], [i,j+1], [i+1,j+1]	
};