#include "lexos/kprint.h"

#include "lexos/panic.h"


void panic(interrupt_stack_frame_s *stackframe, const char *fmt, ...)
{
    va_list args;

    kprint("KERNEL PANIC : ");
    va_start(args, fmt);
    kvprint(fmt, args);
    va_end(args);
    
    if (stackframe)
    {

    }
    else
    {
        
    }

    HALT();
}
