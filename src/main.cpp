#include <stdio.h>
#include <ncurses.h>
#include "dreamwalk.h"
#include "support.h"
using namespace std;

//----------------------------------
//  Define Macros
//----------------------------------
//#define DEBUGON

//---------------------------------
//  Define Global Variables
//---------------------------------


//---------------------------------
//  Def :   Start of the Game
//  Para :  void
//  return : NORMAL(0)/ERROR(1)
//---------------------------------
int main() {
#if (1)
    /* Initialize ncurses related */
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(-1);

    /* Initialize variables */
    int key{0};

    char msg[] = "Enter game? (y/n)" ;
    DrawBlocks(LINES-1, COLS-1, 2, 2, msg);

    key = getch();
    refresh();
    /* Title */
    if (key == 'y') dreamwalk();
    else {
        endwin();
        return 0;
    }
#else 
    dreamwalk();
#endif

#ifdef DEBUGON
    //dreamwalk();
//    printf("Hello\n");
#endif

	return 0;
}
