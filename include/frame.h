/*

MSF Frame Structure
Michael Moffitt 2014
--------------------------------------------------------------------------
A frame is a single... well, "frame" of a song. Frames are laid out to 
arrange a song. The frame keeps track of which patterns should be played
on each channel for that part of the song.

All frames are is basically a set of two int arrays: pattern number, tune,
transpose amount (in half steps). This lets a pattern be re-used with a 
transposition. For example, using -12 or +12 would have a pattern play
the same, but at a shifted octave for a stronger bassline. The tune 
parameter allows a phrase to be de-tuned to give a chorus effect when
used with the same pattern adjacent. 


*/

#ifndef FRAME_H
#define FRAME_H

#include <stdlib.h>

typedef struct msf_frame msf_frame;
struct msf_frame
{
	int num_channels; // "Width" of a frame
	int *phrase; // Pattern[channel]
	int *transpose; // Transposition[channel]
	int *tune; // Detune[channel];
};

msf_frame *msf_create_frame(int num);
void msf_destroy_frame(msf_frame *ptr);

#endif
