/*

MSF Song Loader
Michael Moffitt 2014
-----------------------------------------------------------------------------

First it builds a MSF driver instance with the following specifications:
	256 phrases
	256 frames
	256 instruments

	8 channels
*/
#include "../include/driver.h"
#include "../include/instrument.h"

int msf_load_song(msf_driver *driver, const char *file);
