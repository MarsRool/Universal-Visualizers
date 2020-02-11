#include "stdafx.h"
#include "global.h"
#include "func.h"
#include <windows.h>
#include "conversions.h"
using namespace std;

/*old
unsigned char * dtuch(double a)//double to unsigned char[]
{
	unsigned char cha[23], *ch;//cha-����� � ������� ��������, ch- �����
	short int i = 0;//������� �������� � cha
	double drob;//������� ����� �����
	double cel;//����� ����� �����
	bool ismn = false;//true - ���� ������������� �����
	drob = modf(a, &cel);
	int drob100 = (int)(100 * drob);//
	if (a < 0)
	{
		ismn = true;
		cel = fabs(cel);
		drob100 = fabs((float)drob100);
	}
	if (drob != 0)
	{
		i = 3;
		cha[0] = '0' + drob100 % 10;
		cha[1] = '0' + (int)(drob100 / 10);
		cha[2] = ',';
	}
	if (cel == 0)
	{
		i++;
		cha[i - 1] = '0';
	}
	else
		while (fabs((float)cel) > 0)
		{
			i++;
			cha[i - 1] = '0' + (int)rest(cel, 10);//+������� ������� �� 10
			modf(cel / 10, &cel);
		}
	if (ismn == true)
	{
		i++;
		cha[i - 1] = '-';
	}
	ch = new unsigned char[i + 1];
	ch[i] = '\0';
	for (int j = i - 1; j >= 0; j--)
		ch[j] = cha[i - j - 1];
	return ch;
}*/

unsigned char * dtuch(double a, int precision)//double to unsigned char[]
{
	unsigned char cha[64], *ch;//cha-����� � ������� ��������, ch- �����
	short int i = 0;//������� �������� � cha
	double drob;//������� ����� �����
	double cel;//����� ����� �����
	bool ismn = false;//true - ���� ������������� �����
	drob = modf(fabs(a), &cel);
	int drob_10N = int(drob * pow(10, precision));//������� �����, ���������� �� 10^precision
	int cel_int = (int)cel;//����� ����� ���� int
	if (a < 0)
	{
		ismn = true;
	}
	if (drob != 0)
	{
		i = precision + 1;
		for (int j = 0; j < precision; j++)
		{
			cha[j] = '0' + drob_10N % 10;
			drob_10N /= 10;
		}
		cha[precision] = '.';
	}
	if (cel == 0)
	{
		i++;
		cha[i - 1] = '0';
	}
	else
		while (cel_int > 0)
		{
			i++;
			cha[i - 1] = '0' + cel_int % 10;//+������� ������� �� 10
			cel_int /= 10;
		}
	if (ismn == true)
	{
		i++;
		cha[i - 1] = '-';
	}
	ch = new unsigned char[i + 1];
	ch[i] = '\0';
	for (int j = i - 1; j >= 0; j--)
		ch[j] = cha[i - j - 1];
	return ch;
}

double uchtd(unsigned char * ch, bool &failed)
{
	double res = 0;
	bool ismn = false;//������������� �� �����
	int n = 0;//����� ch
	while (ch[n] != '\0' && n < 64)
		n++;

	if (!(ch[0] == '-' || (ch[0] >= '0' && ch[0] <= '9')) || ch[n - 1] == '.' || ch[n - 1] == ',')
		failed = true;

	int i_dot = -1;
	for (int i = 1; i < n; i++)
		if (!(ch[i] >= '0' && ch[i] <= '9'))
		{
			if ((ch[i] == '.' || ch[i] == ',') && i_dot == -1)
				i_dot = i;
			else
			{
				failed = true;
				break;
			}
		}

	if (failed == false)
	{
		if (ch[0] == '-')
			ismn = true;
		if (i_dot == -1)
		{
			for (int i = 0; i < n; i++)
				if (ch[i] != '-')
					res = res * 10 + ch[i] - '0';
		}
		else
		{
			for (int i = 0; i < i_dot; i++)
				if (ch[i] != '-')
					res = res * 10 + ch[i] - '0';
			for (int i = i_dot + 1; i < n; i++)
				res = res + double(ch[i] - '0') / pow(10.0, i - i_dot);
		}
	}
	if (ismn == false)
		return res;
	else
	{
		res = -res;
		return res;
	}
	if (failed == true)
		return 0;
}

