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
	add(4,46,1);
	add(4,0,0);
	add(4,46,1);
	add(4,46,1);
	add(4,45,1);
	add(4,0,0);
	add(4,43,1);
	add(4,0,0);
	add(4,42,1);
	add(4,42,1);
	add(4,38,1);
	add(4,0,0);
	add(4,42,1);
	add(4,0,0);
	add(4,43,1);
	add(4,0,0);
	add(4,45,1);
	add(4,0,0);
	add(4,0,1);
	add(4,0,0);
	add(4,46,1);
	add(4,0,0);
	add(4,0,1);
	add(4,0,0);
	add(4,43,1);
	add(4,0,0);
	add(4,0,0);
	add(4,0,0);
	add(4,38,1);
	add(4,0,0);
	add(4,0,0);
	add(4,0,0);
	add(4,38,1);
	add(4,0,0);
	add(4,0,0);
	add(4,0,0);
	add(4,38,1);
	add(4,0,0);
	player.frames[0]->tune[3] = 16;
	add(4,43,1);
	add(4,0,0);

	in=0;
add(5,-1,1);
	add(5,0,0);

	add(5,39,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,43,1);
	add(5,0,0);

	add(5,46,1);
	add(5,0,0);

	add(5,46,1);
	add(5,46,1);

	add(5,45,1);
	add(5,0,0);

	add(5,43,1);
	add(5,0,0);

	add(5,41,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);


	add(5,38,1);
	add(5,0,0);

	add(5,41,1);
	add(5,0,0);

	add(5,43,1);
	add(5,41,1);

	add(5,39,1);
	add(5,0,0);

	add(5,38,1);
	add(5,0,0);

	add(5,42,1);
	add(5,42,1);

	add(5,38,1);
	add(5,0,0);

	add(5,42,1);
	add(5,0,0);

	add(5,43,1);
	add(5,0,0);

	add(5,45,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,46,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,43,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,38,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,38,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,0,1);
	add(5,0,0);

	add(5,-1,1);
	add(5,0,0);


	// A-2 harmony

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
	player.frames[0]->tune[3] = 16;

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
	player.frames[0]->tune[3] = 16;

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

	// A bassline // 43 = 
	in = 0;
	add(6,38-24,2);
	add(6,0,0);
	add(6,38-12,2);
	add(6,0,0);
	add(6,38-24,2);
	add(6,0,0);
	add(6,38-12,2);
	add(6,0,0);
	add(6,38-24,2);
	add(6,0,0);
	add(6,38-12,2);
	add(6,0,0);
	add(6,38-24,2);
	add(6,0,0);
	add(6,38-12,2);
	add(6,0,0);


	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);
	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);
	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);
	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);

	add(6,42-24,2);
	add(6,0,0);
	add(6,42-12,2);
	add(6,0,0);
	add(6,42-24,2);
	add(6,0,0);
	add(6,42-12,2);
	add(6,0,0);

	add(6,38-24,2);
	add(6,0,0);
	add(6,38-12,2);
	add(6,0,0);
	add(6,38-24,2);
	add(6,0,0);
	add(6,38-12,2);
	add(6,0,0);

	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);
	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);
	add(6,43-24,2);
	add(6,0,0);
	add(6,43-12,2);
	add(6,0,0);
	add(6,45-12,2);
	add(6,0,0);
	add(6,46-12,2);
	add(6,0,0);

	// A-2 bassline
	in=0;

	add(7,48-12,2);
	add(7,0,0);

	add(7,48-24,2);
	add(7,0,0);

	add(7,-1,0);
	add(7,-1,0);

	add(7,48-24,2);
	add(7,0,0);

	add(7,-1,0);
	add(7,-1,0);

	add(7,48-24,2);
	add(7,0,0);

	add(7,55-24,2);
	add(7,0,0);

	add(7,48-24,2);
	add(7,0,0);

	add(7,46-24,2);
	add(7,0,0);

	add(7,46-12,2);
	add(7,0,0);

	add(7,-1,2);
	add(7,0,0);

	add(7,46-12,2);
	add(7,0,0);

	add(7,46-24,2);
	add(7,0,0);

	add(7,41-24,2);
	add(7,0,0);

	add(7,43-24,2);
	add(7,0,0);

	add(7,46-24,2);
	add(7,0,0);

	add(7,45-24,2);
	add(7,0,0);

	add(7,45-12,2);
	add(7,0,0);

	add(7,45-24,2);
	add(7,0,0);

	add(7,45-12,2);
	add(7,0,0);

	add(7,38-24,2);
	add(7,0,0);

	add(7,38-12,2);
	add(7,0,0);

	add(7,42-24,2);
	add(7,0,0);

	add(7,42-12,2);
	add(7,0,0);

	add(7,43-12,2);
	add(7,0,0);

	add(7,38-12,2);
	add(7,0,0);

	add(7,34-12,2);
	add(7,0,0);

	add(7,38-12,2);
	add(7,0,0);

	add(7,43-24,2);
	add(7,0,0);
	add(7,0,0);
	add(7,0,0);
	add(7,0,0);
	add(7,0,0);
	add(7,-1,0);
	add(7,0,0);
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
	player.frames[1]->phrase[1] = 5;
	player.frames[0]->phrase[2] = 6;
	player.frames[1]->phrase[2] = 7;
	player.loopback = 0;
	player.track_length = 2;


	msf_instrument *inst2 = player.instruments[2];
	inst2->type = WAVE_SQUARE;
	
	msf_instrument *inst = player.instruments[1];
	inst->type = WAVE_SAW;

	printf("Building instrument macro data\n");
	msf_ll *base_amp = inst->amp_macro;
	for (int i = 0; i < 18; i++)
	{
		msf_add_ll(base_amp,255-(12*i));
		msf_add_ll(inst2->amp_macro,255-(9*i));
	}
	
	inst2->arp_macro->value = 7;
	inst->arp_macro->value = 7;

/*	msf_ll *base_arp = inst2->arp_macro;
	base_arp->value = 12;
	msf_add_ll(base_arp,12);
	msf_add_ll(base_arp,0);
	msf_add_ll(base_arp,12);
	msf_add_ll(base_arp,12);
	msf_loop_ll(base_arp,base_arp);
*/
	msf_ll *base_duty = inst2->duty_macro;
	base_duty->value = 128;
	for (int i = 0; i < 0; i++)
	{
		msf_add_ll(base_duty,60 + (3*i));
	}
//	inst->arp_macro->next = base_arp;
	for (int i = 0; i < 2560; i++)
	{
		usleep(16000);
		msf_step();
		//msf_spill();
	}
	printf("Killing player now.\n");
	msf_shutdown();
	return 0;
}
