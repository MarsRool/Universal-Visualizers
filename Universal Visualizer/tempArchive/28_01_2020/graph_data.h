#pragma once
class graph_func;

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