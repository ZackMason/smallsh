#include "parsed_command.h"

#include "validation.h"

ParsedCommand* parse_command(CommandList* head)
{
    ParsedCommand* new = calloc(1, sizeof(ParsedCommand));
    CommandList* start = head;

    while(head)
    {
	if(validate_background_task(head)) // bg task
	{
	    new->mask |= CMD_BACKGROUND_TASK;
	}
	else if (validate_pipe_in(head)) // file in
	{
	    new->mask |= CMD_FILE_IN;
	    
	    head->prev->next = NULL;
	    head = head->next;

	    if(!head)
	    {
		new->mask |= CMD_SYNTAX_ERROR;
		break;
	    }
	    
	    new->input_file = calloc(strlen(head->token)+1, sizeof(char));
	    strcpy(new->input_file, head->token);
	}
	else if(validate_pipe_out(head)) // file out
	{
	    new->mask |= CMD_FILE_OUT;
	    
	    head->prev->next = NULL;
	    head = head->next;

	    if(!head)
	    {
		new->mask |= CMD_SYNTAX_ERROR;
		break;
	    }

	    new->output_file = calloc(strlen(head->token)+1, sizeof(char));
	    strcpy(new->output_file, head->token);
	}

	head = head->next;
    }
    
    new->command_len = list_len(start);
    new->command = calloc(new->command_len, sizeof(char*));
    for(int i = 0; start; i++)
    {
	new->command[i] = calloc(strlen(start->token)+1, sizeof(char));
	strcpy(new->command[i], start->token);
	
	start = start->next;
    }

    return new;
}
