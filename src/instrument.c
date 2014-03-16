#include "src/include/instrument.h"

msf_instrument *msf_create_instrument()
{
	msf_instrument *ret = malloc(sizeof(ret));
	ret->type = 0;
	ret->wave_ptr = 0;
	ret->wave_depth = 16; // Default to a 16-bit wave
	ret->wave_mult = 1; // Default to 44.1khz sample rate
	ret->wave_len = 2; // Defaul to two samples (1 is useless...)
	ret->amp_macro = malloc(sizeof(*(ret->amp_macro)));
	ret->arp_macro = malloc(sizeof(*(ret->arp_macro)));
	ret->pitch_macro = malloc(sizeof(*(ret->pitch_macro)));
	return ret;
}

void msf_destroy_instrument(msf_instrument *ptr)
{
	free(ptr->amp_macro);
}
