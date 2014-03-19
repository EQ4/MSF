/*

MSF Player
Michael Moffitt 2014
------------------------------------------------------------------------------
This is a simple example "client" to the MSF driver. 




*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/instrument.h"
#include "../include/phrase.h"
#include "../include/frame.h"
#include "../include/driver.h"
int in = 0;
void add(int phr, int val, int inst, msf_driver *driver)
{
	driver->phrases[phr]->note[in] = val;
	driver->phrases[phr]->inst[in] = inst;

	in++;
}

void build_tetris(msf_driver *driver)
{
	// A section harmony
	add(4,45,1,driver);
	add(4,0,0,driver);

	add(4,0,0,driver);
	add(4,0,0,driver);

	add(4,38,1,driver);
	add(4,0,0,driver);

	add(4,42,1,driver);
	add(4,0,0,driver);

	add(4,45,1,driver);
	add(4,0,0,driver);

	add(4,46,1,driver);
	add(4,45,1,driver);
	add(4,43,1,driver);
	add(4,0,0,driver);
	add(4,39,1,driver);
	add(4,0,0,driver);
	add(4,38,1,driver);
	add(4,38,1,driver);
	add(4,34,1,driver);
	add(4,0,0,driver);
	add(4,38,1,driver);
	add(4,0,0,driver);
	add(4,43,1,driver);
	add(4,0,0,driver);
	add(4,46,1,driver);
	add(4,0,0,driver);
	add(4,46,1,driver);
	add(4,46,1,driver);
	add(4,45,1,driver);
	add(4,0,0,driver);
	add(4,43,1,driver);
	add(4,0,0,driver);
	add(4,42,1,driver);
	add(4,42,1,driver);
	add(4,38,1,driver);
	add(4,0,0,driver);
	add(4,42,1,driver);
	add(4,0,0,driver);
	add(4,43,1,driver);
	add(4,0,0,driver);
	add(4,45,1,driver);
	add(4,0,0,driver);
	add(4,0,1,driver);
	add(4,0,0,driver);
	add(4,46,1,driver);
	add(4,0,0,driver);
	add(4,0,1,driver);
	add(4,0,0,driver);
	add(4,43,1,driver);
	add(4,0,0,driver);
	add(4,0,0,driver);
	add(4,0,0,driver);
	add(4,38,1,driver);
	add(4,0,0,driver);
	add(4,0,0,driver);
	add(4,0,0,driver);
	add(4,38,1,driver);
	add(4,0,0,driver);
	add(4,0,0,driver);
	add(4,0,0,driver);
	add(4,38,1,driver);
	add(4,0,0,driver);
	add(4,43,1,driver);
	add(4,0,0,driver);

	in=0;
add(5,-1,1,driver);
	add(5,0,0,driver);

	add(5,39,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,43,1,driver);
	add(5,0,0,driver);

	add(5,46,1,driver);
	add(5,0,0,driver);

	add(5,46,1,driver);
	add(5,46,1,driver);

	add(5,45,1,driver);
	add(5,0,0,driver);

	add(5,43,1,driver);
	add(5,0,0,driver);

	add(5,41,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);


	add(5,38,1,driver);
	add(5,0,0,driver);

	add(5,41,1,driver);
	add(5,0,0,driver);

	add(5,43,1,driver);
	add(5,41,1,driver);

	add(5,39,1,driver);
	add(5,0,0,driver);

	add(5,38,1,driver);
	add(5,0,0,driver);

	add(5,42,1,driver);
	add(5,42,1,driver);

	add(5,38,1,driver);
	add(5,0,0,driver);

	add(5,42,1,driver);
	add(5,0,0,driver);

	add(5,43,1,driver);
	add(5,0,0,driver);

	add(5,45,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,46,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,43,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,38,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,38,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,0,1,driver);
	add(5,0,0,driver);

	add(5,-1,1,driver);
	add(5,0,0,driver);


	// A-2 harmony

	// A section lead

	in = 0;
	add(2,50,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,45,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);

	add(2,48,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);
	
	add(2,45,1,driver);
	add(2,0,0,driver);

	add(2,43,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,43,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);

	add(2,50,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,48,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);

	add(2,45,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,45,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);

	add(2,48,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,50,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,43,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,43,1,driver);
	add(2,0,0,driver);

	add(2,0,1,driver);
	add(2,0,0,driver);

	add(2,45,1,driver);
	add(2,0,0,driver);

	add(2,46,1,driver);
	add(2,0,0,driver);

	in = 0;
	add(3,-1,1,driver);
	add(3,0,0,driver);

	add(3,48,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,51,1,driver);
	add(3,0,0,driver);

	add(3,55,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,53,1,driver);
	add(3,0,0,driver);

	add(3,51,1,driver);
	add(3,0,0,driver);

	add(3,50,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);


	add(3,46,1,driver);
	add(3,0,0,driver);

	add(3,50,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,48,1,driver);
	add(3,0,0,driver);

	add(3,46,1,driver);
	add(3,0,0,driver);

	add(3,45,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,45,1,driver);
	add(3,0,0,driver);

	add(3,46,1,driver);
	add(3,0,0,driver);

	add(3,48,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,50,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,46,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,43,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,43,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,0,1,driver);
	add(3,0,0,driver);

	add(3,-1,1,driver);
	add(3,0,0,driver);

	// A bassline // 43 = 
	in = 0;
	add(6,38-24,2,driver);
	add(6,0,0,driver);
	add(6,38-12,2,driver);
	add(6,0,0,driver);
	add(6,38-24,2,driver);
	add(6,0,0,driver);
	add(6,38-12,2,driver);
	add(6,0,0,driver);
	add(6,38-24,2,driver);
	add(6,0,0,driver);
	add(6,38-12,2,driver);
	add(6,0,0,driver);
	add(6,38-24,2,driver);
	add(6,0,0,driver);
	add(6,38-12,2,driver);
	add(6,0,0,driver);


	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);
	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);
	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);
	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);

	add(6,42-24,2,driver);
	add(6,0,0,driver);
	add(6,42-12,2,driver);
	add(6,0,0,driver);
	add(6,42-24,2,driver);
	add(6,0,0,driver);
	add(6,42-12,2,driver);
	add(6,0,0,driver);

	add(6,38-24,2,driver);
	add(6,0,0,driver);
	add(6,38-12,2,driver);
	add(6,0,0,driver);
	add(6,38-24,2,driver);
	add(6,0,0,driver);
	add(6,38-12,2,driver);
	add(6,0,0,driver);

	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);
	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);
	add(6,43-24,2,driver);
	add(6,0,0,driver);
	add(6,43-12,2,driver);
	add(6,0,0,driver);
	add(6,45-12,2,driver);
	add(6,0,0,driver);
	add(6,46-12,2,driver);
	add(6,0,0,driver);

	// A-2 bassline
	in=0;

	add(7,48-12,2,driver);
	add(7,0,0,driver);

	add(7,48-24,2,driver);
	add(7,0,0,driver);

	add(7,-1,0,driver);
	add(7,-1,0,driver);

	add(7,48-24,2,driver);
	add(7,0,0,driver);

	add(7,-1,0,driver);
	add(7,-1,0,driver);

	add(7,48-24,2,driver);
	add(7,0,0,driver);

	add(7,55-24,2,driver);
	add(7,0,0,driver);

	add(7,48-24,2,driver);
	add(7,0,0,driver);

	add(7,46-24,2,driver);
	add(7,0,0,driver);

	add(7,46-12,2,driver);
	add(7,0,0,driver);

	add(7,-1,2,driver);
	add(7,0,0,driver);

	add(7,46-12,2,driver);
	add(7,0,0,driver);

	add(7,46-24,2,driver);
	add(7,0,0,driver);

	add(7,41-24,2,driver);
	add(7,0,0,driver);

	add(7,43-24,2,driver);
	add(7,0,0,driver);

	add(7,46-24,2,driver);
	add(7,0,0,driver);

	add(7,45-24,2,driver);
	add(7,0,0,driver);

	add(7,45-12,2,driver);
	add(7,0,0,driver);

	add(7,45-24,2,driver);
	add(7,0,0,driver);

	add(7,45-12,2,driver);
	add(7,0,0,driver);

	add(7,38-24,2,driver);
	add(7,0,0,driver);

	add(7,38-12,2,driver);
	add(7,0,0,driver);

	add(7,42-24,2,driver);
	add(7,0,0,driver);

	add(7,42-12,2,driver);
	add(7,0,0,driver);

	add(7,43-12,2,driver);
	add(7,0,0,driver);

	add(7,38-12,2,driver);
	add(7,0,0,driver);

	add(7,34-12,2,driver);
	add(7,0,0,driver);

	add(7,38-12,2,driver);
	add(7,0,0,driver);

	add(7,43-24,2,driver);
	add(7,0,0,driver);
	add(7,0,0,driver);
	add(7,0,0,driver);
	add(7,0,0,driver);
	add(7,0,0,driver);
	add(7,-1,0,driver);
	add(7,0,0,driver);

	// Drums
	in = 0;
	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,100,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,100,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,0,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);

	add(8,100,3,driver);
	add(8,0,3,driver);








}

int main(int argc, char *argv[])
{
	msf_driver driver;
	printf("MSF init sequence starting.\n");
	msf_init(&driver);
	build_tetris(&driver);	
	int idx = 0;

	printf("Setting phrases.\n");
	driver.frames[0]->phrase[0] = 2;
	driver.frames[0]->phrase[1] = 4;
	driver.frames[1]->phrase[0] = 3;
	driver.frames[1]->phrase[1] = 5;
	driver.frames[0]->phrase[2] = 6;
	driver.frames[1]->phrase[2] = 7;
	
	// Drums
	driver.frames[0]->phrase[3] = 8;
	driver.frames[1]->phrase[3] = 8;
	driver.loopback = 0;
	driver.track_length = 2;

	msf_instrument *inst3 = driver.instruments[3];
	inst3->type = WAVE_NOISE;
	inst3->duty_macro->value = 240;
	inst3->arp_macro->value = -19;

	msf_instrument *inst2 = driver.instruments[2];
	inst2->type = WAVE_SQUARE;
	
	// Lead instrument
	msf_instrument *inst = driver.instruments[1];
	inst->type = WAVE_SQUARE;

	printf("Building instrument macro data\n");
	msf_ll *base_amp = inst->amp_macro;
	base_amp->value = 0;
	for (int i = 0; i < 18; i++)
	{
		msf_add_ll(base_amp,255-(11*i));
		//msf_add_ll(inst->amp_macro,0);
		msf_add_ll(inst3->amp_macro,255-(19*i));
		msf_add_ll(inst2->amp_macro,255-(9*i));
		//msf_add_ll(inst2->amp_macro,0);
	}

	// Bassline
	inst2->duty_macro->value = 128;
	inst2->arp_macro->value = 12;
	// Lead
	inst->duty_macro->value = 128;
	inst->arp_macro->value = 12;
	



/*	msf_ll *base_arp = inst->arp_macro;
	base_arp->value = 7;
	msf_add_ll(base_arp,8);
	msf_add_ll(base_arp,9);
	msf_add_ll(base_arp,10);
//	msf_add_ll(base_arp,12);
//	msf_add_ll(base_arp,12);
	msf_loop_ll(base_arp,base_arp);*/


