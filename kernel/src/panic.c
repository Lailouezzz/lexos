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
        kprint("--- INTERRUPT STACK FRAME :\n");
        kprint("RAX=0x%x    RBX=0x%x    RCX=0x%x\n", stackframe->rax,
                stackframe->rdx, stackframe->rcx);
        kprint("RDX=0x%x    RDI=0x%x    RSI=0x%x\n", stackframe->rdx,
                stackframe->rdi, stackframe->rsi);
        kprint("RBP=0x%x    R08=0x%x    R09=0x%x\n", stackframe->rbp,
                stackframe->r8, stackframe->r9);
        kprint("R10=0x%x    R11=0x%x    R12=0x%x\n", stackframe->r10,
                stackframe->r11, stackframe->r12);
        kprint("R13=0x%x    R14=0x%x    R15=0x%x\n", stackframe->r13,
                stackframe->r14, stackframe->r15);
        kprint("---\n");
    }
    else
    {
        
    }

    HALT();
}
