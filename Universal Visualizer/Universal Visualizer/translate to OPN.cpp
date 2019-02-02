#include "stdafx.h"
#include "global.h"
#include "calculate from OPN.h"
#include "func.h"
#include "OpenGL funcs.h"
#include "graph.h"

using namespace std;

graph GRAPHICS;

bool is_StartedChangingLang=false;//�������� �� ����� ��������� �����(��� ���������� ������ �����)
bool is_FinishedLangChanging=false;//true-���� ����� ChL ��������� � ����� ����������� ����� ����� ������� �����.
int mode_Now=0;//����� ���� ������
int mode_Form1=-1;//����� ���� ���������� �� ����� Form1
int mode_FormLoad=-1;//����� ���� ���������� �� ����� FormLoad
int mode_FormDemo=-1;//����� ���� ���������� �� ����� FormDemo
int mode_FormProcess=-1;//����� ���� ���������� �� ����� FormProcess
string Language[2] = { "ru-RU", "en-GB" };
string error_otpfr_func;
string errors[12];
int num_func_calculateing=0;

int cch=0,cop=0;//���-�� �����, ���-�� ��������

stack<char> S;

void IsScobkiCompensed(char str[sostr], bool &failedi)
{//��������������� �� ������
	int i=0,otkr=0,zakr=0;
	while(str[i]!=0)
	{
		if(str[i]=='(')
			otkr++;
		else if(str[i]==')')
			zakr++;
		
		if (zakr > otkr)
		{
			if (failedi == false)
				GRAPHICS.SetError(1);
				//MsgBoxShow(L"������ �� ���������������");/*err1*/
			failedi = true;
		}
		i++;
	}
	if (otkr!=zakr)
	{
		if (failedi == false)
			GRAPHICS.SetError(1);
			//MsgBoxShow(L"������ �� ���������������");/*err1*/
		failedi=true;
	}
}
void graph_func::TranslatingToEquvalentOp()//������ sin->s � ...
{
	char streq[sostr];//����� �������������� ��������������
	int i=0, k=0;
	for (i=0;i<sostr;i++)
		streq[i]=0;

	i=0;
	bool rest=true;//true, ���� ������� ������� ��������������
	while (strpr[i]!=0)
	{
		rest=false;//sin
		if (strpr[i]=='s' && strpr[i+1]=='i' && strpr[i+2]=='n')
		{
			rest=true;
			streq[k]='s';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}//cos
		else if (strpr[i]=='c' && strpr[i+1]=='o' && strpr[i+2]=='s')
		{
			rest=true;
			streq[k]='c';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}//tg
		else if (strpr[i]=='t' && strpr[i+1]=='g')
		{
			rest=true;
			streq[k]='p';
			k++;
			i+=2;
			if (strpr[i]!='(') failed=true;
		}//ctg
		else if (strpr[i]=='c' && strpr[i+1]=='t' && strpr[i+2]=='g')
		{
			rest=true;
			streq[k]='g';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}//sqrt
		else if (strpr[i]=='s' && strpr[i+1]=='q' && strpr[i+2]=='r' && strpr[i+3]=='t')
		{
			rest=true;
			streq[k]='q';
			k++;
			i+=4;
			if (strpr[i]!='(') failed=true;
		}
		//abs
		else if (strpr[i]=='a' && strpr[i+1]=='b' && strpr[i+2]=='s')
		{
			rest=true;
			streq[k]='a';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}//round
		else if (strpr[i]=='r' && strpr[i+1]=='o' && strpr[i+2]=='u' && strpr[i+3]=='n' && strpr[i+4]=='d')
		{
			rest=true;
			streq[k]='r';
			k++;
			i+=5;
			if (strpr[i]!='(') failed=true;
		}//ceil
		else if (strpr[i]=='c' && strpr[i+1]=='e' && strpr[i+2]=='i' && strpr[i+3]=='l')
		{
			rest=true;
			streq[k]='l';
			k++;
			i+=4;
			if (strpr[i]!='(') failed=true;
		}//floor
		else if (strpr[i]=='f' && strpr[i+1]=='l' && strpr[i+2]=='o' && strpr[i+3]=='o' && strpr[i+4]=='r')
		{
			rest=true;
			streq[k]='f';
			k++;
			i+=5;
			if (strpr[i]!='(') failed=true;
		}
		//asin
		else if (strpr[i]=='a' && strpr[i+1]=='s' && strpr[i+2]=='i' && strpr[i+3]=='n')
		{
			rest=true;
			streq[k]='v';
			k++;
			i+=4;
			if (strpr[i]!='(') failed=true;
		}//acos
		else if (strpr[i]=='a' && strpr[i+1]=='c' && strpr[i+2]=='o' && strpr[i+3]=='s')
		{
			rest=true;
			streq[k]='b';
			k++;
			i+=4;
			if (strpr[i]!='(') failed=true;
		}//atg
		else if (strpr[i]=='a' && strpr[i+1]=='t' && strpr[i+2]=='g')
		{
			rest=true;
			streq[k]='i';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}//actg
		else if (strpr[i]=='a' && strpr[i+1]=='c' && strpr[i+2]=='t' && strpr[i+3]=='g')
		{
			rest=true;
			streq[k]='m';
			k++;
			i+=4;
			if (strpr[i]!='(') failed=true;
		}
		//ln
		else if (strpr[i]=='l' && strpr[i+1]=='n')
		{
			rest=true;
			streq[k]='n';
			k++;
			i+=2;
			if (strpr[i]!='(') failed=true;
		}//log
		else if (strpr[i]=='l' && strpr[i+1]=='o' && strpr[i+2]=='g')
		{
			rest=true;
			streq[k]='u';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}
	/*min
		else if (strpr[i]=='m' && strpr[i+1]=='i' && strpr[i+2]=='n')
		{
			rest=true;
			streq[k]='w';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}//max
		else if (strpr[i]=='m' && strpr[i+1]=='a' && strpr[i+2]=='x')
		{
			rest=true;
			streq[k]='y';
			k++;
			i+=3;
			if (strpr[i]!='(') failed=true;
		}*/
		else
		{
			int j=0;
			while (dops[j]!=0)
			{
				if (dops[j]==strpr[i]) 
					rest=true;
				j++;
			}
			if (rest==true)
			{
				streq[k]=strpr[i];
				k++;
				i++;
			}
		}
		if (rest==false)
		{
			if (failed==false)
				GRAPHICS.SetError(2);
				//MsgBoxShow(L"������� �������� ������������ �������");/*err2*/
			failed=true;
			break;
		}
	}
	if (failed==false)
		for (i=0;i<1000;i++)
			strpr[i]=streq[i];
}

