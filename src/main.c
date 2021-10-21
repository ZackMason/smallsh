#include <stdio.h>

#include "core.h"

#include "shell_io.h"
#include "command_list.h"
#include "hash_map.h"
#include "custom_commands.h"
#include "shell_state.h"
#include "validation.h"

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
	if (feof(stdin))
	{
	    state->run = 0;
	    continue;
	}
	
	if(isatty(0))
	{
	    char cur_dir[1024];
	    getcwd(cur_dir, sizeof(cur_dir));	
	    printf("%s: ",cur_dir);
	    fflush(stdout);
	}

	CommandList* cmd = get_input();

	if (!cmd) continue;
	
	char** args = calloc(list_len(cmd), sizeof(char*));
	i32 argc = 0;
	CommandList* head = cmd->next;
	i32 is_bkgr_cmd = 0;

	while(head)
	{
	    if (validate_background_task(head)) 
	    {
		is_bkgr_cmd = 1;
		head = head->next;
		continue;
	    }
	    args[argc] = calloc(strlen(head->token)+1, sizeof(char));
	    strcpy(args[argc++], head->token);
	    head = head->next;
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
		if(is_bkgr_cmd)
		{
		    dup2(open("/dev/null", O_WRONLY), 1);
		}
		execvp(args[0], args);
		
		// if we get to here it means the command was not successful
		printf("Command unknown: %s\n", cmd->token);
		fflush(stdout);
		exit(1);
	    }
	    else
	    {
		int exit_code;
		if (!is_bkgr_cmd && waitpid(child_pid, &exit_code, is_bkgr_cmd ? WNOHANG : 0) >= 0)
		    state->status = WEXITSTATUS(exit_code);
	    }
	}
    }

    // clean up
    free(state);
    hash_map_free(custom_commands);
    return 0;
}
