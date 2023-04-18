#ifndef COLLISION_H
#define COLLISION_H
//------------------------------
#include <stdio.h>
#include "../movingobject/mobj.h"
#include <cmath>

//----------------------------
//  Macros definition
//----------------------------

//----------------------------
//  Type definition
//----------------------------

/* data needed to forecast collision */
struct ColFactor {
    double px, py, vx, vy, sx, sy;
};

//----------------------------
//  Prototype declaration
//----------------------------

/* check if it is GOING to collide at the wall */
int chkWall(Player* player, int ymax, int xmax);
int chkWall(Enemy* enemy, int ymax, int xmax);
int chkWall(Bullet* bullet, int ymax, int xmax);

/* check if it's hitting */
void chkHit(Player* player, Enemy enemies[], int len_en);
void chkHit(Enemy enemies[], int len_en, Bullet bullets[], int len_bu);

//----------------------
#endif
