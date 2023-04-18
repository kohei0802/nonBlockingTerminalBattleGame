#include "mobj.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
#define DEBUGON

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
static void drawEnemies(Enemy *p_en);
static void drawBullets(Bullet *p_bu);

/*move individual of mobj */ 
static void moveEn(Enemy* p_en);
static void moveBu(Bullet* p_bu);
static void movePl(Player* p_pl);

/*move list of mobj*/
static void moveEnemies(Enemy *p_en);
static void moveBullets(Bullet *p_bu);


//--------------------------------
//  Def :   draw objects based on position
//  Para :  Mobj lists, len of lists, Mobj player
//  return :    void
//-----------------------------------
void drawMobj(Enemy* p_en, int len_en, Bullet* p_bu, int len_bu, Player* p_pl) {
#ifdef DEBUGON
    printf("Enter drawing everything\n");
#endif
    drawBullets(p_bu);
    drawEnemies(p_en);
    drawPl(p_pl);
#ifdef DEBUGON
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
#ifdef DEBUGON
    printf("Enter moving everything\n");
#endif
    moveBullets(p_bu);
    moveEnemies(p_en);
    movePl(p_pl);
    return ;
#ifdef DEBUGON
    printf("Finished moving everything\n");
#endif
}

/*draw individual mobj */
static void drawEn(Enemy *p_en) {
#ifdef DEBUGON
    printf("Enter drawing individual en\n");
#endif

#ifdef DEBUGON
    printf("Finished drawing individual en\n");
#endif
}
static void drawBu(Bullet *p_bu) {
#ifdef DEBUGON
    printf("Start drawing individual bu\n");
#endif

#ifdef DEBUGON
    printf("Finished drawing individual bu\n");
#endif
}
static void drawPl(Player *p_pl) {
#ifdef DEBUGON
    printf(" drawing individual pl\n");
#endif

#ifdef DEBUGON
    printf("Finished drawing individual pl\n");
#endif
}

/*draw list of mobj */
static void drawEnemies(Enemy *p_en) {
#ifdef DEBUGON
    printf(" sta draw all en\n");
#endif

    drawEn(p_en);

#ifdef DEBUGON
    printf(" fin draw all en\n");
#endif

}
static void drawBullets(Bullet *p_bu) {
#ifdef DEBUGON
    printf(" sta draw all bu\n");
#endif
    drawBu(p_bu);

#ifdef DEBUGON
    printf(" fin draw all bu\n");
#endif

}

/*move individual of mobj */ 
static void moveEn(Enemy* p_en) {
#ifdef DEBUGON
    printf(" sta move a en\n");
#endif

#ifdef DEBUGON
    printf(" fin move a en\n");
#endif

}
static void moveBu(Bullet* p_bu) {
#ifdef DEBUGON
    printf(" start move a bu\n");
#endif

#ifdef DEBUGON
    printf(" fin move a bu\n");
#endif

}
static void movePl(Player* p_pl) {
#ifdef DEBUGON
    printf(" start move a pl\n");
#endif

#ifdef DEBUGON
    printf(" fin move a pl\n");
#endif

}

/*move list of mobj*/
static void moveEnemies(Enemy *p_en) {
#ifdef DEBUGON
    printf(" start move all en\n");
#endif

    moveEn(p_en);

#ifdef DEBUGON
    printf(" fin move all en\n");
#endif

}
static void moveBullets(Bullet *p_bu) {
#ifdef DEBUGON
    printf(" start move all bullets\n");
#endif
    moveBu(p_bu);

#ifdef DEBUGON
    printf(" fin move all bullets \n");
#endif

}
