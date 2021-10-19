#include "command_list.h"

#include "core.h"

void print_list(CommandList* head)
{
    i8 count = 0;
    while(head)
    {
	if (count++) printf(" ");
	printf("%s", head->token);
	head = head->next;
    }
    printf("\n");
    fflush(stdout);
}

i32 list_len(CommandList* head)
{
    i32 count = 0;
    while(head)
    {
	count++;
	head = head->next;
    }
    return count;
}