/*msf_ll *pitch_m = inst->pitch_macro;
	pitch_m->value = 0;
	msf_add_ll(pitch_m,0);
	msf_add_ll(pitch_m,0);
	msf_add_ll(pitch_m,0);
	msf_add_ll(pitch_m,0);
	msf_add_ll(pitch_m,0);
	msf_add_ll(pitch_m,0);
	msf_add_ll(pitch_m,9*1);
	msf_add_ll(pitch_m,9*2);
	msf_add_ll(pitch_m,9*3);
	msf_add_ll(pitch_m,9*2);
	msf_add_ll(pitch_m,9*1);
	msf_add_ll(pitch_m,9*0);
	msf_add_ll(pitch_m,9*-1);
	msf_add_ll(pitch_m,9*-2);
	msf_add_ll(pitch_m,9*-3);
	msf_add_ll(pitch_m,9*-2);
	msf_add_ll(pitch_m,9*-1);
	msf_loop_ll(pitch_m,pitch_m->next->next->next->next->next->next->next);*/

	driver.speed = 6;
/*	msf_ll *base_duty = inst->duty_macro;
	base_duty->value = 128;
	for (int i = 0; i < 0; i++)
	{
		msf_add_ll(base_duty,20 + (6*i));
	}
*/


//	inst->arp_macro->next = base_arp;
	for (int i = 0; i < 6*64*4; i++)
	{
		usleep(16000);
		
		msf_step(&driver);
		//msf_spill();
	}
	printf("Killing driver now.\n");
	msf_shutdown(&driver);
	return 0;
}
