#ifndef _CUSTOM_COMMANDS_H
#define _CUSTOM_COMMANDS_H

#include "command_list.h"
#include "shell_state.h"

typedef void (*CommandFunc)(CommandList* args, ShellState* state);

void cd_cmd(CommandList* args, ShellState* state);
void cwd_cmd(CommandList* args, ShellState* state);
void exit_cmd(CommandList* args, ShellState* state);
void status_cmd(CommandList* args, ShellState* state);

#endif
