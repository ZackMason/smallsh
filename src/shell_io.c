#include "shell_io.h"

#include <assert.h>

#include "core.h"
#include "command_list.h"

void clear_input() {
    char ch;
    while((ch = getchar() != '\n' && (ch != EOF)));
}

struct CommandList* get_input()
{
    char input[1024];
    size_t size = 0;
    ssize_t len = 0;

    char cur_dir[1024];
    getcwd(cur_dir, 1024);
    if (feof(stdin))
    {
	clear_input();
    }
    else
    {
	printf("%s: ", cur_dir);
	fflush(stdout);
    }
    if (!fgets(input, sizeof(input), stdin)) return NULL;
    len = strlen(input);
    
    if (!input || input[0] == '#' || input[0] == ' ' || input[0] == '\n')
    {
//	printf("\33[2K\r");
//	fflush(stdout);

	return NULL;
    }
    
    input[len-1] = '\0';
    //printf("%s\n", input);
    //return NULL;
    
    char* save = 0;
    char* token = 0;
    CommandList* head = calloc(1, sizeof(CommandList));
    CommandList* last = head;

    head->token = calloc(strlen(input)+1, sizeof(char));
    strcpy(head->token, input);
    
    while((token = strtok_r(last!=head ? NULL : input, " ", &save)) != NULL)
    {
	CommandList* new = calloc(1, sizeof(CommandList));
	new->token = calloc(strlen(token)+1, sizeof(char));
	strcpy(new->token, token);

	if (last)
	{
	    last->next = new;
	    new->prev = last;
	}
	last = new;
    }
    return head;
}
