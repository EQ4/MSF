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

#define WAVE_SQUARE 0
#define WAVE_SINE 1
#define WAVE_SAW 2
#define WAVE_TRIANGLE 3
#define WAVE_NOISE 4
#define WAVE_ONESAMPLE 5
#define WAVE_LOOPSAMPLE 6
#include "ll.h"

typedef struct
{
	// Which type of wave the generator should use
	int type;
	float left_amp; // 0.0 - 1.0 left amplitude multiplier
	float right_amp; // 0.0 - 1.0 right amplitude multiplier

	// Indeces for macros and wave num
	unsigned int wave_num;
	unsigned int amp_num;
	unsigned int arp_num;
	unsigned int pitch_num;
	unsigned int duty_num;
//	msf_ll *amp_macro; // Absolute amplitude linked list macro
//	msf_ll *arp_macro; // Absolute half-step linked list macro
//	msf_ll *pitch_macro; // Relative pitch linked list macro
//	msf_ll *duty_macro;
	
} msf_instrument;

msf_instrument *msf_create_instrument();
void msf_destroy_instrument(msf_instrument *ptr);
float msf_get_freq(int note);
#endif
