#pragma once
#include "stdafx.h"

double rest(const double &a, const int &b);//������� �� �������
bool Contain(char t, char* in,int schc);//���������� �� ������ t � ������ in ������ schc ��������
bool Contain(char t, const char* in,int schc);//���������� �� ������ t � ������ in ������ schc ��������
void MsgBoxShow(System::String^ msg);
char* outFOPZ(char *instr);
int getprior(char ii);

void LoadErrors(int mode);//�������� ������(����������) �� ??-??errors.ini
void CalculateScreenSize(int &x, int &y);//��������� ���������� � ���������� ������. ������������� � Form1.h void Form1.Activated
void Open_Help();//�������� ������� chm