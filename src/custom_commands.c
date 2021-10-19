#include "custom_commands.h"

void cd_cmd(CommandList* args, ShellState* state)
{
    //printf("cd ");
    //print_list(args->next);
    //fflush(stdout);
    
    chdir(args->next && *args->next->token != '~' ? args->next->token : getenv("HOME"));
}

void cwd_cmd(CommandList* args, ShellState* state)
{
    char dir[1024];
    getcwd(dir, 1024);
    printf("%s\n", dir );
    fflush(stdout);
}

void exit_cmd(CommandList* args, ShellState* state)
{
    printf("Exiting shell\n");
    fflush(stdout);
    state->run = 0;
}

void status_cmd(CommandList* args, ShellState* state)
{
    printf("exit value %d\n", state->status);
    fflush(stdout);
}
