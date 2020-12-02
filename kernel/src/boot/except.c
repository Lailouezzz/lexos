#include "lexos/panic.h"

#include "lexos/boot/except.h"


/* Called by ISR in isr.S 
 * errcode can be undefined depend of exceptnum
 */
void except_handler(uint64_t exceptnum, interrupt_stack_frame_s *stackframe,
        uint64_t errcode)
{
    UNUSED(errcode);
    panic(stackframe, "EXCEPTION : %u\n", exceptnum);
}
