#include "diy.h"
using namespace std;

#define WAIT 10


struct Obj {
   int px, py, vx, vy, sx, sy; 
};

void initObj(vector<Obj> &objects);

static int game(WIN *win) {
    int ch = 0;
    vector<Obj> objects (2);

    objects[0].px = win->startx; 
    objects[0].py = win->starty + win->height/2;
    objects[0].vx = 1;
    objects[0].vy = 1;
    objects[0].sx = 0;
    objects[0].sy = 0;
    objects[1].px = win->startx + win->width - 2; 
    objects[1].py = win->starty + win->height/2;
    objects[1].vx = 1;
    objects[1].vy = 1;
    objects[1].sx = 0;
    objects[1].sy = 0;

    timeout(0);
    while (true) {
        ch = getch();
        if (ch == 'q') {
            return 0;
        }
        static double prev2 = getime();
        double cur2 = getime();
        if (cur2 - prev2 > 1.0) {
            clean_box(win);
            for (auto obj : objects) {
                mvaddch(obj.py, obj.px, '#');
            }
            refresh();
            prev2 = getime();
        }

        static double prev1 = getime();
        double cur1 = getime();
        if (cur1-prev1 > 1.0) {
            for (auto obj : objects) {
                //check if obj will fall out of screen
                if (obj.px + obj.vx >= win->startx && obj.px + obj.vx <= win->startx + win->width ) {
                    obj.px += obj.vx;
                }
                else {
                    obj.vx  =  -1 * obj.vx;
                }
                if (obj.py + obj.vy >= win->starty && obj.py + obj.vy <= win->starty + win->height ) {
                    obj.py += obj.vy;
                }
                else {
                    obj.vy  = -1 * obj.vy;
                }
            }
            prev1 = getime();
        }
    }

    return 1;

}

int minigame(WIN *win) {
    int res = 0;

    initscr();
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(20, COLOR_CYAN, COLOR_CYAN);
    init_pair(21, COLOR_YELLOW, COLOR_YELLOW);
    res = game(win);

    clean_box(win);

    if (res) {
        return 1;
    }
    else {
        return 0;
    }
    
}

