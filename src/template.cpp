//gaming in 160*50
#include "gameutil.h"
using namespace std;

//initialize player's position
static void init_item_params(ITEM *p_win);
//initilaize boundary's position
static void init_win_params(WIN *p_win);
//initialize NPC1's position
static void init_npc1_params(NPC1 *p_win);
//initialize NPC2's position
static void init_npc2_params(NPC2 *p_win);
//initialize Treasure's position
static void init_treas_params(Treas *p_win);
//printing
static void create_box(WIN *win, bool flag,ITEM *item,NPC1 *npc1,NPC2 *npc2,Treas *treas,int Coins, int HP,bool is_weapon);

//initialize player's position(boss)
static void init_item_params_boss(ITEM *p_win);
//initialize boundary's position(boss)
static void init_win_params_boss(WIN *p_win);
//initialize boss's position(boss)
static void init_boss_params_boss(Boss *p_win);
//initialize spine(boss)
static void init_spine_params_boss(Spine *spine_down, Spine *spine_up, Spine *spine_left, Spine *spine_right);
//printing(boss)
static void create_boss(WIN *win,bool flag,ITEM *item,bool is_item,Boss *boss1,bool is_boss1,int wave_weapon,int HP, int boss_HP,Spine *spine_down,Spine *spine_up, Spine *spine_left,Spine *spine_right);

static void npc1_action(int &HP, int &Coins, WIN *win)
{
	int ch;
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	mvprintw(win->starty + win->height + 2,win->startx,"profitter: I have a bottle of magic agentia!");
	refresh();
	sleep(2.5);
	mvprintw(win->starty + win->height + 3,win->startx,"profitter: Do you want to try it!");
	refresh();
	sleep(2.5);
	mvprintw(win->starty + win->height + 4,win->startx,"profitter: It costs you 20 coins!  (y/n)");
	refresh();
	ch = getch();
	while(ch != 'y' and ch != 'n'){
		ch = getch();	
	}
	if(ch == 'y'){
		if(Coins < 20){
			mvprintw(win->starty + win->height + 5,win->startx,"player1: Fine, give me that!");
			refresh();
			sleep(2.5);
			mvprintw(win->starty + win->height + 6,win->startx,"profitter: you can't pay for it, I never work for charity!");
			refresh();
			sleep(2.5);
			attron(COLOR_PAIR(4));
			mvprintw(win->starty + win->height + 7,win->startx,"Nothing happened...");
			attron(COLOR_PAIR(4));
			refresh();
			sleep(2.5);
		}
		else{
			Coins = Coins - 20;
			mvprintw(win->starty + win->height + 5,win->startx,"player1: Fine, give me that!");
			refresh();
			sleep(2.5);
			int i;
			i = rand() % 2;
			if(i == 0){
				HP = HP - 15;
				mvprintw(win->starty + win->height + 6,win->startx,"player1: Shift, it is toxic!!!");
				refresh();
				sleep(2.5);
				attron(COLOR_PAIR(4));
				mvprintw(win->starty + win->height + 7,win->startx,"Toxic!!! HP - 15, Coins - 20...");
				attron(COLOR_PAIR(4));
				refresh();
				sleep(2.5);
			}
			else{
				HP = HP + 10;
				mvprintw(win->starty + win->height + 6,win->startx,"player1: Well, I am feeling better!!!");
				refresh();
				sleep(2.5);
				attron(COLOR_PAIR(4));
				mvprintw(win->starty + win->height + 7,win->startx,"Healing!!! HP + 10, Coins - 20...");
				attron(COLOR_PAIR(4));
				refresh();
				sleep(2.5);
			}
		}
	}
	else{
		mvprintw(win->starty + win->height + 5,win->startx,"player1: Nope!");
		refresh();
		sleep(2.5);
		attron(COLOR_PAIR(4));
		mvprintw(win->starty + win->height + 6,win->startx,"Nothing happened...");
		attron(COLOR_PAIR(4));
		refresh();
		sleep(2.5);
	}
}

