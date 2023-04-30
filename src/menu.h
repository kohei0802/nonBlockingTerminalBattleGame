#include <stdio.h>
#include <ncurses.h>
#include <fstream>

//-----------
// Def:     Print the menu, wait for intput
// Para:    Void
// Return:  [1]Resume [2]Save [3]Quit
int menu(int x, int y);

int save(int HP, int Coins, bool next_stage, bool is_weapon, bool is_flash, bool is_upgrade);
