#include "mobj.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
//#define DEBUGM

#define MAX_EN 15
#define MAX_BU 15

//--------------------------------
//  Global variables
//-------------------------------


//-----------------------------------------
//  Static functions
//------------------------------------------
/*draw individual mobj */
static void drawEn(Enemy *p_en);
static void drawBu(Bullet *p_bu);
static void drawPl(Player *p_pl);

/*draw list of mobj */
static void drawEnemies(Enemy *p_en, int len_en);
static void drawBullets(Bullet *p_bu, int len_bu);

/*move individual of mobj */ 
static void moveEn(Enemy* p_en);
static void moveBu(Bullet* p_bu);
static void movePl(Player* p_pl);

/*move list of mobj*/
static void moveEnemies(Enemy *p_en, int len_en);
static void moveBullets(Bullet *p_bu, int len_bu);


//--------------------------------
//  Def :   draw objects based on position
//  Para :  Mobj lists, len of lists, Mobj player
//  return :    void
//-----------------------------------
void drawMobj(Enemy* p_en, int len_en, Bullet* p_bu, int len_bu, Player* p_pl) {
#ifdef DEBUGM
    printf("Enter drawing everything\n");
#endif
    drawBullets(p_bu, len_en);
    drawEnemies(p_en, len_bu);
    drawPl(p_pl);
#ifdef DEBUGM
    printf("finished drawing everything\n");
#endif
    return ;
}


//--------------------------------
//  Def :   move objects based on position, velocity
//  Para :  Mobj lists, len of Mobj, Mobj player
//  return :    void
//-----------------------------------
void moveMobj(Enemy* p_en, int len_en, Bullet* p_bu, int len_bu, Player* p_pl) {
#ifdef DEBUGM
    printf("Enter moving everything\n");
#endif
    moveBullets(p_bu, len_bu);
    moveEnemies(p_en, len_en);
    movePl(p_pl);
    return ;
#ifdef DEBUGM
    printf("Finished moving everything\n");
#endif
}


//-----------------------------------------
//  Def : Static Functions for drawing Mobj
//-----------------------------------------
/*draw individual mobj */
static void drawEn(Enemy *p_en) {
#ifdef DEBUGM
    printf("Enter drawing individual en\n");
#endif
    (p_en->draw)((p_en->obj).px, (p_en->obj).py);

#ifdef DEBUGM
    printf("Finished drawing individual en\n");
#endif
}
static void drawBu(Bullet *p_bu) {
#ifdef DEBUGM
    printf("Start drawing individual bu\n");
#endif
    (p_bu->draw)((p_bu->obj).px, (p_bu->obj).py);

#ifdef DEBUGM
    printf("Finished drawing individual bu\n");
#endif
}
static void drawPl(Player *p_pl) {
#ifdef DEBUGM
    printf(" drawing individual pl\n");
#endif
    if ((p_pl->obj).life <= 0) {
        (p_pl->draw)((p_pl->obj).px, (p_pl->obj).py);
    }

#ifdef DEBUGM
    printf("Finished drawing individual pl\n");
#endif
}

/*draw list of mobj */
static void drawEnemies(Enemy *p_en, int len_en) {
#ifdef DEBUGM
    printf(" sta draw all en\n");
#endif

    for (int i=0; i<len_en; i++) {
        if ( ((p_en+i)->obj).life != 1 )
            continue;
        drawEn(p_en+i);
    }

#ifdef DEBUGM
    printf(" fin draw all en\n");
#endif

}
static void drawBullets(Bullet *p_bu, int len_bu) {
#ifdef DEBUGM
    printf(" sta draw all bu\n");
#endif
    for (int i=0; i<len_bu; i++) {
        if ( ((p_bu+i)->obj).life !=1 ) {
            continue;

        }
        drawBu(p_bu+i);
    }

#ifdef DEBUGM
    printf(" fin draw all bu\n");
#endif

}

//---------------------------------------------------



//----------------------------
// Def : Static Functions for Moving objects
// --------------------------------------
/*move individual of mobj */ 
static void moveEn(Enemy* p_en) {
#ifdef DEBUGM
    printf(" sta move a en\n");
#endif
    (p_en->obj).px = (p_en->obj).vx;
    (p_en->obj).py = (p_en->obj).vy;

#ifdef DEBUGM
    printf(" fin move a en\n");
#endif

}
static void moveBu(Bullet* p_bu) {
#ifdef DEBUGM
    printf(" start move a bu\n");
#endif

    (p_bu->obj).px = (p_bu->obj).vx;
    (p_bu->obj).py = (p_bu->obj).vy;

#ifdef DEBUGM
    printf(" fin move a bu\n");
#endif

}
static void movePl(Player* p_pl) {
#ifdef DEBUGM
    printf(" start move a pl\n");
#endif

    /* player freezes if life <= 0  */
        ( p_pl->obj ).px += ( p_pl->obj ).vx;
        ( p_pl->obj ).py += ( p_pl->obj ).vy;

#ifdef DEBUGM
    printf(" fin move a pl\n");
#endif

}

/*move list of mobj*/
static void moveEnemies(Enemy *p_en, int len_en) {
#ifdef DEBUGM
    printf(" start move all en\n");
    printf("%d\n", ((p_en)->obj).life);
#endif

    for (int i=0; i<len_en; i++) {
        if (  ( (p_en+i)->obj  ).life  <=   0 ) {
            continue; 

        }

        /* pass on address of the ith Enemy counted from index 0 */
        moveEn(p_en+i);
    }


#ifdef DEBUGM
    printf(" fin move all en\n");
#endif
}

static void moveBullets(Bullet *p_bu, int len_bu) {
#ifdef DEBUGM
    printf(" start move all bullets\n");
    printf("%d\n", ((p_bu)->obj).life);
#endif

    for (int i=0; i<len_bu; i++) {
        if (  (  (p_bu+i)->obj ).life   <=  0 ) {
            continue;

        }

        /*pass on address on the ith bullets counted form index 0 */
        moveBu(p_bu+i);
    }

#ifdef DEBUGM
    printf(" fin move all bullets \n");
#endif

}

//------------------------------------------------
