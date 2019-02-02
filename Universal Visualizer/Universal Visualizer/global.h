#pragma once
#include "stdafx.h"

//of global
constexpr double PI = 3.14159265;
constexpr double E = 2.71828183;

constexpr char dops[] = ",.0123456789xyt+-*/^()";//���������� �������
constexpr char dopd[] = "scpgqarlfvbimnu";//��������� ��������. ������� ������ (���� ������)//sin, cos, tg, ctg, sqrt
const std::string eqf[15]={//���������� �������� � ������ ������
"sin","cos","tg","ctg","sqrt",
"abs","round","ceil","floor",
"asin","acos","atg","actg",
"ln","log"};

const double smallV=0.001,bigV=1000000;//����� ��������, ������� ��������
const int soarr=101,sostr=1000,sorazm=10;
//(sizeofarr,sizeofstr,sizeofrazmern)������ ������� ��������(�����), ������ ������ � ��������, ������ ����� � ��������

//����
extern int mode_Form1;//����� ���� ���������� �� ����� Form1
extern int mode_FormLoad;//����� ���� ���������� �� ����� Formload
extern int mode_FormDemo;//����� ���� ���������� �� ����� FormDemo
extern int mode_FormProcess;//����� ���� ���������� �� ����� FormProcess
extern std::string Language[2];//����� ������ ��� ��� � ����
extern std::string error_otpfr_func;
extern std::string errors[12];
extern int num_func_calculateing;//����� ������� �� ������ �������������� ������(��� show_errors)