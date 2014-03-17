#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/instrument.h"
#include "../include/phrase.h"
#include "../include/frame.h"
#include "../include/player.h"

int main(int argc, char *argv[])
{
/*
	printf("Building test instrument\n\n");
	msf_instrument *test = msf_create_instrument();
	printf("Messing with test->type\n\n");
	test->type = 18;
	printf("The type of wave is %d.\n\nAdding a little something to test's arp_macro.\n\n",test->type);
	test->arp_macro->next = malloc(sizeof(msf_ll));
	test->arp_macro->next->value = 6;
	msf_destroy_instrument(test);
	printf("Done.\n\nMessing with some phrases...\n");

	// Dynamic array containing n pointers to msf_phrase structs
	#define NUM_TEST_PHRASES 24
	msf_phrase **tphrases = malloc(sizeof(msf_phrase *) * NUM_TEST_PHRASES);

	for (int i = 0; i < NUM_TEST_PHRASES; i++)
	{
		tphrases[i] = msf_create_phrase(64);
		printf("Created phrase %d at 0x%d\n",(i+1),(unsigned int)tphrases[i]);
	}
	msf_frame *frame = msf_create_frame(16);
	printf("Destroying the frame at 0x%d.\n",(unsigned int)frame);
	msf_destroy_frame(frame);
	for (int i = 0; i < NUM_TEST_PHRASES; i++)
	{
		printf("Destroying phrase at 0x%d.\n",(unsigned int)tphrases[i]);
		msf_destroy_phrase(tphrases[i]);
	}
	free(tphrases);
	printf("\n\nAll done.\n\n");
*/

	printf("MSF init sequence starting.\n");
	msf_init();
	printf("Playing.\n");
	
	
	player.phrases[2]->note[1] = 48-5;
	player.phrases[2]->note[2] = 52-5;
	player.phrases[2]->note[3] = 48-5;
	player.phrases[2]->note[4] = 53-5;
	player.phrases[2]->note[5] = 48-5;
	player.phrases[2]->note[6] = 52-5;
	player.phrases[2]->note[7] = 48-5;
	player.phrases[2]->inst[1] = 1;
	player.phrases[2]->inst[2] = 1;
	player.phrases[2]->inst[3] = 1;
	player.phrases[2]->inst[4] = 1;
	player.phrases[2]->inst[5] = 1;
	player.phrases[2]->inst[6] = 1;
	player.phrases[2]->inst[7] = 1;
	player.phrases[2]->note[8] = -1;
	
	
	
	
	player.phrases[1]->note[1] = 48;
	player.phrases[1]->note[2] = 52;
	player.phrases[1]->note[3] = 48;
	player.phrases[1]->note[4] = 53;
	player.phrases[1]->note[5] = 48;
	player.phrases[1]->note[6] = 52;
	player.phrases[1]->note[7] = 48;
	player.phrases[1]->inst[1] = 1;
	player.phrases[1]->inst[2] = 1;
	player.phrases[1]->inst[3] = 1;
	player.phrases[1]->inst[4] = 1;
	player.phrases[1]->inst[5] = 1;
	player.phrases[1]->inst[6] = 1;
	player.phrases[1]->inst[7] = 1;
	player.phrases[1]->note[9] = -1;
	player.frames[0]->phrase[0] = 1;
	player.frames[0]->phrase[1] = 2;

	player.instruments[1]->duty = 0.40;
	for (int i = 0; i < 54; i++)
	{
		usleep(20000);
		msf_step();
		msf_spill();
	}
	printf("Killing player now.\n");
	msf_shutdown();
	return 0;
}
