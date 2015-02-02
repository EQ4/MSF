#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>

#include "driver.h"
#include "editor/colors.h"

extern ALLEGRO_BITMAP *main_buffer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_AUDIO_STREAM *stream;
extern ALLEGRO_FONT *font;
extern ALLEGRO_FONT *fontbold;
extern msf_driver *driver;

extern int scroll_x;
extern int scroll_y;
extern int win_w;
extern int win_h;

extern int char_w;
extern int char_h;

extern int hilight1;
extern int hilight2;

#endif
