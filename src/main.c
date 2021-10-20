#include <stdio.h>

#include "core.h"

#include "shell_io.h"
#include "command_list.h"
#include "hash_map.h"
#include "custom_commands.h"
#include "shell_state.h"

#include <sys/wait.h>
#include <sys/types.h>

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
	while(head)
	{
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
	    pid_t child_pid = fork();

	    if (!child_pid)
	    {
		execvp(args[0], args);

		// if we get to here it means the command was not successful
		printf("Command unknown: %s\n", args[0]);
		fflush(stdout);
		exit(1);
	    }
	    else
	    {
		int exit_code;
		if (waitpid(child_pid, &exit_code, 0) >= 0)
		    state->status = WEXITSTATUS(exit_code);
	    }
	}
    }
    free(state);
    hash_map_free(custom_commands);
    return 0;
}
