#include "ll.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void msf_destroy_ll(msf_ll *ptr)
{
	if (ptr == NULL)
	{
		return;
	}
	// First build a list of addresses we've seen, and check against them 
	// before freeing anything. This is to handle the ones that loop back
	// on earlier nodes in a listo.
	msf_ll *addr_list = msf_create_ll(-1);
	addr_list->next = NULL;
	msf_ll *addr_list_base = addr_list; // Store this to go back to later
	msf_ll *current = ptr;
	while (current != NULL && current->next != NULL)
	{
		// Go through the address list as it is now. If the address of current
		// is not in the list, add it to the list. Otherwise, we have found a
		// loop in the list and are finished constructing it.
		int addr_in_list = 0;
		addr_list = addr_list_base;
		while(addr_list->next != NULL && !addr_in_list)
		{
			if (addr_list->value == (unsigned int)current)
			{
				addr_in_list = 1;
			}
			// Travel down the list
			addr_list = addr_list->next;
			if (addr_list->next == NULL)
			{
				if (addr_list->value == (unsigned int)current)
				{
					addr_in_list = 1;
				}
			}
		}
		if (!addr_in_list)
		{
			// The address wasn't found, so we add it.
			addr_list->next = msf_create_ll((unsigned int)current);

			// Go to the next node and repeat.
			current = current->next;
		}
		else
		{
			current = NULL;
		}
	}

	// Using the list of addresses, free the pointers as stored in the address 
	// list then free the list itself.
	
	addr_list = addr_list_base->next; // Skip the -1 inserted
	msf_ll *prev;
	while (addr_list != NULL)
	{
		// Free value pointed to by the address list node
		free((msf_ll*)addr_list->value);

		// Store address to free
		prev = (msf_ll *)addr_list;

		// Traverse list
		addr_list = addr_list->next;

		// Free node we hopped off of
		if (prev)
		{
			free(prev);
		}
	}
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
	int first = 0;
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
				if (!first)
				{
					llptr->next = msf_create_ll((int)strtoul(token,NULL,0) + shift);
					if (llptr->next->value == shift) // deal with odd outliers
					{
						llptr->next->value = 0;
					}
					if (get_loop == 1)
					{
						loop = llptr->next;
						get_loop = 2;
					}
					llptr = llptr->next;
				}
				else
				{
					first = 1;

					llptr->value = ((int)strtoul(token,NULL,0) + shift);
				}
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
