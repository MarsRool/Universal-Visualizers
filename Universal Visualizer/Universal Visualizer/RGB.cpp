#include "stdafx.h"
#include "global.h"
#include "RGB.h"

void RGB_MR::operator=(const RGB_MR& right)
{
	for (int i = 0; i < 3; i++)
		color3[i] = right.color3[i];
}

RGB_MR::RGB_MR()
{
	for (int i = 0; i < 3; i++)
		color3[i] = 0;
}

RGB_MR::RGB_MR(double colori[3])
{
	for (int i = 0; i < 3; i++)
		if (colori[i] > 1.0)
			color3[i] = 1;
		else if (colori[i] < 0)
			color3[i] = 0;
		else
			color3[i] = colori[i];
}

RGB_MR::RGB_MR(double c1, double c2, double c3)
{
	if (c1 > 1.0)
		color3[0] = 1;
	else if (c1 < 0)
		color3[0] = 0;
	else
		color3[0] = c1;

	if (c2 > 1.0)
		color3[1] = 1;
	else if (c2 < 0)
		color3[1] = 0;
	else
		color3[1] = c2;

	if (c3 > 1.0)
		color3[2] = 1;
	else if (c3 < 0)
		color3[2] = 0;
	else
		color3[2] = c3;
}

double RGB_MR::getColor(int k)
{
	if (k >= 0 && k < 3)
		return color3[k];
	else
		return 0.0;
}

void RGB_MR::setColor(int k, double colori)
{
	color3[k] = colori;
}

void RGB_MR::setColor(double red, double green, double blue)
{
	color3[0] = red;
	color3[1] = green;
	color3[2] = blue;
}