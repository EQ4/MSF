/*

MSF Driver
Michael Moffitt 2014
-----------------------------------------------------------------------------
This is the struct responsible for stepping through an actual piece and is the 
bulk of where the action is. Organization of the other structs is pretty flat
so it should be relatively managable. 

This will need to be linked against:
pthreads
lao
lm
lpoly

*/
#ifndef DRIVER_H
#define DRIVER_H

#include <stdlib.h>
#include <poly.h> 

#include "../include/frame.h"
#include "../include/instrument.h"
#include "../include/ll.h"
#include "../include/phrase.h"

#define MSF_DEFAULT_SPEED 6
#define MSF_NUM_FRAMES 256
#define MSF_NUM_CHANNELS 8 // AKA frame width
#define MSF_NUM_PHRASES 512
#define MSF_PHRASE_LENGTH 64 // .mod much?
#define MSF_NUM_INSTRUMENTS 256
#define MSF_TUNE_DIV 32.00
typedef struct msf_driver msf_driver;
struct msf_driver
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
	msf_ll **duty;
	msf_ll **pitch;
};


// For those who aren't satisfied with my defaults
void msf_init_special(int speed, int num_frames, int num_channels, int num_phrases, int phrase_length, int num_instruments, msf_driver *driver);
void msf_init(msf_driver *driver);
void msf_spill(msf_driver *driver); // Print where we are in the track
void msf_step(msf_driver *driver); // Actually runs the music
void msf_shutdown(msf_driver *driver); // No leaks!

//frames = malloc(sizeof(msf_frame *) * number);

#endif
