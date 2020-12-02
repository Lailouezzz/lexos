#include "lexos/kprint.h"

#include "lexos/boot/except.h"


/* Called by ISR in isr.S 
 * errcode can be undefined depend of exceptnum
 */
void except_handler(uint64_t exceptnum, regs_s *regs, uint64_t errcode)
{
    UNUSED(regs);
    UNUSED(errcode);
    /* TODO: real panic function */
    kprint("PANIC : EXCEPTION : %u\n", exceptnum);
    HALT();
}
