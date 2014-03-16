/*

MSF Linked List
Michael Moffitt 2014
------------------------------------------------------------------------
This is precisely what it looks like. It is used primarily for macros in
instruments like arpeggios, volume, etc.

*/

#ifndef LL_H
#define LL_H

typedef struct
{
	int value;
	int *next;
} msf_ll;

void msf_destroy_ll(msf_ll *ptr);
#endif
