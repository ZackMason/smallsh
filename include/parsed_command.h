#ifndef _PARSED_COMMAND_H
#define _PARSED_COMMAND_H

#include "core.h"
#include "command_list.h"

#define BIT(x) (1<<x)

enum {
    CMD_BACKGROUND_TASK = BIT(0),
    CMD_FILE_IN = BIT(1),
    CMD_FILE_OUT = BIT(2),
    CMD_SYNTAX_ERROR = BIT(3)
};

typedef struct ParsedCommand {
    char* input_file;
    char* output_file;
    i32 mask;
    char** command;
    i32 command_len;
} ParsedCommand;

ParsedCommand* parse_command(CommandList* head);
#endif
