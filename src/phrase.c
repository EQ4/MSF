#include "../include/phrase.h"

msf_phrase *msf_create_phrase(int len)
{
	// Build the phrase structure itself
	msf_phrase *ret = malloc(sizeof(*ret));

	// Create and clear arrays for its properties
	ret->note = calloc(len,sizeof(int));
	ret->inst = malloc(len * sizeof(int));
	ret->vol = malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
	{
		ret->inst[i] = -1; // Default to no instrument
		ret->vol[i] = -1; // Default to no volume modification
	}
	ret->cmd = calloc(len,sizeof(int));
	ret->arg = calloc(len,sizeof(int));

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
