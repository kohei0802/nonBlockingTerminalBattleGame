#include <ncurses.h>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

string pdrawing="167891111111abcdefghijklabcdefghijklabcdefghijklabcdefghijkl&&&&&&&&&&&31415926535";
string bdrawing="BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"; 


// vector of char stores every characters on the player
//vector<vector<char>> look_boss(12, vector<char>(24, ' '));

struct WIN
{

    int startx, starty;
    int height, width;
    vector<string> look;

};

/*creating mutex for changing variable
 * It acts like a flag
 * There're 2 threads running that can change the variable's value
 * A flag is added so that they can only use the variable after 
 * the other thread finished using it*/

void init_look(WIN &character, string drawing, int h, int w) {
   /*it's drawers reponsibility to write the right amount of characters*/
    int index{0};
    character.height = h; character.width = w;
    character.startx = 0; character.starty = 0;
    character.look.resize(h);
    for (int r=0; r<h; r++) {
        string& str = (character.look)[r];
        for (int c=0; c<w; c++) {
            str = str + drawing[index];  
            //character.look[] is a string
            index++;
            /*index refers to index in string pdrawing*/
        }
    }    
}

int print_look(const WIN &character){
    
    int x=character.startx, y=character.starty;

    for (int r=0; r<character.height; r++) {
        mvaddstr(y+r, x, (character.look)[r].c_str());
        //mvaddch(y+r, x+c, (character.look)[r][c] | A_BOLD | A_UNDERLINE);
    }
    refresh();
    return 0;
} 


WIN player, boss;

mutex mtx_;
void change(WIN &who, int key)
{
    lock_guard<mutex> lock(mtx_);
    siwtch (key)
    {
        case KEY_LEFT: //change the vector's characters
            break;
        case KEY_RIGHT:
            break;
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
    }
}

void moveBoss(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur); //updates boss coordinates 
void moveBall(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur); 
void printPlayer(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur); 
void display(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur); 
void updateHP(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur); 

int ThreadA() {
    clear();

    while true {
        static auto old = steady_clock::now();
        cur = steady_clock::now();
        moveBoss(old, cur); //updates boss coordinates 
        moveBall(old, cur);
        printPlayer(old, cur); /*only for player, coordinate is updated on the other thread */
        display(old, cur); //include refresh();
        updateHP(old, cur); /*check collision and update HP value. 
                              Also, refresh */

        old = cur;
    }
    return 0;
}



int ThreadB() {
    int ch;
    while ((ch=getch()) != q) {
        change(player, ch);
        }
    }
    return 0;
}

int main()
{

    initscr();
    cbreak(); /*disable line buffering. pass on every thing to me*/
    noecho();

    init_look(player, pdrawing, 6, 12); //initialize startxy to 0
    init_look(boss, bdrawing, 12, 24); //initialize startxy to 0
    move(0,0);
    printw("height=%d width=%d", player.height, player.width);
    printw("height=%d width=%d", boss.height, boss.width);

    player.startx=0;
    player.starty=LINES-player.height;
    boss.startx=COLS-boss.width;
    boss.starty=LINES-boss.height;

    print_look(player);
    print_look(boss);

    refresh();

    thread th_a(ThreadA);
    thread th_b(ThreadB);
    th_a.join();
    th_b.join();

    getch();

    endwin();
    return 0;
}


void moveBoss(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur) {
    if (duration_cast<milliseconds>(cur - old).count() <= 600ms){
        ;
    }
    return;
}
void moveBall(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur) {
    if (duration_cast<milliseconds>(cur - old).count() <= 300ms){
        ;
    }
    return ;
}
void printPlayer(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur) {
    if (duration_cast<milliseconds>(cur - old).count() <= 10ms){
        ;
    }
    return ;
} 
void display(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur) {
    if (duration_cast<milliseconds>(cur - old).count() <= 10ms){
        ;
    }
    return ;
}
void updateHP(std::chrono::time_point<std::chrono::steady_clock> old, std::chrono::time_point<std::chrono::steady_clock> cur) {
    if (duration_cast<milliseconds>(cur - old).count() <= 10ms){
        ;
    }
    return ;
}