static void treasure_action(bool &is_weapon,WIN *win)
{
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	mvprintw(win->starty + win->height + 2,win->startx,"player1 open the treasure!");
	attroff(COLOR_PAIR(4));
	refresh();
	sleep(2.5);
	if(is_weapon){
		attron(COLOR_PAIR(4));
		mvprintw(win->starty + win->height + 3,win->startx,"player1 find nothing...");
		attroff(COLOR_PAIR(4));
		refresh();
	}
	else{
		attron(COLOR_PAIR(4));
		mvprintw(win->starty + win->height + 3,win->startx,"player1 find his sword!!!");
		attroff(COLOR_PAIR(4));
		refresh();
		is_weapon = true;
	}
	sleep(2.5);
}

static void npc2_action(bool &is_flash,WIN *win,int &Coins)
{	
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	if(is_flash == true){
		mvprintw(win->starty + win->height + 2,win->startx,"master: I have nothing to teach you!");
		refresh();
		sleep(2.5);
		attron(COLOR_PAIR(4));
		mvprintw(win->starty + win->height + 3,win->startx,"Nothing happened...");
		attron(COLOR_PAIR(4));
		refresh();
		sleep(2.5);
		return;
	}

	int ch;
	mvprintw(win->starty + win->height + 2,win->startx,"master: I can teach you something!");
	refresh();
	sleep(2.5);
	mvprintw(win->starty + win->height + 3,win->startx,"master: 20 coins for tutition fee!  (y/n)!");
	refresh();
	ch = getch();
	while(ch != 'y' and ch != 'n'){
		ch = getch();	
	}
	if(ch == 'y'){
		if(Coins < 20){
			mvprintw(win->starty + win->height + 4,win->startx,"player1: Yes, my teacher!");
			refresh();
			sleep(2.5);
			mvprintw(win->starty + win->height + 5,win->startx,"master: you can't pay for it, Sorry!");
			refresh();
			sleep(2.5);
			attron(COLOR_PAIR(4));
			mvprintw(win->starty + win->height + 6,win->startx,"Nothing happened...");
			attron(COLOR_PAIR(4));
			refresh();
			sleep(2.5);
		}
		else{
			Coins = Coins - 20;
			mvprintw(win->starty + win->height + 4,win->startx,"player1: Yes, my teacher!");
			refresh();
			sleep(2.5);
			attron(COLOR_PAIR(4));
			mvprintw(win->starty + win->height + 5,win->startx,"Achievement in flash!!! press 'f' before movement to get flash...");
			attron(COLOR_PAIR(4));
			refresh();
			is_flash = true;
			sleep(2.5);
		}
	}
	else{
		mvprintw(win->starty + win->height + 4,win->startx,"player1: I will learn it next time!");
		refresh();
		sleep(2.5);
		attron(COLOR_PAIR(4));
		mvprintw(win->starty + win->height + 5,win->startx,"Nothing happened...");
		attron(COLOR_PAIR(4));
		refresh();
		sleep(2.5);
	}
}
//enter boss room
static int boss_action(int &HP, bool is_flash)
{	
	timeout(0);
	int res = 0;
	WIN win;
	ITEM item;
	Spine spine_down;
	Spine spine_up;
	Spine spine_left;
	Spine spine_right;
	bool is_item = true;
	Boss boss1;
	bool is_boss1 = true;
	bool is_boss2 = true;
	int boss_HP = 1000;
	int wave_weapon = 0;
	int count = 0;
	int dot_x = 0;
	int dot_y = 0;
	int lock_HP = 0;
	int lock_boss = 0;
	int lock_spine = 0;
	int which_spine = 0;
	int attack = 0;
	int lock_attack = 0;
	init_win_params_boss(&win);
	init_item_params_boss(&item);
	init_boss_params_boss(&boss1);
	init_spine_params_boss(&spine_down, &spine_up, &spine_left, &spine_right);
	create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
	create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
	int ch;
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	mvprintw(win.starty + win.height + 2,win.startx,"Press w/a/s/d to attack!");
	refresh();
	sleep(2.5);
	mvprintw(win.starty + win.height + 3,win.startx,"Ready For Fight?  (y)");
	refresh();
	attroff(COLOR_PAIR(4));
	ch = getch();
	while(ch != 'y'){
		ch = getch();
	}
	create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
	while((ch = getch()) != KEY_F(1))
	{	
		count = (count == 1999) ? 0 : count + 1;
		if(count % 1000 == 0){
			int i;
			i = rand() % 4;
			if(i == 0){
				spine_down.is_spine = true;
			}
			else if(i == 1){
				spine_up.is_spine = true;
			}
			else if(i == 2){
				spine_left.is_spine = true;
			}
			else{
				spine_right.is_spine = true;
			}
		}
		attack = (attack == 2999) ? 0 : count + 1;
		if(attack % 2000 == 0){
			boss1.status = 1;
			lock_attack = 1;
		}
		lock_HP = (lock_HP != 0 and lock_HP < 50) ? lock_HP + 1 : 0;
		lock_boss = (lock_boss == 30) ? 0 : lock_boss + 1;
		lock_spine = (lock_spine == 7) ? 0 : lock_spine + 1;
		lock_attack = (lock_attack != 0 and lock_attack < 400) ? lock_attack + 1 : 0;
		if(lock_attack == 0){
			boss1.status = 0;
		}
		wave_weapon = 0;
		if(ch == 'f'){
			ch = getch();
			while(ch != KEY_LEFT and ch != KEY_RIGHT and ch != KEY_UP and ch != KEY_DOWN){
				ch = getch();
			}
			switch(ch)
			{
				case KEY_LEFT:
					create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					if(item.startx > win.startx + 21 and is_flash){
						item.startx = item.startx-20;
					}
					create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					break;
				case KEY_RIGHT:
					create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					if(item.startx + item.width - 1 < win.startx + win.width - 22 and is_flash){
						item.startx = item.startx+20;
					}
					create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					break;
				case KEY_UP:
					create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					if(item.starty > win.starty + 11 and is_flash){
						item.starty = item.starty-10;
					}
					create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					break;
				case KEY_DOWN:
					create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					if(item.starty + item.height - 1 < win.starty + win.height - 12 and is_flash){
						item.starty = item.starty+10;
					}
					create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					break;
			}
		}

		switch(ch)
		{
			case KEY_RIGHT:
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				if(item.startx + item.width - 1 < win.startx + win.width - 2){
					++item.startx;
				}
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case KEY_LEFT:
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				if(item.startx > win.startx + 1){
					--item.startx;
				}
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case KEY_UP:
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				if(item.starty > win.starty + 1){
					--item.starty;
				}
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case KEY_DOWN:
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				if(item.starty + item.height - 1 < win.starty + win.height - 2){
					++item.starty;
				}
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case 'w':
				wave_weapon = 1;
				dot_y = item.starty - 4;
				dot_x = item.startx + 5;
				if(dot_y <= boss1.starty + 4 and dot_y >= boss1.starty and dot_x <= boss1.startx + 13 and dot_x >= boss1.startx){
					boss_HP = boss_HP - 10;
				}
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case 's':
				wave_weapon = 2;
				dot_y = item.starty + 8;
				dot_x = item.startx - 1;
				if(dot_y <= boss1.starty + 4 and dot_y >= boss1.starty and dot_x <= boss1.startx + 13 and dot_x >= boss1.startx){
					boss_HP = boss_HP - 10;
				}
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case 'a':
				wave_weapon = 3;
				dot_y = item.starty + 1;
				dot_x = item.startx - 5;
				if(dot_y <= boss1.starty + 4 and dot_y >= boss1.starty and dot_x <= boss1.startx + 13 and dot_x >= boss1.startx){
					boss_HP = boss_HP - 10;
				}
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case 'd':
				wave_weapon = 4;
				dot_y = item.starty + 3;
				dot_x = item.startx + 9;
				if(dot_y <= boss1.starty + 4 and dot_y >= boss1.starty and dot_x <= boss1.startx + 13 and dot_x >= boss1.startx){
					boss_HP = boss_HP - 10;
				}
				create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				break;
			case ERR:
				if(count % 20 == 0){
					create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
					create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
				}
				break;
		}
		if(abs(item.starty + 2 - (boss1.starty + 2)) < 5 and abs(item.startx + 2 - (boss1.startx + 6)) < 8 and lock_HP == 0){
			HP = HP - 2;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		//judge HP minus by boss attack
		if(boss1.status == 1 and abs(item.startx + 2 - (boss1.startx + 6)) < 3 and lock_HP == 0){
			HP = HP - 5;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(boss1.status == 1 and abs(item.starty + 2 - (boss1.starty + 2)) < 3 and lock_HP == 0){
			HP = HP - 5;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		//judge HP minus by spine
		if(spine_down.is_spine and abs(spine_down.starty - (item.starty + 2)) <= 2 and lock_HP == 0){
			HP = HP - 8;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(spine_up.is_spine and abs(spine_up.starty - (item.starty + 2)) <= 2 and lock_HP == 0){
			HP = HP - 8;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(spine_left.is_spine and abs(spine_left.startx - (item.startx + 2)) <= 2 and lock_HP == 0){
			HP = HP - 8;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(spine_right.is_spine and abs(spine_right.startx - (item.startx + 2)) <= 2 and lock_HP == 0){
			HP = HP - 8;
			lock_HP = 1;
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		
		if(spine_down.is_spine and lock_spine == 0){
			lock_spine = 1;
			if(spine_down.starty == 5){
				spine_down.starty = 44;
				spine_down.is_spine = false;
			}
			else{
				spine_down.starty = spine_down.starty - 1;
			}
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(spine_up.is_spine and lock_spine == 0){
			lock_spine = 1;
			if(spine_up.starty == 44){
				spine_up.starty = 5;
				spine_up.is_spine = false;
			}
			else{
				spine_up.starty = spine_up.starty + 1;
			}
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(spine_left.is_spine and lock_spine == 0){
			lock_spine = 1;
			if(spine_left.startx == 134){
				spine_left.startx = 5;
				spine_left.is_spine = false;
			}
			else{
				spine_left.startx = spine_left.startx + 1;
			}
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(spine_right.is_spine and lock_spine == 0){
			lock_spine = 1;
			if(spine_right.startx == 5){
				spine_right.startx = 134;
				spine_right.is_spine = false;
			}
			else{
				spine_right.startx = spine_right.startx - 1;
			}
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		
		if((boss1.starty + 2 != item.starty + 2 or boss1.startx + 6 != item.startx + 2) and lock_boss == 0){
			lock_boss = 1;
			if(abs(boss1.starty + 2 - (item.starty + 2)) < abs(boss1.startx + 6 - (item.startx + 2))){
				if(boss1.startx + 6 < item.startx + 2){
					boss1.startx = boss1.startx + 2;
				}
				else{
					boss1.startx = boss1.startx - 2;
				}
			}
			else{
				if(boss1.starty + 2 < item.starty + 2){
					boss1.starty = boss1.starty + 2;
				}
				else{
					boss1.starty = boss1.starty - 2;
				}
			}
			create_boss(&win,false,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
			create_boss(&win,true,&item,is_item,&boss1,is_boss1,wave_weapon,HP,boss_HP,&spine_down,&spine_up,&spine_left,&spine_right);
		}
		if(boss_HP == 0){
			res = 1;
			break;
		}
		if(HP <= 0){
			res = 2;
			break;
		}
		usleep(10000);
	}
	return res;
}
//print boss room
static void create_boss(WIN *p_win,bool flag,ITEM *item,bool is_item,Boss *boss1,bool is_boss1,int wave_weapon,int HP, int boss_HP,Spine *spine_down,Spine *spine_up,Spine *spine_left,Spine *spine_right)
{	
	int i, j;
	int x, y, w, h;
	
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == false){
		for(j = y - 3; j <= y + h + 2; ++j)
			for(i = x - 4; i <= x + w + 3; ++i)
				mvaddch(j, i, ' ');
	}
	else{	
		//clean the event
		mvhline(y+h+2, x, ' ', 100);
		mvhline(y+h+3, x, ' ', 100);
		mvhline(y+h+4, x, ' ', 100);
		mvhline(y+h+5, x, ' ', 100);
		//print HP and Boss HP
		attron(COLOR_PAIR(2));
		mvprintw(y + h - 3, x + 1, "HP: ");
		printw("%d",HP);
		mvprintw(y + h - 2, x + 1, "BOSS HP: ");
		printw("%d",boss_HP); 
		attroff(COLOR_PAIR(2));
		//print boundary
		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w - 1, p_win->border.tr);
		mvaddch(y + h - 1, x, p_win->border.bl);
		mvaddch(y + h - 1, x + w - 1, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 2);
		mvhline(y + h - 1, x + 1, p_win->border.bs, w - 2);
		mvvline(y + 1, x, p_win->border.ls, h - 2);
		mvvline(y + 1, x + w - 1, p_win->border.rs, h - 2);
		//print boss room
		mvprintw(y + 1,x + 43,"---  ---  ---  ---    ---  ---  ---  -----");
		mvprintw(y + 2,x + 43,"| |  | |  | |  |      |    | |  | |  | | |");
		mvprintw(y + 3,x + 43,"---  | |  | |  ---    |    | |  | |  | | |");
		mvprintw(y + 4,x + 43,"| |  | |  | |    |    |    | |  | |  | | |");
		mvprintw(y + 5,x + 43,"---  ---  ---  ---    |    ---  ---  | | |");
		//print boss1
		if(is_boss1){
			if(boss1->status == 0){
				attron(COLOR_PAIR(3));
			}
			else{
				attron(COLOR_PAIR(6));
			}
			mvprintw(boss1->starty+0,boss1->startx,"--------------");
			mvprintw(boss1->starty+1,boss1->startx,"|   \\    /   |");
			mvprintw(boss1->starty+2,boss1->startx,"|            |");
			mvprintw(boss1->starty+3,boss1->startx,"|    ----    |");
			mvprintw(boss1->starty+4,boss1->startx,"--------------");
			mvprintw(boss1->starty+5,boss1->startx,"     BOSS     ");
			if(boss1->status == 0){
				attroff(COLOR_PAIR(3));
			}
			else{
				attroff(COLOR_PAIR(6));
			}
		}
		//print boss1 attack
		if(boss1->status == 1){
			attron(COLOR_PAIR(6));
			//left side attack
			mvhline(boss1->starty+2,p_win->startx+1,'<',boss1->startx - 5);
			//right side attack
			mvhline(boss1->starty+2,boss1->startx+14,'>',134 - boss1->startx - 14);
			//up side attack
			mvvline(p_win->starty+1,boss1->startx+6,'^',boss1->starty - 5);
			//down side attack
			mvvline(boss1->starty+5,boss1->startx+6,'v',44 - boss1->starty - 5);
			attroff(COLOR_PAIR(6));
		}
		//print spine
		if(spine_down->is_spine){
			attron(COLOR_PAIR(3));
			mvhline(spine_down->starty,spine_down->startx,'^',w);
			attroff(COLOR_PAIR(3));
		}
		if(spine_up->is_spine){
			attron(COLOR_PAIR(3));
			mvhline(spine_up->starty,spine_up->startx,'v',w);
			attroff(COLOR_PAIR(3));
		}
		if(spine_left->is_spine){
			attron(COLOR_PAIR(3));
			mvvline(spine_left->starty,spine_left->startx,'>',h);
			attroff(COLOR_PAIR(3));
		}
		if(spine_right->is_spine){
			attron(COLOR_PAIR(3));
			mvvline(spine_right->starty,spine_right->startx,'<',h);
			attroff(COLOR_PAIR(3));
		}
		//print sword
		if(wave_weapon == 0){
			attron(COLOR_PAIR(5));
		        mvprintw(item->starty, item->startx+5,"/\\");
			mvprintw(item->starty+1, item->startx+5,"||");
			mvprintw(item->starty+2, item->startx+5,"||");
			mvprintw(item->starty+3, item->startx+5,"--");
			mvprintw(item->starty+4, item->startx+5,"<>");
			attroff(COLOR_PAIR(5));
		}
		if(wave_weapon == 1){
			attron(COLOR_PAIR(5));
			mvprintw(item->starty-4, item->startx+5,"/\\");
			mvprintw(item->starty-3, item->startx+5,"||");
			mvprintw(item->starty-2, item->startx+5,"||");
			mvprintw(item->starty-1, item->startx+5,"--");
			mvprintw(item->starty-0, item->startx+5,"<>");
			attroff(COLOR_PAIR(5));
		}
		if(wave_weapon == 2){
			attron(COLOR_PAIR(5));
			mvprintw(item->starty+4, item->startx-2,"<>");
			mvprintw(item->starty+5, item->startx-2,"--");
			mvprintw(item->starty+6, item->startx-2,"||");
			mvprintw(item->starty+7, item->startx-2,"||");
			mvprintw(item->starty+8, item->startx-2,"\\/");
			attroff(COLOR_PAIR(5));
		}
		if(wave_weapon == 3){
			attron(COLOR_PAIR(5));
			mvprintw(item->starty, item->startx-5,"/--|^");
			mvprintw(item->starty+1, item->startx-5,"\\--|v");
			attroff(COLOR_PAIR(5));
		}
		if(wave_weapon == 4){
			attron(COLOR_PAIR(5));
			mvprintw(item->starty+3, item->startx+5,"^|--\\");
			mvprintw(item->starty+4, item->startx+5,"v|--/");
			attroff(COLOR_PAIR(5));
		}
		//print player
		if(is_item){
			mvhline(item->starty,item->startx,'-',item->width);
			mvvline(item->starty+1,item->startx,'|',item->height-2);
			mvhline(item->starty+item->height-1,item->startx,'-',item->width);
			mvvline(item->starty+1,item->startx+item->width-1,'|',item->height-2);
			mvprintw(item->starty+5, item->startx-1,"player1");
		}
		//print eyes and nose
		mvaddch(item->starty+1,item->startx+1,'-');
		mvaddch(item->starty+1,item->startx+3,'-');
		mvaddch(item->starty+3,item->startx+2,'-');
	}
	refresh();
}


int main4(void)
{	WIN win;
	ITEM item;
	NPC1 npc1;
	NPC2 npc2;
	Treas treas;
	int ch;

	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Initialize the boundary and player parameters and npc1 parameters*/
	init_win_params(&win);
	init_item_params(&item);
	init_npc1_params(&npc1);
	init_npc2_params(&npc2);
	init_treas_params(&treas);
	attron(COLOR_PAIR(1));
    
    mvhline(0, 0, ' ', 100);
	printw("STAGE 4 !!!!!!!!");
	
	refresh();
	attroff(COLOR_PAIR(1));

	int HP = 100;
	int Coins = 100;
	bool is_weapon = false;
	bool is_flash = false;
	int res = 0;

	create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);

	while((ch = getch()) != 'q')
	{	
		if(ch == 'f'){
			ch = getch();
			while(ch != KEY_LEFT and ch != KEY_RIGHT and ch != KEY_UP and ch != KEY_DOWN){
				ch = getch();
			}
			switch(ch)
			{
				case KEY_LEFT:
					create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					if(item.startx > win.startx + 21 and is_flash){
						item.startx = item.startx-20;
					}
					create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					break;
				case KEY_RIGHT:
					create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					if(item.startx + item.width - 1 < win.startx + win.width - 22 and is_flash){
						item.startx = item.startx+20;
					}
					create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					break;
				case KEY_UP:
					create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					if(item.starty > win.starty + 11 and is_flash){
						item.starty = item.starty-10;
					}
					create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					break;
				case KEY_DOWN:
					create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					if(item.starty + item.height - 1 < win.starty + win.height - 12 and is_flash){
						item.starty = item.starty+10;
					}
					create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
					break;
			}
		}

		switch(ch)
		{	
			case KEY_RIGHT:
				create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				if(item.startx + item.width - 1 < win.startx + win.width - 2){
					++item.startx;
				}
				create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				break;
			case KEY_LEFT:
				create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				if(item.startx > win.startx + 1){
					--item.startx;
				}
				create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				break;
			case KEY_UP:
				create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				if(item.starty > win.starty + 1){
					--item.starty;
				}
				create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				break;
			case KEY_DOWN:
				create_box(&win,FALSE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				if(item.starty + item.height - 1 < win.starty + win.height - 2){
					++item.starty;
				}
				create_box(&win,TRUE,&item,&npc1,&npc2,&treas,Coins,HP,is_weapon);
				break;	
		}
		//npc1 event
		if(item.starty == npc1.starty+1 and item.startx == npc1.startx+10){
			npc1_action(HP,Coins,&win);
		}
		//treasure event
		if(item.starty == treas.starty-1 and item.startx == treas.startx-7){
			treasure_action(is_weapon,&win);
		}
		//npc2 event
		if(item.starty == npc2.starty and item.startx == npc2.startx-7){
			npc2_action(is_flash,&win,Coins);
		}
		//entrance event
		if(item.starty == win.starty + win.height - 6 and item.startx == win.startx + win.width - 6){
			if(is_weapon == false){
                static double old = 0;
                double cur = getime();
                if (cur - old > 10) {
    				init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	    			attron(COLOR_PAIR(4));
		    		mvprintw(win.starty + win.height + 2,win.startx,"Please find your sword!");
			    	attroff(COLOR_PAIR(4));
				    refresh();
    				sleep(2.5);
                    old = cur;
                }
			}
			else{
				//enter boss room
				res = boss_action(HP,is_flash);
				break;
			}
		}
		sleep(0.5);
	}
	if(res == 0){
        endwin();
        cout << "terminate\n";
        exit(0);
        return 0;
	}
	else if(res == 1){
        /* win */
        return 1;
	}
	else{
        /* lose */
        return 2;
	}
	return 0;
}
static void init_item_params(ITEM *p_win){
	p_win->height=5;
	p_win->width=5;
	p_win->starty=25;
	p_win->startx=13;
}
static void init_win_params(WIN *p_win)
{
	p_win->height = 30;
	p_win->width = 100;
	p_win->starty = 5;	
	p_win->startx = 5;
	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}
static void init_npc1_params(NPC1 *p_win)
{
	p_win->starty = 15;
	p_win->startx = 15;
	p_win->height = 5;
	p_win->width = 5;
}
static void init_npc2_params(NPC2 *p_win)
{
	p_win->starty = 18;
	p_win->startx = 80;
	p_win->height = 5;
	p_win->width = 5;
}
static void init_treas_params(Treas *p_win)
{
	p_win->starty = 25;
	p_win->startx = 58;
	p_win->height = 5;
	p_win->width = 7;
}
static void create_box(WIN *p_win, bool flag,ITEM *item,NPC1 *npc1 ,NPC2 *npc2,Treas *treas, int Coins, int HP,bool is_weapon)
{	
	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{	
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(5, COLOR_GREEN, COLOR_BLACK);
		//clean the event
		mvhline(y+h+2, x, ' ', 100);
		mvhline(y+h+3, x, ' ', 100);
		mvhline(y+h+4, x, ' ', 100);
		mvhline(y+h+5, x, ' ', 100);
		mvhline(y+h+6, x, ' ', 100);
		mvhline(y+h+7, x, ' ', 100);
		mvhline(y+h+8, x, ' ', 100);
		//print HP and Coins
		attron(COLOR_PAIR(2));
		mvprintw(y + h - 3, x + 1, "HP: ");
		printw("%d",HP);
		attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(3));
		mvprintw(y + h - 2, x + 1, "Coins: ");
		printw("%d",Coins);
		attroff(COLOR_PAIR(3));
		//print store
		mvprintw(y + 1,x + 35,"---  ---  ---  ---  ---");
		mvprintw(y + 2,x + 35,"|     |   | |  |    |  ");
		mvprintw(y + 3,x + 35,"---   |   | |  |    ---");
		mvprintw(y + 4,x + 35,"  |   |   | |  |    |  ");
		mvprintw(y + 5,x + 35,"---   |   ---  |    ---");
		//print boundary
		mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w - 1, p_win->border.tr);
		mvaddch(y + h - 1, x, p_win->border.bl);
		mvaddch(y + h - 1, x + w - 1, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 2);
		mvhline(y + h - 1, x + 1, p_win->border.bs, w - 2);
		mvvline(y + 1, x, p_win->border.ls, h - 2);
		mvvline(y + 1, x + w - 1, p_win->border.rs, h - 2);
		//print npc1
		attron(COLOR_PAIR(3));
		mvprintw(npc1->starty, npc1->startx,"------- |");
		mvprintw(npc1->starty+1, npc1->startx,"| / \\ | o");
		mvprintw(npc1->starty+2, npc1->startx,"| --- |");
		mvprintw(npc1->starty+3, npc1->startx,"| | | |");
		mvprintw(npc1->starty+4, npc1->startx,"| --- |     (*)");
		mvprintw(npc1->starty+5, npc1->startx-1,"profitter");
		attroff(COLOR_PAIR(3));
		//print npc2
		attron(COLOR_PAIR(3));
		mvprintw(npc2->starty, npc2->startx,"----- |");
		mvprintw(npc2->starty+1, npc2->startx,"|- -| o");
		mvprintw(npc2->starty+2, npc2->startx,"| - |");
		mvprintw(npc2->starty+3, npc2->startx-5,"(*)  -----");
		mvprintw(npc2->starty+4, npc2->startx,"master");
		attroff(COLOR_PAIR(3));
		//print treasure
		attron(COLOR_PAIR(5));
		mvprintw(treas->starty, treas->startx,"-------");
		mvprintw(treas->starty+1, treas->startx,"| |-| |");
		mvprintw(treas->starty+2, treas->startx-5,"(*)  |     |");
		mvprintw(treas->starty+3, treas->startx,"-------");
		mvprintw(treas->starty+4, treas->startx,"treasure");
		attroff(COLOR_PAIR(5));
		//print entrance to boss room
		mvprintw(y + h - 6, x + w - 2, "/");
		mvprintw(y + h - 5, x + w - 3, "/");
		mvprintw(y + h - 4, x + w - 4, "/");
		mvprintw(y + h - 3, x + w - 8, "-->|(*)");
		mvprintw(y + h - 2, x + w - 5, "|");
		//print sword
		if(is_weapon == true){
			attron(COLOR_PAIR(5));
		        mvprintw(item->starty, item->startx+5,"/\\");
			mvprintw(item->starty+1, item->startx+5,"||");
			mvprintw(item->starty+2, item->startx+5,"||");
			mvprintw(item->starty+3, item->startx+5,"--");
			mvprintw(item->starty+4, item->startx+5,"<>");
			attroff(COLOR_PAIR(5));
		}
		//print player
		mvhline(item->starty,item->startx,'-',item->width);
		mvvline(item->starty+1,item->startx,'|',item->height-2);
		mvhline(item->starty+item->height-1,item->startx,'-',item->width);
		mvvline(item->starty+1,item->startx+item->width-1,'|',item->height-2);
		mvprintw(item->starty+5, item->startx-1,"player1");
		//print eyes and nose
		mvaddch(item->starty+1,item->startx+1,'-');
		mvaddch(item->starty+1,item->startx+3,'-');
		mvaddch(item->starty+3,item->startx+2,'-');
	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();
}

static void init_item_params_boss(ITEM *p_win){
	p_win->height=5;
	p_win->width=5;
	p_win->starty=33;
	p_win->startx=15;
}

static void init_win_params_boss(WIN *p_win)
{
	p_win->height = 40;
	p_win->width = 130;
	p_win->starty = 5;
	p_win->startx = 5;
	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
}

static void init_boss_params_boss(Boss *p_win)
{
	p_win->height = 5;
	p_win->width = 14;
	p_win->starty = 15;
	p_win->startx = 50;
	p_win->status = 0;
}

static void init_spine_params_boss(Spine *spine_down, Spine *spine_up, Spine *spine_left, Spine *spine_right)
{
	spine_down->startx = 5;
	spine_down->starty = 44;
	spine_down->is_spine = false;

	spine_up->startx = 5;
	spine_up->starty = 5;
	spine_up->is_spine = false;

	spine_left->startx = 5;
	spine_left->starty = 5;
	spine_left->is_spine = false;
	
	spine_right->startx = 134;
	spine_right->starty = 5;
	spine_right->is_spine = false;

}









