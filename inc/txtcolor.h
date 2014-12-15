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

#define COL_NOTE COL_GREEN
#define COL_INST COL_YELLOW
#define COL_DIV COL_WHITE
#define COL_CUT COL_RED
#define COL_NUM COL_BLUE
#define COL_CMD COL_CYAN
#define COL_ARG COL_MAGENTA
#define COL_FRAME COL_WHITE

#define ATTR_NOTE COL_BRIGHT
#define ATTR_INST COL_BRIGHT
#define ATTR_DIV COL_DIM
#define ATTR_CUT COL_BRIGHT
#define ATTR_NUM COL_BRIGHT
#define ATTR_CMD COL_BRIGHT
#define ATTR_ARG COL_BRIGHT
#define ATTR_FRAME COL_BRIGHT

void textcolor(int attr, int fg, int bg);

#endif
