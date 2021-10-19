#include "shell_state.h"

#include <stdlib.h>

struct ShellState* shell_state_create()
{
    ShellState* new_state = calloc(1, sizeof(ShellState));
    new_state->run = 1;
    return new_state;
}
