#include "stdafx.h"
#include "global.h"
#include "conversions.h"
#include "func.h"
#include "calculate from OPN.h"
#include "graph.h"
#include "OpenGL funcs.h"

graph::graph()
{
	ngrid=32;//количество полигонов / одно ребро (количество точек на 1 больше)
	xsha,ysha;//шаг сетки по x и y
	IsTimeStartedNow = false;//true - если процесс запущен сейчас
	ti = 0;//текущее время
	t1 = 0; t2 = 0;//начальное и конечное время в секундах

	isinitOpenGl = false;//инициализирован OpenGL
	modecolor = 0;//тип раскраски функции
	modeoses = 2;//тип расположения осей
	ndeloses = 4;//количество делений на оси (для начала промежуточных, т.е. не при макс и мин значениях)
	moderot = true;//Вращается ли график
	modegridgr = true;//есть ли сетка на графике
	modeistoses = true;//есть ли оси
	modepokaz = true;//есть ли показания максимумов и минимумов
	isLoaded = false;//произошла ли загрузка из файла(если да, то обносить элементы Form1 и установить равным false)
	fps = 25; ffs = 9;//fps, размер шрифта формы
	color_type1[0] = RGB_MR(1.0, 0.0, 0.0);
	color_type1[1] = RGB_MR(0.0, 1.0, 0.0);
	color_type1[2] = RGB_MR(0.0, 0.0, 1.0);
	color_type1[3] = RGB_MR(0.0, 0.0, 0.0);

	color_type2[0] = RGB_MR(1.0, 0.06, 0.06);
	color_type2[1] = RGB_MR(1.0, 0.5, 0.06);
	color_type2[2] = RGB_MR(1.0, 0.95, 0.06);
	color_type2[3] = RGB_MR(0.06, 0.85, 0.06);
	color_type2[4] = RGB_MR(0.06, 0.95, 1.0);
	color_type2[5] = RGB_MR(0.06, 0.4, 1.0);
	color_type2[6] = RGB_MR(0.5, 0.06, 0.5);

	//параметры сетки
	Xmin=-1.0, Xmax=1.0, Ymin=-1.0, Ymax=1.0;//минимальные и максимальные значения x,y,z
	isautozmin = true, isautozmax = true;//есть ли auto в zmin и zmax

	nfuncs = 0;//количество функций.
	funcs = NULL;//установить указатель на функции в нуль
}

void graph::InitErrorsGlobal(int n)
{
	ErrorsGlobal = new std::string[n];
	for (int i=0; i<n; i++)
		ErrorsGlobal[i]="";
	nvsego_ErrorsGlobal=n;
	k_ErrorsGlobal=0;
}

void graph::AddFunc(char *instr, int len, const RGB_MR &colori, System::Windows::Forms::ProgressBar^ ProgBar)
{
	nfuncs++;
	int k = sizeof(graph_data);
	int n = sizeof(graph_func);
	int l = sizeof(graph_data*);
	graph_func* temp = funcs;
	funcs = new graph_func[nfuncs];
	for (int i = 0; i < nfuncs - 1; i++)
		funcs[i] = temp[i];
	delete temp;
	//funcs = (graph_func*) realloc (funcs, nfuncs*sizeof(graph_func));
	num_func_calculateing=nfuncs-1;//для ошибок
	funcs[nfuncs - 1].ClearData();
	funcs[nfuncs - 1].Translate(instr, len);
	funcs[nfuncs - 1].testFuncOnDymanic();
	funcs[nfuncs - 1].CalculateMatrix(ngrid, xsha, ysha, tsha, Xmin, Xmax, Ymin, Ymax, t1, t2, fps, ProgBar);
	funcs[nfuncs - 1].color = colori;
	num_func_calculateing=0;//для ошибок
}

bool graph::DeleteFunc(int k)//удалить функцию под номером k
{
	if (k>=0 && k<nfuncs)
	{
		funcs[k].ClearData();
		for (int i=k; i<nfuncs-1; i++)
		{
			funcs[i]=funcs[i+1];
		}
		nfuncs--;
		graph_func* temp = funcs;
		funcs = new graph_func[nfuncs];
		for (int i = 0; i < nfuncs; i++)
			funcs[i] = temp[i];
		delete temp;
		return true;
	}
	else
		return false;
}

