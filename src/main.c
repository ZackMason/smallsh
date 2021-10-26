#include <stdio.h>

#include "core.h"

#include "shell_io.h"
#include "command_list.h"
#include "hash_map.h"
#include "custom_commands.h"
#include "shell_state.h"
#include "validation.h"
#include "parsed_command.h"


int main()
{
    ShellState* state = shell_state_create();
    
    HashMap* custom_commands = hash_map_create(256, sizeof(CommandFunc));

    hash_map_add(custom_commands, "cd", cd_cmd, sizeof(cd_cmd));
    hash_map_add(custom_commands, "status", status_cmd, sizeof(status_cmd));
    hash_map_add(custom_commands, "exit", exit_cmd, sizeof(exit_cmd));
    hash_map_add(custom_commands, "cwd", cwd_cmd, sizeof(cwd_cmd));
    
    while(state->run)
    {	
	//if we reach the eof, terminate the shell
	if (feof(stdin))
	{
	    state->run = 0;
	    continue;
	}
	// check background pids
	for(int i = 0; i < state->top; i++)
	{
	    if (state->child_processes[i])
	    {
		int exit_code;
		if (waitpid(state->child_processes[i], &exit_code, WNOHANG) >= 0)
		{
		    state->status = WEXITSTATUS(exit_code);

		    printf("Process: [%d] closed with exit code %d\n", state->child_processes[i], state->status);
		    fflush(stdout);

		    state->child_processes[i] = 0;
		} 
	    }
	}
	
	//is running interactively
	if(isatty(0))
	{
	    char cur_dir[1024];
	    getcwd(cur_dir, sizeof(cur_dir));	
	    printf("%s: ",cur_dir);
	    fflush(stdout);
	}
	// get input from the user
	CommandList* cmd = get_input();
	
	// if get_input returned null, try again
	if (!cmd) continue;
	
	// skip the first node which holds the full string that the user typed
	CommandList* head = cmd->next;
	ParsedCommand* parsed_command = parse_command(head);

	if (parsed_command->mask & CMD_SYNTAX_ERROR)
	{
	    printf("Parsed Command Syntax Error, try again\n");
	    fflush(stdout);
	}
		
	CommandFunc builtin_command = hash_map_get(custom_commands, cmd->next->token);
	if (builtin_command)
	{
	    builtin_command(cmd->next, state);
	}
	else
	{
	    pid_t child_pid = shell_state_new_process(state, fork());

	    if (!child_pid)
	    {
		if(parsed_command->mask & CMD_BACKGROUND_TASK)
		{
		    dup2(open("/dev/null", O_WRONLY), 1);
		}
		execvp(parsed_command->command[0], parsed_command->command);
		
		// if we get to here it means the command was not successful
		printf("Command unknown: %s\n", cmd->token);
		fflush(stdout);
		exit(1);
	    }
	    else
	    {
		int exit_code;
		if (!(parsed_command->mask & CMD_BACKGROUND_TASK))
		{ 
		    if(waitpid(child_pid, &exit_code, 0) >= 0)
			state->status = WEXITSTATUS(exit_code);
		}
	    }
	}
    }

    // clean up
    free(state);
    hash_map_free(custom_commands);
    return 0;
}
