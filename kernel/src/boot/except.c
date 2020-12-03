#include "lexos/panic.h"

#include "lexos/boot/except.h"


/* Exception messages */
static const char *exception_messages[32] = {
    "Divide error",
    "Debug exception",
    "NMI interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND range exceeded",
    "Invalid opcode",
    "Device note available (no math coprocessor)",
    "Double fault",
    "Coprocessor segment overrune (reserved)",
    "Invalid TSS",
    "Segment not present",
    "Stack segment fault",
    "General protection",
    "Page fault",
    "Reserved",
    "x87 FPU Floating-point error",
    "Alignment check",
    "Machine check",
    "SIMD Floating-point exception",
    "Virtualization exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


/* Called by ISR in isr.S 
 * errcode can be undefined depend of exceptnum
 */
void except_handler(uint64_t exceptnum, interrupt_stack_frame_s *stackframe,
        uint64_t errcode)
{
    /* TODO : handle task */
    if (exceptnum < 32)
    {
        panic(stackframe, "EXCEPTION : %s. (EXCEPTNUM : %u | ERRCODE : %u)\n",
                exception_messages[exceptnum], exceptnum, errcode);
    }
    else
    {
        panic(stackframe, "EXCEPTION : INVALID EXCEPT NUMBER.\n");
    }
}
