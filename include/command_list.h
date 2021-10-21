#ifndef _COMMAND_LIST_H
#define _COMMAND_LIST_H

#include "core.h"

typedef struct CommandList
{
    char* token;
    struct CommandList* next;
    struct CommandList* prev;
} CommandList;

void print_list(struct CommandList* head);
i32 list_len(struct CommandList* head);
struct CommandList* list_last(struct CommandList* head);

#endif