bool graph::ReInitFunc(int k, char *instr, int len, const RGB_MR &colori, System::Windows::Forms::ProgressBar^ ProgBar)//реинициализировать элемент под номером k
{
	if (k>=0 && k<nfuncs)
	{
		num_func_calculateing=k;//для ошибок
		funcs[k].ClearData();
		funcs[k].Translate(instr, len);
		funcs[k].testFuncOnDymanic();
		funcs[k].CalculateMatrix(ngrid, xsha, ysha, tsha, Xmin, Xmax, Ymin, Ymax, t1, t2, fps, ProgBar);
		funcs[k].color = colori;
		num_func_calculateing=0;//для ошибок
		return true;
	}
	else
		return false;
}

void graph::TestOnDynamics()//проверка на существование динамической функции
{
	istDynamic=false;
	for (int i=0; i<nfuncs; i++)
		if (funcs[i].isFuncDynamic)
		{
			istDynamic=true;
			break;
		}
}

void graph::RedrawAll()
{
	if (Failed==false)
	{
		SetDrawData(fps);
		for (int i = 0; i < nfuncs; i++)
			funcs[i].RedrawFunc(ngrid, modecolor);
	}
}

void graph::SetError(int num)//добавить ошибку в массив ошибок GRAPHICS::ErrorsGlobal. n_func-номер ошибочной функции(нумерация с нуля(в самой функции прибавляется 1)). num-номер ошибки
{
	//MsgBoxShow(strToStr(error_otpfr_func)+uchToStr(dtuch(num_func_calculateing+1))+L": "+strToStr(errors[num]));
	//сделаю вывод ошибок в форму рачсет
	if (k_ErrorsGlobal>=nvsego_ErrorsGlobal)
		return;
	else
	{
		std::string stri=error_otpfr_func;
		stri.append(uchTostr(dtuch(num_func_calculateing+1)));
		stri.append(": ");
		stri.append(errors[num]);
		ErrorsGlobal[k_ErrorsGlobal]=stri;
		k_ErrorsGlobal++;
	}
	
}

void graph::ShowErrors(System::Windows::Forms::TextBox^ txtb)//вывести ошибки в TextBox формы Foem_Process
{//изначально в текстбоксе написано нет ошибок
	if (k_ErrorsGlobal>0)
	{
		txtb->Clear();
		array<System::String^>^ striarr = gcnew array<System::String^>(k_ErrorsGlobal);
		for (int i=0; i<k_ErrorsGlobal; i++)
		{
			striarr[i]=strToStr(ErrorsGlobal[i]);
		}
		txtb->Lines = striarr;
	}
}

