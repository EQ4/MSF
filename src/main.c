#include <stdio.h>
#include <stdlib.h>
#include "../include/instrument.h"

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
	printf("Done.\n\n");
	return 0;
}
