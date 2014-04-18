/*

MSF Phrase Structure
Michael Moffitt 2014
--------------------------------------------------------------------------
Stores a single line of note commands for a channel. Must be created with
a passed length value for how many steps there are. This should be kept
global within a song.

*/

#ifndef PHRASE_H
#define PHRASE_H
typedef struct msf_phrase msf_phrase;

struct msf_phrase
{
	int length; // Number of steps
	int *note; // Note[step]
	int *inst; // Instrument[step] This is an instrument number, not a pointer.
	int *vol; // Volume[step] (scale from 0-255)
	int *cmd; // Command[step]
	int *arg; // Argument[step] for the command
};

msf_phrase *msf_create_phrase(int len);
void msf_destroy_phrase(msf_phrase *ptr);

#endif
