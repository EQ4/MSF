#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#define WIN_W 640
#define WIN_H 480

#define CHAR_W 6
#define CHAR_H 9

#define HILIGHT1 4
#define HILIGHT2 16

extern unsigned int char_w;
extern unsigned int char_h;
extern unsigned int win_w;
extern unsigned int win_h;

extern unsigned int hilight1;
extern unsigned int hilight2;

extern int scroll_x;
extern int scroll_y;

void dimensions_init(void);

#endif