unsigned char * ituch(int a)
{
	return dtuch(a, 0);
}

int uchti(unsigned char * ch, bool &failed)
{
	double res = uchtd(ch, failed), cel;
	double drob = modf(fabs(res), &cel);
	if (drob != 0)
	{
		failed = true;
		return 0;
	}
	return int(res);
}

double StrToD(bool &failed, System::String^ stri)//System::String^ to Double
{
	double res=0;
	char chstr[sostr] = "";
	bool ismn=false;//������������� �� �����
	int n = stri->Length;
	for (int i=0;i<n+10;i++)
		chstr[i]=0;
	for (int i=0;i<n;i++)
		chstr[i]=(char)stri[i];

	if (!(chstr[0]=='-' || (chstr[0]>='0' && chstr[0]<='9')) || chstr[n]=='.' || chstr[n]==',')
		failed=true;
	else
	{
		if (chstr[0]=='-')
			ismn=true;
		if (Contain('.',chstr,n)==false && Contain(',',chstr,n)==false)
		{
			for (int i=0;i<n;i++)
				if(chstr[i]!='-')
				{
					if (!(chstr[i]>='0' && chstr[i]<='9'))
						failed=true;
					res=res*10+chstr[i]-'0';
				}
		}
		else
		{
			int posd=0;
			for (int i=0;i<n;i++)
				if(chstr[i]=='.' || chstr[i]==',')
				{
					posd=i;
					break;
				}
			chstr[n+1]='0';
			for(int i=posd+1;i<=n+1;i++)
				chstr[i-1]=chstr[i];
			int k=posd+3;
			for (int i=0;i<k;i++)
				if(chstr[i]!='-')
				{
					if (!(chstr[i]>='0' && chstr[i]<='9' || chstr[i]==0))
						failed=true;
					if (chstr[i]==0)
						res=res*10;
					else
						res=res*10+chstr[i]-'0';
				}
				res/=1000;
		}
	}
	if (ismn==false)
		return res;
	else
	{
		res=-res;
		return res;
	}
	if (failed==true) return 0;
}

unsigned char * chTouch(char * ch)
{
	int count = -1;
	while (ch[++count] != 0);
	unsigned char *out = new unsigned char[count + 1];
	unsigned char test = (unsigned char)'�';
	for (int i = 0; i <= count; i++)
	{
		if (ch[i] < 0)
			out[i] = (unsigned char)(128 - ch[i]);
		else
			out[i] = (unsigned char)ch[i];
	}
	return out;
}

char * uchToch(unsigned char * uch)
{
	int count = -1;
	while (uch[++count] != 0);
	char *out = new char[count + 1];
	for (int i = 0; i <= count; i++)
	{
		if (uch[i] > 127)
			out[i] = (char)(128 - uch[i]);
		else
			out[i] = (char)uch[i];
	}
	return out;
}

System::String^ uchToStr(unsigned char * ch)//unsigned char[] to System::String^
{
	int i=0;
	System::String^ stri = L"";
	while (ch[i]!=0)
	{
	stri+=(wchar_t)ch[i];
	i++;
	}
	return stri;
}

unsigned char * StrTouch(System::String^ stri)//System::String^ to unsigned char[]
{
	int l = stri->Length;
	unsigned char * ch = new unsigned char[l + 1];
	for (int i = 0; i < l; i++)
		ch[i] = unsigned char(stri[i]);
	ch[l] = '\0';
	return ch;
}

string uchTostr(unsigned char * ch)//unsigned char[] to string
{
	int i = 0;
	string stri = "";
	while (ch[i]!=0)
	{
		stri += char(ch[i]);
		i++;
	}
	return stri;
}

