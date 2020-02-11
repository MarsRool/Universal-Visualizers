#pragma once
#include "global.h"

#include "RGB.h"
#include "graph_data.h"

class graph_func
{
public:
	//данные(1)
	bool failed;//true, если преобразование с ошибкой
	bool isFuncDynamic;//true-если функция динамическая
	bool isfunc;//есть ли функция на отрисовку
	bool isFuncVisible;//true-если надо отрисовать функцию

	//функция(2)
	int outsch;//сколько символов в конечной строке
	char str[sostr];//введенная строка
	char strpr[sostr];//преобразованная строка
	char outstr[sostr];//выходная строка
	double zmin, zmax;//минимальные и максимальные значения x,y,z

	short int type_of_color;//тип раскраски функции. как в GRAPHICS
	RGB_MR color;//стандартный(монотонный) цвет функции
	RGB_MR color_grad[4];//градиентный цвет downleft, downright, upleft, upright colors (от 0.0 до 1.0)
	RGB_MR color_grad_land[7];//ландшафт. по второй схеме. радуга от красного до фиолетового сверху вниз.

	//unsigned int TimeCalcMatrs, TimeCalcChoords;//времена расчета CalculateMatrix и CalculateMatrixOut

private:
	//значения сетки(3)
	graph_data *data;//данные функции.
	int ndata;//количество матриц значений функции

public:
	graph_func();
	void Translate(char *instr, int len);
	void testFuncOnDymanic();
	void ClearData();
	void CalculateMatrix(int ngrid, double &xsha, double &ysha, double &tsha, double xmin, double xmax, double ymin, double ymax, int t1, int t2, unsigned int fps, System::Windows::Forms::ProgressBar^ ProgBar);
	void CalculateMatrixOut(int ngrid, bool isautozmax, bool isautozmin);
	void RedrawFunc(int ngrid, const int &modecolor);

	double Min(int ngrid);//расчет экстремумов
	double Max(int ngrid);//по всем данным всех времен

	void SaveData(FILE *file);
	void LoadData(FILE *file, int ngrid);
private:
	double counticolor(double a, double b, int c, int k);
	void TranslatingToEquvalentOp();
	void stackmachine();
	double calculate(char inpoutstr[sostr], int sch, double x, double y, double t, int tii, int indi, int indj);

	bool CheckOutOfLims(int i, int j, double zmini, double zmaxi);//true - если 4 точки не выходят за пределы zmin и zmax {[i,j], [i+1,j], [i,j+1], [i+1,j+1]	
};