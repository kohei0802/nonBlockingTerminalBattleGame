#include "menu.h"

using namespace std;

int menu (int x, int y) {
    mvprintw(y, x, "Enter a number option: \n");
    mvprintw(y+1, x, "[1] Resume\n");
    mvprintw(y+2, x, "[2] Save\n");
    mvprintw(y+3, x, "[3] Quit\n");

    timeout(-1);
    int input; 
    input = getch();
    timeout(0);
    return input;
}

int save (int HP, int Coins, bool next_stage, bool is_weapon, bool is_flash, bool is_upgrade) {
    ofstream fout;
    string name = "status.txt";
    fout.open(name.c_str());
    if (fout.fail()) {
        return 0;
    }

    string stage = (next_stage) ? "true" : "false";
    string weapon = (is_weapon) ? "true" : "false";
    string flash = (is_flash) ? "true" : "false";
    string upgrade = (is_upgrade) ? "true" : "false";

    fout << '1' << endl;
    fout << HP << " " << Coins << " " << stage << " " << weapon << " " << flash << " " << upgrade << endl;

    fout.close();

    return 1;
}
