#ifndef _VALIDATION_H
#define _VALIDATION_H

#include "command_list.h"

i32 validate_pipe_in(CommandList* list);
i32 validate_pipe_out(CommandList* list);
i32 validate_background_task(CommandList* list);


#endif
