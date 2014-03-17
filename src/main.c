#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/instrument.h"
#include "../include/phrase.h"
#include "../include/frame.h"
#include "../include/player.h"
int in = 0;
void add(int phr, int val, int inst)
{
	player.phrases[phr]->note[in] = val;
	player.phrases[phr]->inst[in] = inst;

	in++;
}

void build_tetris()
{
	// A section harmony
	add(4,45,1);
	add(4,0,0);

	add(4,0,0);
	add(4,0,0);

	add(4,38,1);
	add(4,0,0);

	add(4,42,1);
	add(4,0,0);

	add(4,45,1);
	add(4,0,0);

	add(4,46,1);
	add(4,45,1);
	add(4,43,1);
	add(4,0,0);
	add(4,39,1);
	add(4,0,0);
	add(4,38,1);
	add(4,38,1);
	add(4,34,1);
	add(4,0,0);
	add(4,38,1);
	add(4,0,0);
	add(4,43,1);
	add(4,0,0);
	add(4,43,1);
	add(4,43,1);
	add(4,42,1);
	add(4,0,0);
	add(4,40,1);
	// A section lead

	in = 0;
	add(2,50,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,45,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);

	add(2,48,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);
	
	add(2,45,1);
	add(2,0,0);

	add(2,43,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,43,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);

	add(2,50,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,48,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);

	add(2,45,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,45,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);

	add(2,48,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,50,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,43,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,43,1);
	add(2,0,0);

	add(2,0,1);
	add(2,0,0);

	add(2,45,1);
	add(2,0,0);

	add(2,46,1);
	add(2,0,0);

	in = 0;
	add(3,-1,1);
	add(3,0,0);

	add(3,48,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,51,1);
	add(3,0,0);

	add(3,55,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,53,1);
	add(3,0,0);

	add(3,51,1);
	add(3,0,0);

	add(3,50,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);


	add(3,46,1);
	add(3,0,0);

	add(3,50,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,48,1);
	add(3,0,0);

	add(3,46,1);
	add(3,0,0);

	add(3,45,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,45,1);
	add(3,0,0);

	add(3,46,1);
	add(3,0,0);

	add(3,48,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,50,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,46,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,43,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,43,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,0,1);
	add(3,0,0);

	add(3,-1,1);
	add(3,0,0);


}

int main(int argc, char *argv[])
{


	printf("MSF init sequence starting.\n");
	msf_init();
	build_tetris();	
	int idx = 0;

	printf("Setting phrases.\n");
	player.frames[0]->phrase[0] = 2;
	player.frames[0]->phrase[1] = 4;
	player.frames[1]->phrase[0] = 3;
	player.loopback = 0;
	player.track_length = 2;


	msf_instrument *inst = player.instruments[1];
	inst->type = WAVE_SQUARE;
	inst->right_amp = 1.0;

	printf("Building instrument macro data\n");
	msf_ll *base_amp = inst->amp_macro;
	msf_add_ll(base_amp,255-16);
	msf_add_ll(base_amp,255-32);
	msf_add_ll(base_amp,255-48);
	msf_add_ll(base_amp,255-64);
	msf_add_ll(base_amp,255-80);
	msf_add_ll(base_amp,255-96);
	msf_add_ll(base_amp,255-128);

	msf_ll *base_arp = inst->arp_macro;
	base_arp->value = 12;
//	msf_add_ll(base_arp,12);
/*	msf_add_ll(base_arp,0);
	msf_add_ll(base_arp,12);
	msf_add_ll(base_arp,12);
	msf_loop_ll(base_arp,base_arp);
*/
	msf_ll *base_duty = inst->duty_macro;
	for (int i = 0; i < 0; i++)
	{
		msf_add_ll(base_duty,60 + (6*i));
	}
//	inst->arp_macro->next = base_arp;
	for (int i = 0; i < 2560; i++)
	{
		usleep(15000);
		msf_step();
		//msf_spill();
	}
	printf("Killing player now.\n");
	msf_shutdown();
	return 0;
}
