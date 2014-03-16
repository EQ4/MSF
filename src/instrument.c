#include <stdio.h>
#include "../include/instrument.h"
#include "../include/ll.h"

msf_instrument *msf_create_instrument()
{
	printf("--Making MSF instrument: ");
	msf_instrument *ret = malloc(sizeof(*ret));
	printf("%d\n",(int)ret);
	printf("--Setting defaults.\n");
	ret->type = 0;
	ret->wave_ptr = 0;
	ret->wave_depth = 16; // Default to a 16-bit wave
	ret->wave_mult = 1; // Default to 44.1khz sample rate
	ret->wave_len = 2; // Defaul to two samples (1 is useless...)

	printf("--Making amp_macro at ");
	ret->amp_macro = malloc(sizeof(*(ret->amp_macro)));
	printf("%d\n--Making arp_macro at ",(int)ret->amp_macro);
	ret->arp_macro = malloc(sizeof(*(ret->arp_macro)));
	printf("%d\n--Making pitch_macro at ",(int)ret->arp_macro);
	ret->pitch_macro = malloc(sizeof(*(ret->pitch_macro)));
	printf("%d\n--Done making instrument. Returning.\n",(int)ret->pitch_macro);
	return ret;
}

void msf_destroy_instrument(msf_instrument *ptr)
{
	printf("\nDestroying amp_macro...\n");
	msf_destroy_ll(ptr->amp_macro);
	printf("\nDestroying arp_macro...\n");
	msf_destroy_ll(ptr->arp_macro);
	printf("\nDestroying pitch_macro...\n");
	msf_destroy_ll(ptr->pitch_macro);
	printf("\nFreeing instrument pointer...\n");
	free(ptr);
}
