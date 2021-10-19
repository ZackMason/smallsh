#ifndef _SHELL_STATE_H
#define _SHELL_STATE_H

#include "types.h"

typedef struct ShellState
{
    i32 status;
    i32 run;
    
} ShellState;

struct ShellState* shell_state_create();

#endif
