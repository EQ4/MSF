#include "instrument.h"

#include <stdlib.h>

msf_instrument *msf_create_instrument()
{
	//printf("--Making MSF instrument: ");
	msf_instrument *ret = malloc(sizeof(*ret));
	//printf("%d\n",(int)ret);
	//printf("--Setting defaults.\n");
	ret->type = 0;
	ret->left_amp = 1.0;
	ret->right_amp = 1.0;
	ret->wave_num = 0;
	ret->amp_num = 0;
	ret->arp_num = 0;
	ret->pitch_num = 0;
	ret->duty_num = 0;
	//printf("--Making amp_macro at ");
	//ret->amp_macro = msf_create_ll(255);
	//printf("%d\n--Making arp_macro at ",(int)ret->amp_macro);
	//ret->arp_macro = msf_create_ll(0);
	//printf("%d\n--Making pitch_macro at ",(int)ret->arp_macro);
	//ret->pitch_macro = msf_create_ll(0);
	//printf("New instrument at %d.\n",(int)ret);
	//ret->duty_macro = msf_create_ll(128);
	return ret;
}

void msf_destroy_instrument(msf_instrument *ptr)
{
	free(ptr);
}

float msf_get_freq(int note)
{
	int octave = note/12;
	int base = note % 12;
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
	int mult = 1 << octave;
	return base_freq * mult;
}
