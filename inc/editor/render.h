#ifndef RENDER_H
#define RENDER_H

#define MSF_RENDER_TXTLEN 12

#define MODE_WINDOW 0
#define MODE_FULL 1

#include "editor/includes.h"

extern ALLEGRO_BITMAP *main_buffer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_FONT *fontbold;

extern unsigned int window_mode;

void init_render(void);

void render_hilights(int j, int bx, int by);
void render_notetext(int j, int bx, int by, char *str, msf_phrase *phrase);
void render_phrase(int x, int y, char *str, msf_phrase *phrase);

void update_display(void);

#endif
