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

#include "frame.h"
#include "instrument.h"
#include "ll.h"
#include "phrase.h"

#define MSF_DEFAULT_SPEED 6
#define MSF_NUM_FRAMES 256
#define MSF_NUM_CHANNELS 8 // AKA frame width
#define MSF_NUM_PHRASES 256
#define MSF_PHRASE_LENGTH 64 // .mod much?
#define MSF_NUM_INSTRUMENTS 256
#define MSF_TUNE_DIV 64.00
#define MSF_PITCH_DIV 0.5

#define MSF_LL_CHOICE_DUTY 0
#define MSF_LL_CHOICE_AMP 1
#define MSF_LL_CHOICE_PITCH 2
#define MSF_LL_CHOICE_ARP 3

#define MSF_DELIMITERS " ,_\t"
#define NUM_MACROS 64
typedef struct msf_driver msf_driver;
struct msf_driver
{
	// Driver variables
	int init;
	int num_frames;
	int num_channels;
	int num_phrases;
	int num_instruments;

	int print_notes;

	// Variables for channel state - index of each is which channel
	float *amp_l; // Current Left amplitude
	float *amp_r; // Current Right amplitude
	float *master_l; // Coefficients for above amplitude for track control
	float *master_r;
	float *freq; // Current frequency *offset*
	int *note; // Note value (frequency comes from this)
	
	// Position counters
	int frame_cnt; // Which frame we are on (bigger than phrase step...)
	int phrase_adv; 
	int phrase_cnt; // How far into the frame we are (which line of the phrases)

	int *note_delay; // [n-channels] wide note delay counter
	int *note_cut; // [n-channels] wide note cut counter
	int hop_queue;
	int jump_queue;
	// Track data
	msf_frame **frames; 
	msf_phrase **phrases;
	msf_instrument **instruments;
	int loopback;
	int track_length;
	int speed; // How many steps per frame
	int phrase_length;
	char *name;
	char *author;

	msf_ll **amp_macro;
	msf_ll **arp_macro;
	msf_ll **pitch_macro;
	msf_ll **duty_macro;

	// Instrument macros (not to be allocated), one per channel
	// These store pointers to the currently active macros in use for each channel
	msf_ll **amp;
	msf_ll **arp;
	msf_ll **duty;
	msf_ll **pitch;
};

// For those who aren't satisfied with my defaults
msf_driver *msf_init_special(int speed, int num_frames, int num_channels, 
					  int num_phrases, int phrase_length, int num_instruments);
msf_driver *msf_init(void);
void msf_spill(msf_driver *driver); // Print where we are in the track
int msf_drv_proc(msf_driver *driver);
void msf_drv_inc_ll(msf_driver *driver, int i); // Step through the LLs
void msf_step(msf_driver *driver); // Actually runs the music
void msf_shutdown(msf_driver *driver); // No leaks!

msf_driver *msf_handle_driver_line(char *line);
unsigned int msf_handle_line(msf_driver *driver, char *line);
int *msf_get_line_values(const char *line);
char *msf_get_entry(const char *word, const char *l);
msf_driver *msf_load_file(const char *fname); // Load from MSF file

void msf_trigger_note(msf_driver *driver, int i, msf_instrument *instrument, int note);
void msf_kill_channel(msf_driver *driver, int chan);

#endif
