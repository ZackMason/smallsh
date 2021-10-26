#include "validation.h"


i32 validate_pipe_in(CommandList* list)
{
    return *list->token == '<' && list->next;
}

i32 validate_pipe_out(CommandList* list)
{
    return *list->token == '>' && list->next;
}

i32 validate_background_task(CommandList* list)
{
    return strcmp(list->token, "&") == 0 && !list->next;
}
