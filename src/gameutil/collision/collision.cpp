#include "collision.h"

//------------------------------
// internal Macros definition
//------------------------------
#define DEBUGON

//------------------------------
//  Static functions
//------------------------------
static int chkWall(ColFactor cfac, int ymax, int xmax);
static int chkHit(ColFactor cfac1, ColFactor cfac2);

//------------------------------
//  Global variables
//------------------------------

//------------------------------
//  Def:    Check if the Mobj will move over the wall 
//  Para :  Overloaded
//  Return :    return 1 for going over the wall
//------------------------------
int chkWall(Player* player, int ymax, int xmax) {
    Mobj obj = player->obj;
    ColFactor cfac = {obj.px, obj.py, obj.vx, obj.vy, obj.sx, obj.sy};
    /* decrement life */
    if (chkWall(cfac, ymax, xmax)) {
        (player->obj).life--;
    }
    return 0;
}

/* process a list of enemies */
int chkWall(Enemy* enemies, int len_en, int ymax, int xmax) {
    Mobj obj;
    for (int i=0; i<len_en; i++) {
        obj= (enemies+i)->obj;
        ColFactor cfac = {obj.px, obj.py, obj.vx, obj.vy, obj.sx, obj.sy}; 
        if (chkWall(cfac, ymax, xmax)) {
            ((enemies+i) -> obj).life = 0;
        }
    }

    return 0;
}

/* process a list of bullets */
int chkWall(Bullet* bullets, int len_bu, int ymax, int xmax) {
    Mobj obj;
    for (int i=0; i<len_bu; i++) {
        obj = (bullets+i)->obj;
        ColFactor cfac = {obj.px, obj.py, obj.vx, obj.vy, obj.sx, obj.sy}; 
        if (chkWall(cfac, ymax, xmax)) {
            ((bullets+i)->obj).life = 0;
        }
    }
    return 0;
}

/* determine collision between wall and Mobj */
static int chkWall(ColFactor cfac, int ymax, int xmax) {
    double x = cfac.px + cfac.vx;
    double y = cfac.py + cfac.vy;
    if ( x < cfac.sx || x + cfac.sx > (double) xmax ) 
        return 1;
    if ( y < cfac.sy || y + cfac.sy > (double) ymax )
        return 1; 

    return 0;
}


//------------------------------
//  Def: check hit, if hit, change Object.life to 0 
//  Para :  Overload
//  Return :    void
//------------------------------
void chkHit(Player* player, Enemy enemies[], int len_en) {
    Mobj obj1 = player->obj, obj2;
    ColFactor cfac1 = {obj1.px, obj1.py, obj1.vx, obj1.vy, obj1.sx, obj1.sy}, cfac2;
    for (int i=0; i<len_en; i++) {
        obj2 = enemies[i].obj;
        cfac2 = {obj2.px, obj2.py, obj2.vx, obj2.vy, obj2.sx, obj2.sy};
        if (chkHit(cfac1, cfac2)) {
            enemies[i].obj.life = 0;
        }
    }
    return ;
}


void chkHit(Enemy enemies[], int len_en, Bullet bullets[], int len_bu) {
    Mobj obj1, obj2;
    ColFactor cfac1, cfac2;

    for (int b=0; b<len_bu; b++) {
        obj1 = bullets[b].obj;
        for (int e=0; e<len_en; e++) {
            obj2 = enemies[e].obj;
            cfac1 = {obj1.px, obj1.py, obj1.vx, obj1.vy, obj1.sx, obj1.sy};
            cfac2 = {obj2.px, obj2.py, obj2.vx, obj2.vy, obj2.sx, obj2.sy};
            if (chkHit(cfac1, cfac2)) {
                bullets[b].obj.life = 0;
                enemies[e].obj.life = 0;
            }
        }
    }
    return ;
}

/* return 1 for hit, return 0 otherwise */
static int chkHit(ColFactor cfac1, ColFactor cfac2) {
    double x = fabs((cfac1.px + cfac1.vx) - (cfac2.px + cfac2.vx));
    double y = ((cfac1.py + cfac1.vy) - (cfac2.py + cfac2.vy));
    if (x - 1 < cfac1.sx + cfac2.sx)    
        return 1;
    if (y - 1 < cfac1.sy + cfac2.sy)
        return 1;

    return 0;
}
