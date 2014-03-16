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

float msf_get_freq(int note, )
{
	int octave = note >> 8;
	int base = base % 0xFF;
	float base_freq = 16.351; // Default to C
	switch (base)
	{
	case NOTE_C:
		base_freq = 16.351;
		break;
	case NOTE_CS:
		base_freq = 17.324;
		break;
	case NOTE_D:
		base_freq = 18.354;
		break;
	case NOTE_DS:
		base_freq = 19.445;
		break;
	case NOTE_E:
		base_freq = 20.601;
		break;
	case NOTE_F:
		base_freq = 21.827;
		break;
	case NOTE_FS:
		base_freq = 23.124;
		break;
	case NOTE_G:
		base_freq = 24.499;
		break;
	case NOTE_GS:
		base_freq = 25.956;
		break;
	case NOTE_A:
		base_freq = 27.5;
		break;
	case NOTE_AS:
		base_freq = 29.135;
		break;
	case NOTE_B:
		base_freq = 30.868;
		break;
	}
	int mult = 1;
	mult << octave;
	return base_freq * mult;
}
