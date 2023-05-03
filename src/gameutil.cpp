#include "gameutil.h"

using namespace std;


//-----------------
//  Def: get time information by double
//  Para:   void
//  Return:     Return time in double format
//------------------
double getime(void) {
    return (chrono::duration<double> (chrono::high_resolution_clock::now().time_since_epoch())).count();
}

//-----------------
//  Def: overwrites all characters inside the game area with blank space
//  Para:  address of pointer to the game window 
//  Return:     void
//------------------
void clean_box(WIN *p_win) 
{
    int i, j;
    int x, y, w, h;

    x = p_win->startx;
    y = p_win->starty;
    w = p_win->width;
    h = p_win->height;

    for (j = y; j<=y+h; ++j) {
        for (i = x; i <= x+w; ++i) {
            mvaddch(j, i, ' ');
        }
    }
    refresh();
}

//-----------------
//  Def: initialize the seed value of random number using the time information
//      Make sure the event is random everytime the game is run
//  Para:  void
//  Return: void
//------------------
void InitRand(void) {
    srand( (unsigned int) getime() );
}
