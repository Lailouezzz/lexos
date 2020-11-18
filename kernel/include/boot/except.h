#ifndef H_BOOT_EXCEPT
#define H_BOOT_EXCEPT
#include <stdint.h>
#include "asm/except.h"
#include "util.h"


typedef struct {
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
} __PACKED regs_s;


/* Defined in except_isr.S */
extern uintptr_t except_isr_table[32];


#endif /// #ifndef H_BOOT_EXCEPT