void graph::SaveToFile(const char * name)
{
	FILE * ptrFile;
	fopen_s(&ptrFile, name, "w");
	if (ptrFile == NULL)//проверка на корректность файла
		return;
	fprintf(ptrFile, "%i\n", ngrid);//ngrid
	fprintf(ptrFile, "%i;%i\n", t1, t2);//t1;t2
	fprintf(ptrFile, "%i\n", isinitOpenGl);//isinitOpenGl
	fprintf(ptrFile, "%hi;%i\n", modecolor, modeoses);//modecolor;modeoses
	fprintf(ptrFile, "%i;%i;%i;%i;%i\n", moderot, modegridgr, modeistoses, modepokaz, istDynamic);//moderot;modegridgr;modeistoses;modepokaz;istDynamic
	fprintf(ptrFile, "%u;%u\n", fps, ffs);//fps;ffs
	for (int i = 0; i < 4; i++)//color_type1
		for (int j = 0; j < 3; j++)
			fprintf(ptrFile, "%lf;", color_type1[i].getColor(j));
	fprintf(ptrFile, "\n");
	for (int i = 0; i<7; i++)//color_type2
		for (int j = 0; j<3; j++)
			fprintf(ptrFile, "%lf;", color_type2[i].getColor(j));
	fprintf(ptrFile, "\n");
	fprintf(ptrFile, "%lf;%lf;%lf;%lf;%lf;%lf\n", Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);//Xmin;Xmax;Ymin;Ymax;Zmin;Zmax;
	fprintf(ptrFile, "%i;%i;%i\n", isautozmin, isautozmax, Failed);//isautozmin;isautozmax;Failed
	fprintf(ptrFile, "%i\n", mode_Now);//mode_Now
	fprintf(ptrFile, "%i\n", nfuncs);//nfuncs

	//funcs
	for (int i = 0; i < nfuncs; i++)
	{
		//failed;isFuncDynamic;isfunc;isFuncVisible
		fprintf(ptrFile, "%i;%i;%i;%i\n", funcs[i].failed, funcs[i].isFuncDynamic, funcs[i].isfunc, funcs[i].isFuncVisible);//isautozmin;isautozmax;Failed
		fprintf(ptrFile, "%i\n", funcs[i].outsch);//outsch
		fprintf(ptrFile, "%s\n", funcs[i].str);//str
		fprintf(ptrFile, "%s\n", funcs[i].strpr);//strpr
		fprintf(ptrFile, "%s\n", funcs[i].outstr);//outstr
		fprintf(ptrFile, "%lf;%lf\n", funcs[i].zmin, funcs[i].zmax);//zmin;zmax
		fprintf(ptrFile, "%hi\n", funcs[i].type_of_color);//type_of_color
		fprintf(ptrFile, "%lf;%lf;%lf\n", funcs[i].color.getColor(0), funcs[i].color.getColor(1), funcs[i].color.getColor(2));//color
		for (int j = 0; j<4; j++)//color_grad
			for (int l = 0; l<3; l++)
				fprintf(ptrFile, "%lf;", funcs[i].color_grad[j].getColor(l));
		fprintf(ptrFile, "\n");
		for (int j = 0; j<7; j++)//color_grad_land
			for (int l = 0; l<3; l++)
				fprintf(ptrFile, "%lf;", funcs[i].color_grad_land[j].getColor(l));
		fprintf(ptrFile, "\n");

		funcs[i].SaveData(ptrFile);
	}
	fclose(ptrFile);
	System::String^ namei=L"";
	for (int i = 0; name[i] != 0 && name[i] != '.' && i < 100; i++)
	{
		namei += wchar_t(name[i]);
	}
	namei += L".bmp";

	SaveOpenGlScreen(namei);
}

