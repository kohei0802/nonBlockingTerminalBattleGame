#include "dreamwalk.h"

//---------------------------------------
//  Internal Macros definition
//------------------------------------
#define DEBUGON


//--------------------------------------
//  Global Variable
//-------------------------------------


//-----------------------------------
//  Def :   Main Game Loop
//  Para :  void
//  return :    Normal(0)/ERROR(1)
//------------------------------------
extern int mapgame(void);

int dreamwalk(void) {
    /* game mode : mapgame(0)/fight(1)/quit(2) */
    int mode = 1;

    while (mode != 2) {
        if (mode == 0) {
            mode = mapgame();
        }
        if (mode == 1) {
            mode = fight();
#ifdef DEBUGON
            printf("Fight ended\n");
#endif
        }
    }
    printf("dreamwalk exit normally\n");
    
    return 0;
}
