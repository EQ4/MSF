#include "editor/includes.h"
ALLEGRO_BITMAP *main_buffer;
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_AUDIO_STREAM *stream;
ALLEGRO_FONT *font;
ALLEGRO_FONT *fontbold;
msf_driver *driver;

int scroll_x;
int scroll_y;
int win_w;
int win_h;

int char_w;
int char_h;

int hilight1;
int hilight2;
