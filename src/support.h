#ifndef SUPPORT_H
#define SUPPORT_H
//----------------------


//--------------------
// Include libraries
//------------------
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <sys/time.h>


//----------------
// prototype declaration
//-----------------
void Fatal(char *msg);
void InitColor(int bg);
void UseColor(int c);
void DrawBlocks(int ymax, int xmax, int y, int x, char s[]);
void InitRand();
int Rand(int n);
void InitWait();
void Wait(int msec);



#endif
