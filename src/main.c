#include <stdio.h>
#include <stdlib.h>
#include "../include/instrument.h"
#include "../include/phrase.h"
#include "../include/frame.h"

int main(int argc, char *argv[])
{
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
	msf_phrase *tphrases[8];// = malloc(sizeof(*msf_phrase) * 8);

	for (int i = 0; i < 8; i++)
	{
		tphrases[i] = msf_create_phrase(64);
		printf("Created phrase %d at 0x%d\n",(i+1),(unsigned int)tphrases[i]);
	}
	msf_frame *frame = msf_create_frame(8);
	printf("Destroying the frame at 0x%d.\n",(unsigned int)frame);
	msf_destroy_frame(frame);
	for (int i = 0; i < 8; i++)
	{
		printf("Destroying phrase at 0x%d.\n",(unsigned int)tphrases[i]);
		msf_destroy_phrase(tphrases[i]);
	}
	printf("\n\nAll done.\n\n");
	return 0;
}