unsigned char * strTouch(string stri)//string to unsigned char[]
{
	int l = stri.length();
	unsigned char * ch = new unsigned char[l + 1];
	for (int i = 0; i < l; i++)
		ch[i] = unsigned char(stri[i]);
	ch[l] = '\0';
	return ch;
}

System::String^ ChToStr(char * ch)//Char[] to System::String^
{
	int i = 0;
	System::String^ stri = L"";
	while (ch[i]!=0)
	{
		if (ch[i] == -88)
			stri += L'�';
		else if (ch[i] == -72)
			stri += L'�';
		else if (ch[i] >= -64 && ch[i] <= -1)
			stri += wchar_t(ch[i] + 1104);
		else
			stri += wchar_t(ch[i]);
		i++;
	}

	return stri;
}

char * StrToCh(System::String^ Str)//System::String^ to Char[]
{
	int l = Str->Length;
	char * ch = new char[l + 1];
	for (int i = 0; i < l; i++)
	{
		if (Str[i] == 1025)
			ch[i] = '�';
		else if (Str[i] == 1105)
			ch[i] = '�';
		else if (Str[i] >= 1040 && Str[i] <= 1103)
			ch[i] = Str[i] - 1104;
		else
			ch[i] = (char)Str[i];
	}
	ch[l] = '\0';
	return ch;
}

string ChTostr(char * ch)//char[] to string
{
	int i = 0;
	string stri = "";
	while (ch[i] != 0)
	{
		stri += ch[i];
		i++;
	}
	return stri;
}

char * strToCh(string stri)//string to char[]
{
	int l = stri.length();
	char * ch = new char[l + 1];
	for (int i = 0; i < l; i++)
		ch[i] = stri[i];
	ch[l] = '\0';
	return ch;
}

string StrTostr(System::String^ Str)//System::String^ to string
{
	int l = Str->Length;
	string stri = "";
	for (int i=0; i<l; i++)
	{
		if (Str[i] == 1025)
			stri += '�';
		else if (Str[i] == 1105)
			stri += '�';
		else if (Str[i] >= 1040 && Str[i] <= 1103)
			stri += Str[i] - 1104;
		else
			stri += (char)Str[i];
	}
	return stri;
}

System::String^ strToStr(string stri)//string to System::String^
{
	int l = stri.length();
	System::String^ Str = L"";
	for (int i=0; i<l; i++)
	{
		if (stri[i] == -88)
			Str += L'�';
		else if (stri[i] == -72)
			Str += L'�';
		else if (stri[i] >= -64 && stri[i] <= -1)
			Str += wchar_t(stri[i] + 1104);
		else
			Str += wchar_t(stri[i]);
	}
	return Str;
}

wchar_t * chToWch(char * ch)
{
	int count = -1;
	while (ch[++count] != 0);
	wchar_t *out = new wchar_t[count + 1];
	for (int i = 0; i <= count; i++)
	{
		if (ch[i] == -88)
			out[i] = L'�';
		else if (ch[i] == -72)
			out[i] = L'�';
		else if (ch[i] >= -64 && ch[i] <= -1)
			out[i] = wchar_t(ch[i] + 1104);
		else
			out[i] = wchar_t(ch[i]);
	}
	return out;
}

char * WchToch(wchar_t * wch)
{
	int count = -1;
	while (wch[++count] != 0);
	char *out = new char[count + 1];
	for (int i = 0; i <= count; i++)
	{
		if (wch[i] == 1025)
			out[i] = '�';
		else if (wch[i] == 1105)
			out[i] = '�';
		else if (wch[i] >= 1040 && wch[i] <= 1103)
			out[i] = wch[i] - 1104;
		else
			out[i] = (char)wch[i];
	}
	return out;
}

wchar_t * StrToWch(System::String ^ Str)
{
	wchar_t* out = new wchar_t[Str->Length + 1];
	for (int i = 0; i < Str->Length; i++)
		out[i] = Str[i];
	out[Str->Length] = L'\0';
	return out;
}

System::String ^ WchToStr(wchar_t * wch)
{
	System::String^ str = L"";
	int i = -1;
	while (wch[++i] != 0)
		str += wch[i];
	return str;
}
