#include "../include/phrase.h"
#include <stdlib.h>

msf_phrase *msf_create_phrase(int len)
{
	// Build the phrase structure itself
	msf_phrase *ret = malloc(sizeof(*ret));

	// Create and clear arrays for its properties
	ret->note = malloc(len *sizeof(int));
	ret->inst = malloc(len * sizeof(int));
	ret->vol = malloc(len * sizeof(int));
	ret->cmd = malloc(len * sizeof(int));
	ret->arg = malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
	{
		ret->inst[i] = -1; // Default to no instrument
		ret->vol[i] = -1; // Default to no volume modification
		ret->note[i] = 0;
		ret->cmd[i] = 0;
		ret->arg[i] = 0;
	}
	return ret;
}

void msf_destroy_phrase(msf_phrase *ptr)
{
	// Free the arrays inside the phrase
	free(ptr->note);
	free(ptr->inst);
	free(ptr->vol);
	free(ptr->cmd);
	free(ptr->arg);

	// Free the phrase itself
	free(ptr);
}
