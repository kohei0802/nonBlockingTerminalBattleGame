#ifndef MOBJ_H
#define MOBJ_H
//---------------------------------
#include <stdio.h>
#include <ncurses.h>

//--------------------------------
//  Macros Definition
//--------------------------------
#define DEBUGON


//-------------------------------
//  Type Definition
//--------------------------------
struct Mobj {
    double px, py;
    double vx, vy;
    double sx, sy;
    int life;
};

struct Enemy {
    Mobj obj;
    void *draw (double px, double py); 
};

struct Bullet {
    Mobj obj;
    void *draw (double px, double py);
};

struct Player {
    Mobj obj;
    void *draw (double px, double py);
};

//--------------------------------
//  Prototype Declaration
//--------------------------------
void drawMobj(Enemy* enemy, int enlen, Bullet* bullet, int bulen, Player *player);

void moveMobj(Enemy* enemy, int enlen, Bullet* bullet, int bulen, Player *player);

//--------------------------------
#endif
