#pragma once
#include "stdafx.h"

unsigned char * dtuch(double a, int precision = 2);//double to unsigned char[]
double uchtd(unsigned char* ch, bool &failed);//unsigned char[] to double

unsigned char * ituch(int a);//int to unsigned char[]
int uchti(unsigned char* ch, bool &failed);//unsigned char[] to int

double StrToD(bool &failed, System::String^ stri);//System::String^ to double

unsigned char * chTouch(char* ch);//unsigned char[] to char[]
char * uchToch(unsigned char* uch);//char[] to unsigned char[]

System::String^ uchToStr(unsigned char * ch);//unsigned char[] to System::String^
unsigned char * StrTouch(System::String^ stri);//System::String^ to unsigned char[]

std::string uchTostr(unsigned char * ch);//unsigned char[] to string
unsigned char * strTouch(std::string stri);//string to unsigned char[]

System::String^ ChToStr(char * ch);//unsigned char[] to System::String^
char * StrToCh(System::String^ stri);//System::String^ to unsigned char[]

std::string ChTostr(char * ch);//char[] to string
char * strToCh(std::string stri);//string to char[]

std::string StrTostr(System::String^ Str);//System::String^ to string
System::String^ strToStr(std::string stri);//string to System::String^

wchar_t* chToWch(char* ch);//char* to wchar_t*
char* WchToch(wchar_t* wch);//whar_t* to char*

wchar_t* StrToWch(System::String^ Str);
System::String^ WchToStr(wchar_t* wch);