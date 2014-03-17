/*

MSF Player
Michael Moffitt 2014
-----------------------------------------------------------------------------
This is the "player" struct responsible for playing an actual song and is the 
bulk of where the action is. Organization of the other structs is pretty flat
so it should be relatively managable. 

This will need to be linked against:
pthreads
lao
lm
lpoly

*/
#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <poly.h> 

#include "../include/frame.h"
#include "../include/instrument.h"
#include "../include/ll.h"
#include "../include/phrase.h"

#define MSF_DEFAULT_SPEED 6
#define MSF_NUM_FRAMES 1024
#define MSF_NUM_CHANNELS 16 // AKA frame width
#define MSF_NUM_PHRASES 1024
#define MSF_PHRASE_LENGTH 64 // .mod much?
#define MSF_NUM_INSTRUMENTS 128
typedef struct msf_player msf_player;
struct msf_player
{
	int init;
	int loopback;
	int track_length;
	int speed; // How many steps are spent on one frame
	int num_frames;
	int num_channels;
	int num_phrases;
	int phrase_length;
	int num_instruments;

	// Variables for channel state
	float *amp_l;
	float *amp_r;
	float *freq;
	int *note;

	int frame_cnt; // Which frame we are on (bigger than phrase step...)
	int phrase_adv;
	int phrase_cnt; // How far into the frame we are (which line of the phrases)

	msf_frame **frames; 
	msf_phrase **phrases;
	msf_instrument **instruments;

	msf_ll **arp; // For stepping through macros on channels - NOT to be allocated ll's
	msf_ll **amp; // Just one pointer per channel
	msf_ll **pitch;
};

extern msf_player player;

// For those who aren't satisfied with my defaults
void msf_init_special(int speed, int num_frames, int num_channels, int num_phrases, int phrase_length, int num_instruments);
void msf_init();
void msf_spill(); // Print where we are in the track
void msf_step(); // Actually runs the music
void msf_shutdown(); // No leaks!

//frames = malloc(sizeof(msf_frame *) * number);

#endif