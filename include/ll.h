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

#endif
