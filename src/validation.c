#include "validation.h"


i32 validate_pipe_in(CommandList* list)
{
    return *list->token == '<' && list->prev && list->next;
}

i32 validate_pipe_out(CommandList* list)
{
    return *list->token == '>' && list->prev && list->next;
}

i32 validate_background_task(CommandList* list)
{
    return *list->token == '&' && list->prev && !list->next;
}
