#include "shell_state.h"

struct ShellState* shell_state_create()
{
    ShellState* new_state = calloc(1, sizeof(ShellState));
    new_state->run = 1;
    new_state->status = 0;
    new_state->top = 0;
    new_state->foreground_only = 0;
    return new_state;

}

pid_t shell_state_new_process(ShellState* state, pid_t pid)
{
    state->top = (state->top+1) % 512;
    state->child_processes[state->top] = pid;
    return pid;
}
