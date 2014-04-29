#include "../include/ll.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		while (next_check->next != NULL) // Go through the LL of seen addresses
		{
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
				finished = 1;
			}
			else
			{
				cur = cur->next; // Hop to next node
			}
			addresses->next = msf_create_ll((unsigned int)prev); // Build the next address node
			addresses = addresses->next; // Go to it
			free(prev); // Free the previous
		}
	}
	
	// Now we must free our addresses list
	addresses = addresses_base;
	while (addresses->next != NULL)
	{
		prev = addresses;
		addresses = addresses->next;
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

void msf_print_ll(msf_ll *ptr)
{
	int help = 0;
	while (ptr != NULL && help < 512)
	{
		help++;
		printf("[%i] -> ",ptr->value);
		ptr = ptr->next;
	}
	printf("\n");
}

msf_ll *msf_parse_ll(char *str, int shift, int ignore)
{
	msf_ll *ret = msf_create_ll(0);
	msf_ll *llptr = ret;
	msf_ll *loop = NULL;
	int get_loop = 0;
	char *token = strtok(str, " ,_\t");

/*

For each value in the str line, add a node to ret with that value.
If it contains a pipe (|), a loop point is set. This means that the
address of the next added node should be recorded in the loop pointer.

*/

	if (str != NULL)
	{
		llptr->value = (int)strtoul(str,NULL,0);
	}
	int count = 0;
	while (token != NULL)
	{
		if (token[0] == '|')
		{
			get_loop = 1;	
		}
		else
		{
			if (count >= ignore)
			{
				printf("Adding %lu.\n",strtoul(token,NULL,0));
				llptr->next = msf_create_ll((int)strtoul(token,NULL,0) + shift);
				if (llptr->next->value == shift) // deal with odd outliers
				{
					llptr->next->value = 0;
				}
				if (get_loop == 1)
				{
					loop = llptr->next;
					get_loop = 2;
					printf("Set loop point in LL\n");
				}
				llptr = llptr->next;
			}
			count++;
		}
		token = strtok(NULL, " ,_\t");
	}
	if (get_loop == 2 && loop != NULL)
	{
		llptr->next = loop;
	}
	else
	{
		llptr->next = llptr;
	}
	return ret; 
}
