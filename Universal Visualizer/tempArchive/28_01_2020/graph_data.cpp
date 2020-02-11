#include "stdafx.h"
#include "global.h"
#include "conversions.h"
#include "func.h"
#include "calculate from OPN.h"
#include "graph_data.h"

graph_data::graph_data()
{
	k = 1;
	Matr = new double*[k];
	nMatr = new double*[k];
	Matrnorm = new bool*[k];

	Matr[0] = new double[k];
	nMatr[0] = new double[k];
	Matrnorm[0] = new bool[k];
}

graph_data::~graph_data()
{
	for (int j = 0; j < k; j++)
	{
		delete[] Matr[j];
		delete[] nMatr[j];
		delete[] Matrnorm[j];
	}
}

void graph_data::reinit(int i)
{
	for (int j = 0; j < k; j++)
	{
		delete[] Matr[j];
		delete[] nMatr[j];
		delete[] Matrnorm[j];
	}

	k = fabs((float)i);
	Matr = new double*[k];
	nMatr = new double*[k];
	Matrnorm = new bool*[k];

	for (int j = 0; j < k; j++)
	{
		Matr[j] = new double[k];
		nMatr[j] = new double[k];
		Matrnorm[j] = new bool[k];
	}
}