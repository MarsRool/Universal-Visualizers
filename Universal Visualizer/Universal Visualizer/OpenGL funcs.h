#pragma once

void ChangeTitleOpenGL(const char *title);
void init_OpenGL(int argc, char* argv[]);
void SaveOpenGlScreen(System::String^ path);

double ColorMix(double color1i, double color2i, double mix);
double partofS(double a, double b, double c, double d);

extern int razm;//размер куба