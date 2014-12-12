#ifndef TXTCOLOR_H
#define TXTCOLOR_H

#define COL_RESET 0
#define COL_BRIGHT 1
#define COL_DIM 2
#define COL_UNDERLINE 3
#define COL_BLINK 4
#define COL_REVERSE 7
#define COL_HIDDEN 8

#define COL_BLACK 0
#define COL_RED 1
#define COL_GREEN 2
#define COL_YELLOW 3
#define COL_BLUE 4
#define COL_MAGENTA 5
#define COL_CYAN 6
#define COL_WHITE 7

void textcolor(int attr, int fg, int bg);

#endif
