#pragma once
#include "stdafx.h"
#include "global.h"

#include "ListOfFuncs.h"
#include "RGB.h"
#include "graph_data.h"
#include "graph_func.h"

#pragma pack(push, 1)
class graph
{
public:
	int ngrid;//количество полигонов / одно ребро (количество точек на 1 больше)
	double xsha,ysha,tsha;//шаг сетки по x и y. шаг времени
	bool IsTimeStartedNow;//true - если процесс запущен сейчас
	double ti;//текущее время
	int t1, t2;//начальное и конечное время в секундах

	bool isinitOpenGl;//инициализирован OpenGL
	short int modecolor;/*тип раскраски функции.
				  1-разными цветами каждую функцию(монотонно)
				  2-разными цветами каждую функцию(градиентно)
				  3-раскраска 4 цветами от dl,dr,ul,ur.
				  4-ландшафт.*/
	int modeoses;//тип расположения осей
	int ndeloses;//количество делений на оси (для начала промежуточных, т.е. не при макс и мин значениях)
	bool moderot;//Вращается ли график
	bool modegridgr;//есть ли сетка на графике
	bool modeistoses;//есть ли оси
	bool modepokaz;//есть ли показания максимумов и минимумов
	bool istDynamic;//есть ли хоть одна динамическая функция
	unsigned int fps,ffs;//fps, размер шрифта формы
	RGB_MR color_type1[4];//по первой схеме. downleft, downright, upleft, upright colors (от 0.0 до 1.0)
	RGB_MR color_type2[7];//по второй схеме. радуга от красного до фиолетового сверху вниз.
	bool isLoaded;//произошла ли загрузка из файла(если да, то обносить элементы Form1 и установить равным false)

	double Xmin,Xmax,Ymin,Ymax,Zmin,Zmax;//минимальные и максимальные значения x,y,z
	bool isautozmin, isautozmax;//есть ли auto в zmin и zmax

	int nfuncs;//количество функций.
	graph_func *funcs;//функции и их данные
	
	bool Failed;//true- если неправильно указаны параметры на форме

	int scrw, scrh;//ширина и высота экрана

	std::string *ErrorsGlobal;//массив ошибок при расчете
	int nvsego_ErrorsGlobal, k_ErrorsGlobal;//всего зарезервировано ошибок, сколько ошибок в функциях(или др.)
	int mode_Now;//определяет, какой сейчас язык

	ListOfFuncs listOfFuncs;//для загрузки (!FileInfo.info)содержит список сохранений и их функций в локальном виде
public:
	graph();
	void AddFunc(char *instr, int len, const RGB_MR &colori, System::Windows::Forms::ProgressBar^ ProgBar);
	bool DeleteFunc(int k);//удалить функцию под номером k
	bool ReInitFunc(int k, char *instr, int len, const RGB_MR &colori, System::Windows::Forms::ProgressBar^ ProgBar);//реинициализировать элемент под номером k
	
	void InitErrorsGlobal(int n);
	void SetError(int num);//добавить ошибку в массив ошибок GRAPHICS::ErrorsGlobal. n_func-номер ошибочной функции(нумерация с нуля(в самой функции прибавляется 1)). num-номер ошибки
	void ShowErrors(System::Windows::Forms::TextBox^ txtb);//вывести ошибки в TextBox формы Form_Process
	
	void TestOnDynamics();//проверка на существование динамической функции
	void FuncsReOut();//подготовка функций к выводу(включает инициализацию цветов)
	void ReInitColors();//инициализация цвета функций и типа раскраски
	void SetDrawData(unsigned int fpsi);
	void RedrawAll();

	void SaveToFile(const char * name);//сохранить функции
	void LoadFromFile(const char * name);//загрузить функции
	void SaveToFileInfo(System::String^ FileInfo, char* name);
private:
};
#pragma pack(pop)

extern graph GRAPHICS;