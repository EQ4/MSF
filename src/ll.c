#include "../include/ll.h"

void msf_destroy_ll(msf_ll *ptr)
{
	msf_ll *prev;
	msf_ll *cur;
	prev = NULL;
	cur = ptr;

	msf_ll *addresses; // Addresses we have already seen for end detection
	addresses = msf_create_ll(-1);

	msf_ll *addresses_base = addresses;

	int finished = 0;
	while (finished == 0)
	{
		// Check for the current address in our existing list
		msf_ll *next_check = addresses_base;
		//printf("--Current node's next address is 0x%d.\n",(int)cur->next);
		while (next_check->next != NULL) // Go through the LL of seen addresses
		{
			//printf("--- Checking %d against %d...\n",(unsigned int)next_check->value,(unsigned int)cur->next);
			if (next_check->value == (unsigned int)cur->next) // If we have seen the next node...
			{
				finished = 1; // ...we are done.
				free(cur);
				break;
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
		//		printf("--Finished with this list.\n");
				finished = 1;
			}
			else
			{
		//		printf("--Hopping to 0x%d\n",(int)cur->next);
				cur = cur->next; // Hop to next node
			}
			//addresses->value = (int)prev; // Record the address we visited
		//	printf("--Marked address 0x%d as visited.\n",(int)prev);
			addresses->next = msf_create_ll((unsigned int)prev); // Build the next address node
			addresses = addresses->next; // Go to it
			//addresses->next = NULL;
			//addresses->value = -1;
			//printf("--Freeing msf_ll node at 0x%d\n",(int)prev);
			free(prev); // Free the previous
		}
	}
	
	// Now we must free our addresses list
	addresses = addresses_base;
	while (addresses->next != NULL)
	{
		prev = addresses;
		addresses = addresses->next;
//		printf("--Freeing address list node at 0x%d\n",(int)prev);
		free(prev);
	}
	free(addresses);
}

	

msf_ll *msf_create_ll(int value)
{
	msf_ll *ret = malloc(sizeof(*ret));
	ret->value = value;
	ret->next = NULL;
	return ret;
}

void msf_add_ll(msf_ll *base, int value)
{
	msf_ll *ptr = base;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = msf_create_ll(value);
}

void msf_loop_ll(msf_ll *base, msf_ll *point)
{
	msf_ll *ptr;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = point;
}
