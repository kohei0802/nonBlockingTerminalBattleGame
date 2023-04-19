#include "support.h"

#if (0)
void Fatal(char *msg)
{
    endwin();
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void InitColor(int bg)
{
    if (bg < -1)
        return;

    start_color();
    use_default_colors();

    /* 文字表示用の色 */
    assume_default_colors(COLOR_BLACK, bg); // init_pair(0, ...);
    init_pair(1, COLOR_RED, bg);
    init_pair(2, COLOR_GREEN, bg);
    init_pair(3, COLOR_YELLOW, bg);
    init_pair(4, COLOR_BLUE, bg);
    init_pair(5, COLOR_MAGENTA, bg);
    init_pair(6, COLOR_CYAN, bg);
    init_pair(7, COLOR_WHITE, bg);

    /* ブロックキャラクタ表示用の色 */
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
    init_pair(11, COLOR_RED, COLOR_RED);
    init_pair(12, COLOR_GREEN, COLOR_GREEN);
    init_pair(13, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(14, COLOR_BLUE, COLOR_BLUE);
    init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(16, COLOR_CYAN, COLOR_CYAN);
    init_pair(17, COLOR_WHITE, COLOR_WHITE);

    /* 背景の色 */
    if (bg >= 0)
    {
        bkgd(COLOR_PAIR(7 - bg));
    }
    else
    {
        bkgd(COLOR_PAIR(0));
    }
}

// 色の利用
void UseColor(int c)
{
    attron(COLOR_PAIR(c));
}
#endif

// ブロック列の表示
void DrawBlocks(int ymax, int xmax, int y, int x, char s[])
{
    int w = xmax, h = ymax;

    getmaxyx(stdscr, h, w);
    if (y < 0)
        return;
    if (y >= h)
        return;
    while (*s != '\0')
    {
        if (x < 0)
            ;
        else if (x >= w)
            ;
        else if (*s != ' ')
            mvaddch(y, x, *s);
        s++;
        x++;
    }
}



/* 乱数の処理 */

// 乱数の初期化
void InitRand()
{
    srand(time(NULL)); /*to make the sequence of random numbers in
                      the computer's storage become really random*/
}

// 0 以上 n 未満の整数乱数
int Rand(int n)
{
    return ((int)(n * (rand() / (RAND_MAX + 1.0))));
}


/* タイマーの処理 */

static struct timeval start_time;

// タイマー初期化
void InitWait()
{
    gettimeofday(&start_time, NULL);
}

static int diffTime(struct timeval *t1, struct timeval *t2)
{
    static int sec, msec;

    sec = t1->tv_sec - t2->tv_sec;
    msec = (t1->tv_usec - t2->tv_usec) / 1000;

    if (msec < 0)
    {
        sec -= 1;
        msec += 1000;
    }
    return (sec * 1000 + msec);
}

static int getTime()
{
    static struct timeval now;

    gettimeofday(&now, NULL);
    return (diffTime(&now, &start_time));
}

// 処理時間一定版 sleep()
void Wait(int msec)
{
    while (1)
    {
        if (getTime() >= msec)
            return;
    }
}
