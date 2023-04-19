#include "mapgame.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
#define DEBUGON


//--------------------------------
//  Global variables
//-------------------------------


//--------------------------------
//  Def :   Map Gmae
//  Para : void 
//  return :    fightgame(1)/quit(2) 
//-----------------------------------
int mapgame(void) {
#ifdef DEBUGON
    while (true) {

        printf("Entered map mode\n");

   /*check input*/
        int input;
        printf("input a number: ");
        scanf("%d", &input);

        if (input == 2) {
        /*quit game loop*/
            return 2;
        }

        printf("end of map loop\n");
        printf("enter 1 to enter fight loop: ");
        scanf("%d", &input);
        if (input == 1) break;
    }

#endif

   /* 1: go to fight game */
   return 1;
}
