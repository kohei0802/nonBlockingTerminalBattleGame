#include <stdio.h>
#include <ncurses.h>
#include "dreamwalk.h"
using namespace std;

//----------------------------------
//  Define Macros
//----------------------------------
#define DEBUGON

//---------------------------------
//  Define Global Variables
//---------------------------------


//---------------------------------
//  Def :   Start of the Game
//  Para :  void
//  return : NORMAL(0)/ERROR(1)
//---------------------------------
int main() {
#if (0) 
    /* Initialize ncurses related */
    init();
    timeout(-1);
    /* Initialize ncurses color pairs */
    initcolor();

    /* Initialize variables */
    int key{0};

    /* Title */
    while ((key = getch()) != 'q') {
        ;
    }
#endif

#ifdef DEBUGON
    dreamwalk();
    printf("Hello\n");
#endif

	return 0;
}
