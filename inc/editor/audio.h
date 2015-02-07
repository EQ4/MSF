#ifndef AUDIO_H
#define AUDIO_H

#include "includes.h"

#define NUM_SAMPLES 2
#define NUM_FRAGMENTS 2
#define SIZE_FRAGMENT 4096
#define AUDIO_RATE 44100
#define AUDIO_DEPTH ALLEGRO_AUDIO_DEPTH_INT16
#define CHANNEL_CONF ALLEGRO_CHANNEL_CONF_2

extern unsigned int num_samples;
extern unsigned int audio_rate;
extern unsigned int num_fragments;
extern unsigned int size_fragment;

extern ALLEGRO_AUDIO_STREAM *stream;
extern msf_driver *driver;

void init_stream(void);

#endif
