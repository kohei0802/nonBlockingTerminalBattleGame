#include "gameutil.h"

using namespace std;

double getime(void) {
    return (chrono::duration<double> (chrono::high_resolution_clock::now().time_since_epoch())).count();
}

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

void InitRand(void) {
    srand( (unsigned int) getime() );
}
