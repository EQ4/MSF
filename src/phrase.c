#include "../include/phrase.h"

msf_phrase *msf_create_phrase(int len)
{
	// Build the phrase structure itself
	msf_phrase *ret = malloc(sizeof(*ret));

	// Create and clear arrays for its properties
	ret->note = calloc(sizeof(int) * len);
	ret->inst = calloc(sizeof(int) * len);
	ret->vol = calloc(sizeof(int) * len);
	ret->cmd = calloc(sizeof(int) * len);
	ret->arg = calloc(sizeof(int) * len);

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
