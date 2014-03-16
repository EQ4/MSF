#include "../include/frame.h"

msf_frame *msf_create_frame(int num)
{
	// Make frame
	msf_frame *ret = malloc(sizeof(*ret));

	// Set length
	ret->num_channels = num;

	// Make arrays
	ret->pattern = calloc(num,sizeof(int));
	ret->transpose = calloc(num,sizeof(int));
	ret->tune = calloc(num,sizeof(int));

	return ret;
}

void msf_destroy_frame(msf_frame *ptr)
{
	free(ptr->pattern);
	free(ptr->transpose);
	free(ptr->tune);
	free(ptr);
}
