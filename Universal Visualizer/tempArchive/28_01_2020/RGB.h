#pragma once
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
	void setColor(double red, double green, double blue);
	void operator=(const RGB_MR& right);
};