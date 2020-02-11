#include "stdafx.h"
#include "global.h"
#include "conversions.h"
#include "func.h"
#include "calculate from OPN.h"
#include "graph_func.h"

graph_func::graph_func()
{
	ndata = 0;
	ClearData();
}

void graph_func::Translate(char *instr, int len)
{
	for (int i = 0; i < len; i++)
	{
		str[i] = instr[i];//введенная строка
		strpr[i] = instr[i];//введенная строка
	}
	TranslatingToEquvalentOp();
	stackmachine();
}

void graph_func::ClearData()
{
	//данные
	failed = false;//true, если преобразование с ошибкой
	isFuncDynamic = false;//true- если функция динамичная
	isfunc = false;//есть ли функция на отрисовку
	isFuncVisible = true;//true-если надо отрисовать функцию

	//функция(1)
	outsch = 0;//сколько символов в конечной строке
	for (int i = 0; i < 1000; i++)
	{
		str[i] = 0;//введенная строка
		strpr[i] = 0;//преобразованная строка
		outstr[i] = 0;//выходная строка
	}

	//значения сетки(3)
	if (ndata > 0)
		delete[] data;
	data = NULL;
	ndata = 0;//количество матриц значений функции
	zmin = 0;
	zmax = 0;

	type_of_color = 0;
	color = RGB_MR(0.0, 0.0, 0.0);

	color_grad[0] = RGB_MR(1.0, 0.0, 0.0);
	color_grad[1] = RGB_MR(0.0, 1.0, 0.0);
	color_grad[2] = RGB_MR(0.0, 0.0, 1.0);
	color_grad[3] = RGB_MR(0.0, 0.0, 0.0);

	color_grad_land[0] = RGB_MR(1.0, 0.06, 0.06);
	color_grad_land[1] = RGB_MR(1.0, 0.5, 0.06);
	color_grad_land[2] = RGB_MR(1.0, 0.95, 0.06);
	color_grad_land[3] = RGB_MR(0.06, 0.85, 0.06);
	color_grad_land[4] = RGB_MR(0.06, 0.95, 1.0);
	color_grad_land[5] = RGB_MR(0.06, 0.4, 1.0);
	color_grad_land[6] = RGB_MR(0.5, 0.06, 0.5);
}

void graph_func::testFuncOnDymanic()
{
	if (Contain('t', outstr, outsch) == true)
		isFuncDynamic = true;
}

void graph_func::SaveData(FILE *file)
{
	fprintf(file, "%i\n", ndata);//ndata
	for (int i = 0; i < ndata; i++)
	{
		fprintf(file, "%i\n", data[i].k);//k
		for (int j = 0; j < data[i].k; j++)//Matr
			for (int l = 0; l < data[i].k; l++)
				fprintf(file, "%lf;", data[i].Matr[j][l]);
		fprintf(file, "\n");
		for (int j = 0; j < data[i].k; j++)//nMatr
			for (int l = 0; l < data[i].k; l++)
				fprintf(file, "%lf;", data[i].nMatr[j][l]);
		fprintf(file, "\n");
		for (int j = 0; j < data[i].k; j++)//Matrnorm
			for (int l = 0; l < data[i].k; l++)
				fprintf(file, "%i;", data[i].Matrnorm[j][l]);
		fprintf(file, "\n");
	}
}

void graph_func::LoadData(FILE *file, int ngrid)
{
	fscanf_s(file, "%i\n", &ndata);//ndata
	if (data != NULL)
		delete[] data;
	data = new graph_data[ndata];
	for (int i = 0; i < ndata; i++)
		data[i].reinit(ngrid + 1);
	for (int i = 0; i < ndata; i++)
	{
		fscanf_s(file, "%i\n", &data[i].k);//k
		for (int j = 0; j < data[i].k; j++)//Matr
			for (int l = 0; l < data[i].k; l++)
				fscanf_s(file, "%lf;", &data[i].Matr[j][l]);
		fscanf_s(file, "\n");
		for (int j = 0; j < data[i].k; j++)//nMatr
			for (int l = 0; l < data[i].k; l++)
				fscanf_s(file, "%lf;", &data[i].nMatr[j][l]);
		fscanf_s(file, "\n");
		for (int j = 0; j < data[i].k; j++)//Matrnorm
			for (int l = 0; l < data[i].k; l++)
				fscanf_s(file, "%i;", &data[i].Matrnorm[j][l]);
		fscanf_s(file, "\n");
	}
}