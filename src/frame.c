#include "../include/frame.h"

msf_frame *msf_create_frame(int num)
{
	// Make frame
	msf_frame *ret = malloc(sizeof(*ret));

	// Set length
	ret->num_channels = num;

	// Make arrays
	ret->phrase = malloc(num *sizeof(int));
	ret->transpose = malloc(num * sizeof(int));
	ret->tune = malloc(num * sizeof(int));

	for (int i = 0; i < num; i++)
	{
		ret->phrase[i] = 0;
		ret->transpose[i] = 0;
		ret->tune[i] = 0;
	}
	return ret;
}

void msf_destroy_frame(msf_frame *ptr)
{
	free(ptr->phrase);
	free(ptr->transpose);
	free(ptr->tune);
	free(ptr);
}
