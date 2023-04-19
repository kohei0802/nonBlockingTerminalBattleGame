#ifndef FIGHT_H
#define FIGHT_H
//--------------------------------------------
#include <unistd.h>
#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <ncurses.h>
#include "./gameutil/movingobject/mobj.h"
#include "./gameutil/collision/collision.h"
#include "support.h"

//-------------------------------------------
//  Macros definition
//-----------------------------------------

//--------------------------------------------
//  Type definition
//--------------------------------------------


//-----------------------------------------------
//  Prototype declaration
//---------------------------------------------

/* main fight game loop */
int fight(void);

/* edit all information */
void editMobj(int mode, void* ptr, double px, double py, double vx, double vy, double sx, double sy, int life, void (*draw) (double px, double py));

//----------------------------------------------
#endif
