#include "../include/frame.h"

msf_frame *msf_create_frame(int num)
{
	// Make frame
	msf_frame *ret = malloc(sizeof(*ret));

	// Set length
	ret->num_channels = num;

	// Make arrays
	ret->patterns = calloc(sizeof(int) * num);
	ret->transpose = calloc(sizeof(int) * num);
	ret->tune = calloc(sizeof(int) * num);
}

void msf_destroy_frame(msf_frame *ptr)
{
	free(ptr->patterns);
	free(ptr->transpose);
	free(ptr->tune);
	free(ptr);
}
