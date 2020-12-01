#include "lexos/boot/except.h"
#include "lexos/kprint.h"


/* Called by ISR in isr.S 
 * errcode can be undefined depend of exceptnum
 */
void except_handler(uint64_t exceptnum, regs_s *regs, uint64_t errcode)
{
    /* TODO: real panic function */
    kprint("PANIC : EXCEPTION : %u\n", exceptnum);
    HALT();
}
