/*

MSF Instrument
Michael Moffitt 2014
-----------------------------------------------------------------------
More or less a collection of parameters to be sent to a generator when this 
instrument is used on a channel. 

Notes are stored like this:

(base note) + (256 * octave)

This is so that octaves come from (note value) / 256 = octave.
This can also be done as (note value) >> 8.

*/

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#define NOTE_C  0
#define NOTE_CS 1
#define NOTE_D  2
#define NOTE_DS 3
#define NOTE_E  4
#define NOTE_F  5
#define NOTE_FS 6
#define NOTE_G  7
#define NOTE_GS 8
#define NOTE_A  9
#define NOTE_AS 10
#define NOTE_B  11

#include <stdio.h>
#include <stdlib.h>
#include "../include/ll.h"

typedef struct
{
	// Which type of wave the generator should use
	int type; 
	int *wave_ptr; // Pointer to sample data
	int wave_depth; // Depth of the sample
	int wave_mult; // 44100hz / sample rate (must be 1 for 44.1k, 2 for 22k)
	int wave_len; // Number of samples in the wave
	msf_ll *amp_macro; // Absolute amplitude linked list macro
	msf_ll *arp_macro; // Absolute half-step linked list macro
	msf_ll *pitch_macro; // Relative pitch linked list macro
	
} msf_instrument;

msf_instrument *msf_create_instrument();
void msf_destroy_instrument(msf_instrument *ptr);

float msf_get_freq(msf_instrument *ptr);
#endif
