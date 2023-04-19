#include "fight.h"

//--------------------------------
//  internal Macros definition
//--------------------------------
//#define DEFIGHT

/* loops need to pass to fire again */
#define FINTERVAL 1 
#define GAME_INT 20
#define MAX_EN 10
#define MAX_BU 10


//--------------------------------
//  Global variables
//-------------------------------
static int ymax = 0;
static int xmax = 0;
std::vector<std::vector<double>> sizes = {
    {2.0, 2.0},
    {3.0, 3.0}
};

std::vector<std::vector<double>> vel = {
    {0, 1.0},
    {0, 1.0}
};


//------------------------------
//  Static functions declaration
//---------------------------------

/* first initialization of Mobj */
static void setMobj(Enemy* p_en);
static void setMobj(Bullet* p_en);
static void setPlayer(Player* p_pl);

/* draw monitors */
static void drawMon(Player *p_pl);

/* find unused bullet space and insert a suitable bullet type according to input */
void firing(Bullet* bullets, int len_bu, int fire, int angle);


void drawPlayer(double px, double py);

/*draw bullet1 */
void drawBullet1(double px, double py);
void drawBullet2(double px, double py);

void drawEnemy1(double px, double py);
void drawEnemy2(double px, double py);


//--------------------------------
//  Def :   Fight Gmae
//  Para : void 
//  return :    mapgame(0)/quit(2) 
//-----------------------------------
int fight(void) {
    timeout(0);

    /* screen sizes */
    int h = LINES, w = COLS;
    ymax = h-1; xmax = w-1;

    /* firing related */
    int angle = 45;
    int ready = 0;
    int input;

    /* Moving objects */
    Player player; 
    editMobj(0,&player,3,ymax-3,0,0,3,3,1,drawPlayer);
    Enemy enemies [MAX_EN]; setMobj(enemies);
    Bullet bullets [MAX_BU]; setMobj(bullets);

#ifdef DEFIGHT
#endif

    /* game loop */
    while (true) {
        InitWait();
        erase();
        int fire = 0;
#ifdef DEFIGHT
        printf("Entered fight mode\n");
#endif
        /* Actual Code */ 

        /* draw moving objects */
        drawMobj(enemies, MAX_EN, bullets, MAX_BU, &player);

        /* draw monitors */
        //drawMon(&player);
        refresh();
        /* user input */
        //printf("Enter Key: 1->angleup 2->angledown 3->fire: ");
        //scanf("%d", &input);

        player.obj.vx = 0; player.obj.vy = 0;
        switch (input = getch()) {
            case (KEY_LEFT):
            case (KEY_UP):
                angle += 5;
                break;
            case (KEY_RIGHT):
            case (KEY_DOWN):
                angle -= 5;
                break;
            case ('z'):
                //endwin();
                //printf("Updated: %lf", player.obj.vx);
                //exit(0);
                fire = 1;
                break;
            case ('x'):
                fire = 2;
                break;
            case ('a'):
                player.obj.vx = -1;
                break;
            case ('d'):
                player.obj.vx = 1;
                break;
            case ('s'):
                player.obj.vy = 1;
                break;
            case ('w'):
                player.obj.vy = -1;
                break;
            case ('q'):
                endwin();
                exit(0);
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
            if (fire>0) {
                firing(bullets, MAX_BU, fire, angle);
                ready = FINTERVAL;
            }
        }
        else {
            ready--;
        }

        /* checkhit */
        chkHit(&player, enemies, MAX_EN);
        chkHit(enemies, MAX_EN, bullets, MAX_BU);
        
        /* checkwall*/
        chkWall(&player, ymax, xmax);
        chkWall(enemies, MAX_EN, ymax, xmax);
        chkWall(bullets, MAX_BU, ymax, xmax);

        /* move */
        moveMobj(enemies, MAX_EN, bullets, MAX_BU, &player);

        printf("%lf\n", (bullets[0]).obj.vx);

#if (0)
        /* random generation of enemies */
        for (int i=0; i<MAX_EN; i++) {
            if (enemies[i].obj.life == 1) 
                continue;
            int ranen = Rand(2);
            int ranx = Rand(xmax - sizes[ranen][0]);
            enemies[i].obj.px = ranx; enemies[i].obj.py = 0;
            enemies[i].obj.vx = vel[ranen][0]; enemies[i].obj.vy = vel[ranen][1];
            enemies[i].obj.sx = sizes[ranen][0]; 
            enemies[i].obj.sy = sizes[ranen][1]; 
            switch(ranen) {
                case 0:
                    enemies[i].draw = drawEnemy1;
                    break;
                case 1:
                    enemies[i].draw = drawEnemy2;
                    break;
            }
        }
#endif



    Wait(GAME_INT);

    }

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
    (p_pl->obj).life = 3;
}


/* draw monitors */
static void drawMon(Player *p_pl) {
    int x = xmax/2 - 10;
    char str[6] = "HP: ";
    str[4] = (p_pl->obj).life + '0';
    DrawBlocks(ymax, xmax, ymax, x, str); 
    return ;
}

