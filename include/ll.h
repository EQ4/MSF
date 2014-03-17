/*

MSF Linked List
Michael Moffitt 2014
------------------------------------------------------------------------
This is precisely what it looks like. It is used primarily for macros in
instruments like arpeggios, volume, etc.

*/

#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>


typedef struct msf_ll msf_ll;

struct msf_ll
{
	int value;
	msf_ll *next;
};

void msf_destroy_ll(msf_ll *ptr);
msf_ll *msf_create_ll(int value);
void msf_add_ll(msf_ll *base, int value); // Tack on a macro entry
void msf_loop_ll(msf_ll *base, msf_ll *point); // set a loop point for a macro
#endif
