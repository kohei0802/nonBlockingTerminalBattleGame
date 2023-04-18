#include "fight.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
#define DEBUGON

/* loops need to pass to fire again */
#define FINTERVAL 1 
#define MAX_EN 10
#define MAX_BU 10


//--------------------------------
//  Global variables
//-------------------------------
int ymax = 0;
int xmax = 0;


//------------------------------
//  Static functions declaration
//---------------------------------

/* first initialization of Mobj */
static void setMobj(Enemy* p_en);
static void setMobj(Bullet* p_en);
static void setPlayer(Player* p_pl);

/* draw monitors */
static void drawMon(Player *p_pl);


//--------------------------------
//  Def :   Fight Gmae
//  Para : void 
//  return :    mapgame(0)/quit(2) 
//-----------------------------------
int fight(void) {
    /* screen sizes */
    int h = 25, w = 50;
    ymax = h-1; xmax = w-1;

    /* firing related */
    int angle = 45;
    int ready = 0;

    /* Moving objects */
    Player player; setPlayer(&player);
    Enemy enemies [MAX_EN]; setMobj(enemies);
    Bullet bullets [MAX_BU]; setMobj(bullets);
#ifdef DEBUGON
    Mobj* pmp = &(player.obj);
    Mobj* pme = &((enemies[1]).obj); 
    Mobj* pmb = &((bullets[1]).obj); 
    printf("Player set up: \n\
            px: %lf, py: %lf, vx: %lf, vy: %lf, sx: %lf, sy: %lf, life: %d\n", \
            pmp->px, pmp->py, pmp->vx, pmp->vy, pmp->sx, pmp->sy, pmp->life);
    printf("Second Enemy set up: \n\
            px: %lf, py: %lf, vx: %lf, vy: %lf, sx: %lf, sy: %lf, life: %d\n", \
            pme->px, pme->py, pme->vx, pme->vy, pme->sx, pme->sy, pme->life);
    printf("Second Bullet set up: \n\
            px: %lf, py: %lf, vx: %lf, vy: %lf, sx: %lf, sy: %lf, life: %d\n", \
            pmb->px, pmb->py, pmb->vx, pmb->vy, pmb->sx, pmb->sy, pmb->life);
#endif

    /* game loop */
    while (true) {

#ifdef DEBUGON
        int input = 0;
        int fire = 0;
        printf("Entered fight mode\n");
#endif
        /* Actual Code */ 

        /* draw moving objects */
        drawMobj(enemies, MAX_EN, bullets, MAX_BU, &player);

        /* draw monitors */
        drawMon(&player);
#if (0)
        refresh();
#endif
        /* user input */
        printf("Enter Key: 1->angleup 2->angledown 3->fire: ");
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
#if (0)
        if (ready>=0) {
            if (fire) {
                firing();
                ready = FINTERVAL;
            }
        }
        else {
            ready--;
        }
#else

        /* checkhit */
        chkHit(&player, enemies, MAX_EN);
        chkHit(enemies, MAX_EN, bullets, MAX_BU);
        /* move */
        moveMobj(enemies, MAX_EN, bullets, MAX_BU, &player);
#endif

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


//--------------------------------
//  Def :   initialize the values in Player struct, list of Enemy struct, and list of BULLET struct
//  Para : &player address, enemy array, bullet array 
//  return :    void 
//-----------------------------------
static void setMobj(Enemy* p_en) {
    /* enemies */
    for (int i=0; i<MAX_EN; i++ ) {
        (p_en->obj).px = xmax/2; (p_en->obj).py = 5.0;
        (p_en->obj).vx = 0.0; (p_en->obj).vy = 0.0;
        (p_en->obj).sx = 5.0; (p_en->obj).sy = 5.0;
        (p_en->obj).life = 0;
        p_en++;
    }
}


static void setMobj(Bullet* p_bu) {
    /*bullets */
    for (int i=0; i<MAX_BU; i++) {
        /* bottom */
        (p_bu->obj).px = xmax/2; (p_bu->obj).py = ymax - 1.0;
        (p_bu->obj).vx = 0.0; (p_bu->obj).vy = 0.0;
        (p_bu->obj).sx = 1.0; (p_bu->obj).sy = 1.0;
        (p_bu->obj).life = 0;
        p_bu++;
    }
}


static void setPlayer(Player* p_pl) {
    /* player */
    /* bottom left */
    (p_pl->obj).px = 3.0; (p_pl->obj).py = ymax - 3.0;
    (p_pl->obj).vx = 0.0; (p_pl->obj).vy = 0.0;
    (p_pl->obj).sx =  3.0; (p_pl->obj).sy = 3.0;
    (p_pl->obj).life = 1;
}


/* draw monitors */
static void drawMon(Player *p_pl) {
    return ;
}



