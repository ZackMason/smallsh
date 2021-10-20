#include "shell_io.h"

#include <assert.h>

#include "core.h"
#include "command_list.h"


struct CommandList* get_input()
{
    char input[1024>>1];
    size_t size = 0;
    ssize_t len = 0;

    if (!fgets(input, sizeof(input), stdin)) 
	return NULL;
    len = strlen(input);
    
    if (!len || input[0] == '#' || input[0] == ' ' || input[0] == '\n')
    {

	return NULL;
    }
    
    input[len-1] = '\0';

    // expand $$

    char* pid_token = NULL;
    while((pid_token = strstr(input, "$$")) != NULL)
    {
	char temp[2024];
	pid_token[0] = 0;
	pid_token[1] = 0;
	

	i32 pid = getpid();
	
	if(pid_token[2])
	    sprintf(temp, "%s%d%s", input, pid, &pid_token[2]);
	else
	    sprintf(temp, "%s%d", input, pid);
	strcpy(input, temp);
    }

    
    char* save = NULL;
    char* token = NULL;
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