void regroupop(char *outstr, int &outsch, short int prins,short int prt,char si)
{//�������(prior), �������(prior,symbol)
 //��������������� ��������
	if (prt==4)
	while (prt<prins)//������������������ ���������
	{
		outstr[outsch]=S.top();
		S.pop();
		outsch++;
		outstr[outsch]=' '; outsch++;
		if (!S.empty())
			prins=getprior(S.top());
		else break;
	}
	else
	while (prt<=prins)//���������
	{
		outstr[outsch]=S.top();
		S.pop();
		outsch++;
		outstr[outsch]=' '; outsch++;
		if (!S.empty())
			prins=getprior(S.top());
		else break;
	}
	S.push(si);
}

void addperem(char *outstr, int &outsch, char chi, bool &failedi)
{
	if ((outstr[outsch-2]>='0' && outstr[outsch-2]<='9')||
		outstr[outsch-2]=='+'||
		outstr[outsch-2]=='-'||
		outstr[outsch-2]=='*'||
		outstr[outsch-2]=='/'||
		outstr[outsch-2]=='^'||
		outstr[outsch-2]=='x'||
		outstr[outsch-2]=='y'||
		outstr[outsch-2]=='t'||

		outstr[outsch-2]=='s'||
		outstr[outsch-2]=='c'||
		outstr[outsch-2]=='p'||
		outstr[outsch-2]=='g'||
		outstr[outsch-2]=='q'||

		outstr[outsch-2]=='a'||
		outstr[outsch-2]=='r'||
		outstr[outsch-2]=='l'||
		outstr[outsch-2]=='f'||

		outstr[outsch-2]=='v'||
		outstr[outsch-2]=='b'||
		outstr[outsch-2]=='i'||
		outstr[outsch-2]=='m'||

		outstr[outsch-2]=='n'||
		outstr[outsch-2]=='u'||
		outsch==0)
	{
		outstr[outsch]=chi;outsch++;outstr[outsch]=' '; outsch++;
		/*if ((outstr[outsch-4]>='0' && outstr[outsch-4]<='9') || outstr[outsch-4]=='x'|| outstr[outsch-4]=='y') 
			{
				outstr[outsch]='*';outsch++;outstr[outsch]=' '; outsch++;
			}*/
	}
	else
	{
		if (failedi==false)
			GRAPHICS.SetError(2);
			//MsgBoxShow(L"������� �������� ������������ �������");/*err2*/
		failedi=true;
	}
}

