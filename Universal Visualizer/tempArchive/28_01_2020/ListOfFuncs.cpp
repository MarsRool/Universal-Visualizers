#include "stdafx.h"
#include "global.h"
#include "conversions.h"
#include "func.h"
#include "calculate from OPN.h"
#include "ListOfFuncs.h"

ListOfFuncs::ListOfFuncs()
{
	names = {};
	Funcs = {};
}

void ListOfFuncs::AddFunc(char* namei, char **Funcs_i)
{
	names.push_back(namei);
	Funcs.push_back(Funcs_i);
}

void ListOfFuncs::Clear()
{
	names.clear();
	Funcs.clear();
}

char* ListOfFuncs::GetName(int k)
{
	return names.at(k);
}