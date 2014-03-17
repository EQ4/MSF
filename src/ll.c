#include "../include/ll.h"

void msf_destroy_ll(msf_ll *ptr)
{
	msf_ll *prev;
	msf_ll *cur;
	prev = NULL;
	cur = ptr;

	msf_ll *addresses; // Addresses we have already seen for end detection
	addresses = malloc(sizeof(*addresses));
	addresses->value = -1;
	addresses->next = NULL;

	msf_ll *addresses_base = addresses;

	int finished = 0;
	while (finished == 0)
	{
		// Check for the current address in our existing list
		msf_ll *next_check = addresses_base;
		printf("--Current node's next address is 0x%d.\n",(int)cur->next);
		while (next_check->next != NULL) // Go through the LL of seen addresses
		{
			printf("--Checking %d against %d...\n",(int)next_check->value,(int)cur->next);
			if (next_check->value == (int)cur->next) // If we have seen the next node...
			{
				printf("--Match found! Finished destroying list.\n");
				finished = 1; // ...we are done.
			}
			else
			{
				next_check = next_check->next;
			}
		}
		if (finished == 0)
		{
		    prev = cur; // Record our current node
			if (cur->next == NULL)
			{
				printf("--Finished with this list.\n");
				finished = 1;
			}
			else
			{
				printf("--Hopping to 0x%d\n",(int)cur->next);
				cur = cur->next; // Hop to next node
			}
			addresses->value = (int)prev; // Record the address we visited
			printf("--Marked address 0x%d as visited.\n",(int)prev);
			addresses->next = malloc(sizeof(*addresses)); // Build the next address node
			addresses = addresses->next; // Go to it
			addresses->next = NULL;
			addresses->value = -1;
			printf("--Freeing msf_ll node at 0x%d\n",(int)prev);
			free(prev); // Free the previous
		}
	}

	// Now we must free our addresses list
	addresses = addresses_base;
	while (addresses->next != NULL)
	{
		prev = addresses;
		addresses = addresses->next;
		printf("--Freeing address list node at 0x%d\n",(int)prev);
		free(prev);
	}
}

msf_ll *msf_create_ll(int value)
{
	msf_ll *ret = malloc(sizeof(*ret));
	ret->value = value;
	return ret;
}
