#pragma once
#include "stdafx.h"

double rest(const double &a, const int &b);//остаток от деления
bool Contain(char t, char* in,int schc);//содержится ли символ t в строке in длиной schc символов
bool Contain(char t, const char* in,int schc);//содержится ли символ t в строке in длиной schc символов
void MsgBoxShow(System::String^ msg);
char* outFOPZ(char *instr);
int getprior(char ii);

void LoadErrors(int mode);//загрузка ошибок(исключений) из ??-??errors.ini
void CalculateScreenSize(int &x, int &y);//получение информации о разрешении экрана. Инициализация в Form1.h void Form1.Activated
void Open_Help();//открытие справки chm

//of 3D Model
char* find_folder(const char* ins, int &nout);
double findDoubleInStr(char *ins, int length, char **insAfterDouble = NULL);//возвращает первое содержащееся в строке число. ins - строка количеством байт в length+1. insAfterDouble - ссылка на строку после double