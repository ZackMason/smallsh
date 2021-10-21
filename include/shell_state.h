#ifndef _SHELL_STATE_H
#define _SHELL_STATE_H

#include "core.h"

typedef struct ShellState
{
    i32 status;
    i32 run;
    i32 child_processes[512];
    i32 top;
    i32 foreground_only;

} ShellState;

struct ShellState* shell_state_create();
pid_t shell_state_new_process(ShellState* state, pid_t pid);
#endif
