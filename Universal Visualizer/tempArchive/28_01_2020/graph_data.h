#pragma once
class graph_func;

class graph_data
{
private:
	int k;//количество точек;
	double **Matr, **nMatr;//значения матрицы z=f(x,y,t), координаты точек
	bool **Matrnorm;//допустимое ли значение

	friend graph_func;
public:
	graph_data();
	~graph_data();

	void reinit(int i);
};