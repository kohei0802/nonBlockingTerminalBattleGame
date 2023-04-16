#include "fight.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
#define DEBUGON

/* loops need to pass to fire again */
#define FINTERVAL 1 


//--------------------------------
//  Global variables
//-------------------------------


//--------------------------------
//  Def :   Fight Gmae
//  Para : void 
//  return :    mapgame(0)/quit(2) 
//-----------------------------------
int fight(void) {
    int h = 25, w = 50;
    int angle = 45;
    int ready = 0;

    while (true) {

#ifdef DEBUGON
        int input = 0;
        int fire = 0;
        printf("Entered fight mode\n");
#endif
        /* Actual Code */ 

        /* draw moving objects */
        drawMobj();
        /* draw monitors */
        drawMon();
        refresh();

        printf("Enter Key: 1->angleup 2->angledown 3->fire");
        scanf("%d", &input);
        switch (input) {
            case (1):
                angle += 5;
                break;
            case (2):
                angle -= 5;
                break;
            case (3):
                fire = 1;
                break;
            default:
                break;
        }

        //------------------------
        //  Function Description: 
        //  If firing,  
        //  First, find unused bullet in bullets list
        //  Seconds, initialize it with proper
        //      angles, velocity, and bullet type
        //-------------------------
        //  IMPORTANT
        /* if enough time/iteration has passed since last fired*/
        if (ready>=0) {
            if (fire) {
                firing();
                ready = FINTERVAL;
            }
        }
        else {
            ready--;
        }

        /* checkhit */
        chkHit();

        /* move */
        moveMobj;


#ifdef DEBUGON
   /*check input*/
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
