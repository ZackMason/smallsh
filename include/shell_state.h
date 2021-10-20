#ifndef _SHELL_STATE_H
#define _SHELL_STATE_H

#include "types.h"

typedef struct ShellState
{
    i32 status;
    i32 run;
    i32 child_processes[512];
} ShellState;

struct ShellState* shell_state_create();

#endif
