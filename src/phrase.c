#include "../include/phrase.h"

msf_phrase *msf_create_phrase(int len)
{
	// Build the phrase structure itself
	msf_phrase *ret = malloc(sizeof(*ret));

	// Create and clear arrays for its properties
	ret->note = calloc(len,sizeof(int));
	ret->inst = calloc(len,sizeof(int));
	ret->vol = calloc(len,sizeof(int));
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