//--------------------------------------------------
// Def :    Find empty bullet spaces and inserts appropriate bullet type
// Para :   bullet array address, array length
// Return : void
//--------------------------------------------------
void firing (Bullet* bullets, int len_bu, int fire, int angle) {
    Bullet* p_bu;
    int vx = 4 * cos(angle),  vy = 4*sin(angle);


    /* Must be mode=2 */
    editMobj(2,bullets,7,ymax - 10,1,1,3,3,1,drawBullet1);
    

#ifdef DEFIGHT
    printf("Bullet allocation failed. \n");
#endif
}


void drawBullet1(double px, double py) {
#ifdef DEFIGHT
    printf("drawing bullet 1\n");
#endif
    char l1[] = "$...";
    DrawBlocks(ymax, xmax, py, px, l1);
}
void drawBullet2(double px, double py) {
#ifdef DEFIGHT
    printf("drawing bullet 2\n");
#endif
    char l2[] = "#...";
    DrawBlocks(ymax, xmax, py, px, l2);
}

void drawEnemy1 (double px, double py) {
    //width is 5
    int x, y;
    x = (int) px - 2;
    y = (int) py;
    char l1[] = "././.";
    char l2[] = "| . |"; 
    char l3[] = "| . |";
    char l4[] = " | |.";
    char l5[] = " / /.";
    DrawBlocks(ymax, xmax, y-2, x, l1);
    DrawBlocks(ymax, xmax, y-1, x, l2);
    DrawBlocks(xmax, xmax, y, x, l3);
    DrawBlocks(ymax, xmax, y-1, x, l4);
    DrawBlocks(ymax, xmax, y-2, x, l5);
}

void drawEnemy2 (double px, double py) {
    //width is 7
    int x, y;
    x = (int) px - 3;
    y = (int) py;
    char l1[] = " .___. ";
    char l2[] = "/'.'.'\\";
    char l3[] = ".'.'.'.";
    char l4[] = ".'.'.'.";
    char l5[] = ".'.'.'.";
    char l6[] = "\\'.'.'/";
    char l7[] = " .---. ";
    DrawBlocks(ymax, xmax, y-3, x, l1);
    DrawBlocks(ymax, xmax,y-2, x, l2);
    DrawBlocks(ymax, xmax,y-1, x, l3);
    DrawBlocks(ymax, xmax,y, x, l4);
    DrawBlocks(ymax, xmax,y-1, x, l5);
    DrawBlocks(ymax, xmax,y-2, x, l6);
    DrawBlocks(ymax, xmax,y-3, x, l7);
}

void drawPlayer (double px, double py) {
    int x, y;
    x = (int) px -3;
    y = (int) py;
    char l1[] = "0000000";
    char l2[] = "0000000";
    char l3[] = "0000000";
    char l4[] = "0000000";
    char l5[] = "0000000";
    char l6[] = "0000000";
    char l7[] = "0000000";
    DrawBlocks(ymax, xmax,y-3, x, l1);
    DrawBlocks(ymax, xmax,y-2, x, l2);
    DrawBlocks(ymax, xmax,y-1, x, l3);
    DrawBlocks(ymax, xmax,y, x, l4);
    DrawBlocks(ymax, xmax,y-1, x, l5);
    DrawBlocks(ymax, xmax,y-2, x, l6);
    DrawBlocks(ymax, xmax,y-3, x, l7);
}


//---------------------------------
//  Def: edit Mobj
//  Para :  void* ptr, px, py, vx, vy, sx, sy, FunctionName
//  Return :    void
//--------------------------------
void editMobj(int mode, void* ptr, double px, double py, double vx, double vy, double sx, double sy, int life, void (*draw) (double px, double py)) {
    Player* p_pl; 
    Enemy* p_en;
    Bullet* p_bu;
    if (mode==0) {
        p_pl = (Player*) ptr;
        (p_pl->obj).px=px; (p_pl->obj).py=py;
        (p_pl->obj).vx=vx; (p_pl->obj).vy=vy;
        (p_pl->obj).sx=sx; (p_pl->obj).sy=vy;
        (p_pl->obj).life=life;
        (p_pl->draw) = draw;
    }
    else if (mode==1) {
        p_en = (Enemy*) ptr;
        (p_en->obj).px=px; (p_en->obj).py=py;
        (p_en->obj).vx=vx; (p_en->obj).vy=vy;
        (p_en->obj).sx=sx; (p_en->obj).sy=vy;
        (p_en->obj).life=life;
        (p_en->draw) = draw;
    }
    else if (mode==2) {
        p_bu = (Bullet*) ptr;
        (p_bu->obj).px=px; (p_bu->obj).py=py;
        (p_bu->obj).vx=vx; (p_bu->obj).vy=vy;
        (p_bu->obj).sx=sx; (p_bu->obj).sy=vy;
        (p_bu->obj).life=life;
        (p_bu->draw) = draw;
    }
    else {
        printf("Doesn't recognize the mode\n");
        return;
    }


}