void graph::LoadFromFile(const char * name)//загрузить функции
{//абсолютный путь
	double color1 = 0.0, color2 = 0.0, color3 = 0.0;
	FILE * ptrFile;
	fopen_s(&ptrFile, name, "r");
	if (ptrFile == NULL)//проверка на корректность файла
		return;
	fscanf_s(ptrFile, "%i\n", &ngrid);//ngrid
	fscanf_s(ptrFile, "%i;%i\n", &t1, &t2);//t1;t2
	fscanf_s(ptrFile, "%i\n", &isinitOpenGl);//isinitOpenGl
	fscanf_s(ptrFile, "%hi;%i\n", &modecolor, &modeoses);//modecolor;modeoses
	fscanf_s(ptrFile, "%i;%i;%i;%i;%i\n", &moderot, &modegridgr, &modeistoses, &modepokaz, &istDynamic);//moderot;modegridgr;modeistoses;modepokaz;istDynamic
	fscanf_s(ptrFile, "%u;%u\n", &fps, &ffs);//fps;ffs
	for (int i = 0; i<4; i++)//color_type1
		for (int j = 0; j<3; j++)
		{
			fscanf_s(ptrFile, "%lf;", &color1);
			color_type1[i].setColor(j, color1);
		}
	fscanf_s(ptrFile, "\n");
	for (int i = 0; i<7; i++)//color_type2
		for (int j = 0; j<3; j++)
		{
			fscanf_s(ptrFile, "%lf;", &color1);
			color_type2[i].setColor(j, color1);
		}
	fscanf_s(ptrFile, "\n");
	fscanf_s(ptrFile, "%lf;%lf;%lf;%lf;%lf;%lf\n", &Xmin, &Xmax, &Ymin, &Ymax, &Zmin, &Zmax);//Xmin;Xmax;Ymin;Ymax;Zmin;Zmax;
	fscanf_s(ptrFile, "%i;%i;%i\n", &isautozmin, &isautozmax, &Failed);//isautozmin;isautozmax;Failed
	fscanf_s(ptrFile, "%i\n", &mode_Now);//mode_Now
	fscanf_s(ptrFile, "%i\n", &nfuncs);//nfuncs

	//funcs
	if (funcs != NULL)
		delete [] funcs;
	funcs = new graph_func[nfuncs];
	for (int i = 0; i < nfuncs; i++)
	{
		//failed;isFuncDynamic;isfunc;isFuncVisible
		fscanf_s(ptrFile, "%i;%i;%i;%i\n", &funcs[i].failed, &funcs[i].isFuncDynamic, &funcs[i].isfunc, &funcs[i].isFuncVisible);//isautozmin;isautozmax;Failed
		fscanf_s(ptrFile, "%i\n", &funcs[i].outsch);//outsch
		fscanf_s(ptrFile, "%s\n", funcs[i].str, sizeof(funcs[i].str));//str
		fscanf_s(ptrFile, "%s\n", funcs[i].strpr, sizeof(funcs[i].strpr));//strpr
		fscanf_s(ptrFile, "%[^\n]\n", funcs[i].outstr, sizeof(funcs[i].outstr));//outstr
		fscanf_s(ptrFile, "%lf;%lf\n", &funcs[i].zmin, &funcs[i].zmax);//zmin;zmax
		fscanf_s(ptrFile, "%hi\n", &funcs[i].type_of_color);//type_of_color
		fscanf_s(ptrFile, "%lf;%lf;%lf\n", &color1, &color2, &color3);//color
		funcs[i].color.setColor(0, color1);
		funcs[i].color.setColor(1, color2);
		funcs[i].color.setColor(2, color3);
		for (int j = 0; j<4; j++)//color_grad
			for (int l = 0; l<3; l++)
			{
				fscanf_s(ptrFile, "%lf;", &color1);
				funcs[i].color_grad[j].setColor(l, color1);
			}
		fscanf_s(ptrFile, "\n");
		for (int j = 0; j<7; j++)//color_grad_land
			for (int l = 0; l<3; l++)
			{
				fscanf_s(ptrFile, "%lf;", &color1);
				funcs[i].color_grad_land[j].setColor(l, color1);
			}
		fscanf_s(ptrFile, "\n");

		funcs[i].LoadData(ptrFile, ngrid);

	}
	fclose(ptrFile);
	isLoaded = true;
}

void graph::SaveToFileInfo(System::String^ FileInfo, char* name)
{
	const char* fileInfo_cCh = StrToCh(FileInfo);
	FILE * ptrFile;
	bool istsThisFunc = false;//true- если дубль
	if (System::IO::File::Exists(FileInfo))
	{
		fopen_s(&ptrFile, fileInfo_cCh, "r");
		if (ptrFile == NULL)//проверка на корректность файла
			return;

		fseek(ptrFile, 0, SEEK_END);//проверка файла на пустоту
		if (ftell(ptrFile) != 0)
		{
			//проверка на дубли
			char* namei = new char[sostr];
			int nfi = 0;
			fseek(ptrFile, 0, SEEK_SET);
			while (istsThisFunc == false && !feof(ptrFile))
			{
				fscanf_s(ptrFile, "%[^\n]\n", namei, sizeof(namei));
				fscanf_s(ptrFile, "%i\n", &nfi);
				for (int i = 0; i < nfi; i++)
					fscanf_s(ptrFile, "%*s\n");//funcs
				int i = 0;
				istsThisFunc = true;
				while (name[i] == namei[i] && name[i] > 0 && namei[i] > 0)
				{
					i++;
				}
				if (name[i] != namei[i])
					istsThisFunc = false;
			}
		}
		fclose(ptrFile);
	}

	fopen_s(&ptrFile, fileInfo_cCh, "a");
	if (ptrFile == NULL)//проверка на корректность файла
		return;
	if (istsThisFunc == false)//если не дубль
	{
		fprintf(ptrFile, "%s\n", name);//name
		fprintf(ptrFile, "%i\n", nfuncs);//nfuncs
		for (int i = 0; i < nfuncs; i++)
			fprintf(ptrFile, "%s\n", funcs[i].str);//funcs
	}
	fclose(ptrFile);
}