void vst(char *instr,char chi,int jj)//�������� ������ � jj ������� (����� ����� ��������� ����������)
{
	for(int j=999;j>=jj;j--)
		instr[j+1]=instr[j];
	instr[jj]=chi;
}

void graph_func::stackmachine()//������������� � ���
{
	int i=0;
	IsScobkiCompensed(strpr, failed);
	if (failed == true)
		return;
	cch=0;
	cop=0;
	bool isoper=false;//�������� �� ������� ������ ���������
	bool isch=false;//����� �� ������� ������
	char ich[50];//������� �����
	bool isunminus=false; //���� �� ������� �����, ����������� � �����
	short int priort;//��������� �������� �������

	if (strpr[0]=='-' && ((strpr[1]>='0' && strpr[1]<='9') || (strpr[1]=='x') || (strpr[1]=='y') || (Contain(strpr[1], dopd, 15) == true)))
		vst(strpr,'0',0);
	
	i=-1;
	while (strpr[i+1]!='\0')
	{
		i++;
		if(strpr[i]=='(' && strpr[i+1]=='-'){
			vst(strpr,'0',i+1);i++;}
	}
	i=-1;
	/*while (strpr[i+1]!='\0')
	{
		i++;
		cout << strpr[i];
	}*/
	//cout << endl;
	bool cnch=false;//���������� �� � ������� ������ �����
	for (i=0;i<=9;i++)
		if (Contain(i+'0',strpr,sostr)==true)
			cnch=true;
	if (!(Contain('x',strpr,sostr)==true || Contain('y',strpr,sostr)==true || Contain('t',strpr,sostr)==true || cnch==true) || strpr[0]==0)
	{
		if (failed==false)
			GRAPHICS.SetError(3);
			//MsgBoxShow(L"������� �� �������� ���������� � ����� ���� ������");/*err3*/
		failed=true;
	}//��������� �� �������� ���������� � ����� ���� ������
	i=0;
	while (strpr[i+1]!='\0')
	{
		i++;
		if (strpr[i]=='x'){
			if ((strpr[i-1]>='0' && strpr[i-1]<='9') || strpr[i-1]=='y' || strpr[i-1]=='t')
				vst(strpr,'*',i);}
		else if (strpr[i]=='y'){
			if ((strpr[i-1]>='0' && strpr[i-1]<='9') || strpr[i-1]=='x' || strpr[i-1]=='t')
				vst(strpr,'*',i);}
		else if (strpr[i]=='t'){
			if ((strpr[i-1]>='0' && strpr[i-1]<='9') || strpr[i-1]=='x' || strpr[i-1]=='y')
				vst(strpr,'*',i);}
		else if ((Contain(strpr[i], dopd, 15) == true)){
			if ((strpr[i-1]>='0' && strpr[i-1]<='9') || strpr[i-1]=='x' || strpr[i-1]=='y' || strpr[i-1]=='t')
				vst(strpr,'*',i);}
	}
    i=-1;
	int j=0;//������� ��������� ������(i-�� �������), ������� ����������� �������� �����
	while (strpr[i+1]!='\0')
    {
        i++;
		while (strpr[i]==32 || strpr[i]==13 || strpr[i]==10)
			i++;
		if (strpr[i]==0)
			break;

		if ((strpr[i]>='0' && strpr[i]<='9')||strpr[i]==','||strpr[i]=='.'){
			if (isch==true){if (strpr[i]>='0' && strpr[i]<='9') ich[j]=strpr[i]; else ich[j]=','; j++;}
			else{isch=true; j=0; ich[j]=strpr[i];j++;}

			if (!(strpr[i+1]>='0' && strpr[i+1]<='9') && strpr[i+1]!=',' && strpr[i+1]!='.'){ 
				for(int l=0;l<j;l++){
					if (ich[0]==',' || ich[j-1]==',')
						{
							if (failed==false)
								GRAPHICS.SetError(4);
								//MsgBoxShow(L"����� � ����� ���������� ��������");/*err4*/
							failed=true;
						}//����� ���������� ��������!!!!!!!!!!!!!!!!!!
					outstr[outsch]=ich[l];outsch++;}
					outstr[outsch]=' '; outsch++;cch++;}
		isoper=false;
		}
		else{
			isch=false;
				short int priorinsi;//��������� �������, �������� �� ������� �����
				if (!S.empty())
					priorinsi=getprior(S.top());
				else priorinsi=0;
				if (priorinsi==1000)
				{
					if (failed==false)
						GRAPHICS.SetError(2);
						//MsgBoxShow(L"������� �������� ������������ �������");/*err2*/
					failed=true;} //error in stack!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				
				priort=getprior(strpr[i]);//��������� �������� �������
				if (priort==1000)
				{
					if (failed==false)
						GRAPHICS.SetError(2);
						//MsgBoxShow(L"������� �������� ������������ �������");/*err2*/
					failed=true;
				} //error in prior, �� ��������
				
				if (isoper==true && priort!=-1 && priort!=1000 && priort!=1 && priort!=5) 
				{
					if (failed==false)
						GRAPHICS.SetError(5);
						//MsgBoxShow(L"��� �������� ������");/*err5*/
					failed=true;
				}//��� �������� ������!!!!!!!!!!!!!!!!!!!!!!!!!!
				if (priort!=-1 && priort!=1000 && priort!=1)
					isoper=true;
				else
					isoper=false;
			switch(strpr[i])
			{
				case 'x':{addperem(outstr,outsch,'x', failed);cch++;}break;
				case 'y':{addperem(outstr,outsch,'y', failed);cch++;}break;
				case 't':{addperem(outstr,outsch,'t', failed);cch++;}break;
				case '+':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;}break;
				case '-':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;}break;
				case '*':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;}break;
				case '/':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;}break;
				case '^':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;}break;

				case 's':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'c':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'p':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'g':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'q':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;

				case 'a':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'r':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'l':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'f':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;

				case 'v':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'b':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'i':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'm':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;

				case 'n':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;
				case 'u':{regroupop(outstr,outsch,priorinsi,priort,strpr[i]);cop++;cch++;}break;

				case '(':S.push(strpr[i]);break;
				case ')':
					{
						char c=S.top();
						S.pop();
						while (c!='(')//���� ��� ( ������ �� ����� ����� �������� � �������� ������
						{
							outstr[outsch]=c;outsch++;
							outstr[outsch]=' '; outsch++;
							c=S.top();
							S.pop();
						}
					}break;
			}
		}
    }

	while (!S.empty())
	{
		outstr[outsch]=S.top();
		S.pop();
		outsch++;
		outstr[outsch]=' '; outsch++;
	}
//�������� �� ��, ��� �������� ������ ���� ������, ��� ����� 2-5-3*2
	if (cch-cop!=1)
	{
		if (failed==false)
			GRAPHICS.SetError(6);
			//MsgBoxShow(L"������������ ���� �������");/*err6*/
		failed=true;
	}
}