#include "stdafx.h"
#include "MR_Array.h"
#include "global.h"

MR::Helpers::Array::Array()
{
	size = 0;
	Ptr = nullptr;
}

MR::Helpers::Array::Array(double * Ptr_i, int size_i)
{
	size = size_i;
	Ptr = new double[size];
	for (int i = 0; i < size; i++)
		Ptr[i] = Ptr_i[i];
}

MR::Helpers::Array::Array(const Array & arrayToCopy)
{
	size = arrayToCopy.size;
	Ptr = new double[size];
	for (int i = 0; i < size; i++)
		Ptr[i] = arrayToCopy.Ptr[i];
}

MR::Helpers::Array::~Array()
{
	if (Ptr != nullptr && size != 0)
	{
		size = 0;
		delete Ptr;
		Ptr = nullptr;
	}
}

double & MR::Helpers::Array::at(int k, bool isOk)
{
	if (k >= 0 && k < size)
	{
		return Ptr[k];
	}
	else
	{
		isOk = false;
		double a = 0;
		return a;
	}
}

double MR::Helpers::Array::operator[] (int k)
{
	bool isOk = true;
	return at(k, isOk);
}