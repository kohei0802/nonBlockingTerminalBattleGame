#include "fight.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
#define DEBUGON


//--------------------------------
//  Global variables
//-------------------------------


//--------------------------------
//  Def :   Fight Gmae
//  Para : void 
//  return :    mapgame(0)/quit(2) 
//-----------------------------------
int fight(void) {
#ifdef DEBUGON
    while (true) {

        printf("Entered fight mode\n");

   /*check input*/
        int input;
        printf("input a number: ");
        scanf("%d", &input);

        if (input == 2) {
        /*quit game loop*/
            return 2;
        }

        printf("end of fight loop\n");

        printf("enter 0 and go to map?");
        scanf("%d", &input);
        if (input == 0) break;
    }

#endif

   /* 0: return to map game */
   return 0;
}
