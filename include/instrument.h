/*

MSF Instrument
Michael Moffitt 2014
-----------------------------------------------------------------------
More or less a collection of parameters to be sent to a generator when this 
instrument is used on a channel. 

*/


#ifndef INSTRUMENT_H
#define INSTRUMENT_H

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
#endif
