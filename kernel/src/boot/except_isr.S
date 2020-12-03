#include "lexos/asm/except.h"


extern except_handler


bits 64
section .text


; push all registers
%macro pushaq   0
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rbp
    push rdi
    push rsi
    push rax
    push rbx
    push rcx
    push rdx
%endmacro

; pop all registers
%macro popaq    0
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop rsi
    pop rdi
    pop rbp
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
%endmacro

; Low level ISR routine calling exception handler (NOERR)
%macro except_isr_noerr 1
    cli
    push 0
    push %1
    pushaq
    ; initial rsp is now at rsp+15*8

    mov rdi, rsp    ; pointer to regs_s struct

    cld
    call except_handler  ; in exceptions.c

    popaq
    add rsp, 16          ; skip int num and err code
    sti
    iretq
%endmacro

; Low level ISR routine calling exception handler (ERR)
%macro except_isr_err 1
    cli
    push %1
    pushaq
    ; initial rsp is now at rsp+15*8

    mov rdi, rsp        ; pointer to interrupt_stack_frame_s struct

    cld
    call except_handler ; in exceptions.c

    popaq
    add rsp, 16         ; skip int num and err code
    sti
    iretq
%endmacro

; Low level ISR routine calling exception handler (RESERVED)
%macro except_isr_res 1
except_%1:
    push 0
    push %1
    cli
    pushaq
    ; initial rsp is now at rsp+15*8

    mov rdi, rsp        ; pointer to interrupt_stack_frame_s struct

    cld
    call except_handler ; in exceptions.c

    popaq
    add rsp, 16         ; skip int num and err code
    sti
    iretq
%endmacro


except_de: /* Divide error */
    except_isr_noerr EXCEPT_DE_VEC
except_db: /* Debug exception */
    except_isr_noerr EXCEPT_DB_VEC
except_nmi: /* NMI interrupt */
    except_isr_noerr EXCEPT_NMI_VEC
except_bp: /* Breakpoint */
    except_isr_noerr EXCEPT_BP_VEC
except_of: /* Overflow */
    except_isr_noerr EXCEPT_OF_VEC
except_br: /* BOUND range exceeded */
    except_isr_noerr EXCEPT_BR_VEC
except_ud: /* Invalid opcode */
    except_isr_noerr EXCEPT_UD_VEC
except_nm: /* Device note available (no math coprocessor) */
    except_isr_noerr EXCEPT_NM_VEC
except_df: /* Double fault */
    except_isr_err EXCEPT_DF_VEC
except_isr_res 09
except_ts: /* Invalid TSS */
    except_isr_err EXCEPT_TS_VEC
except_np: /* Segment not present */
    except_isr_err EXCEPT_NP_VEC
except_ss: /* Stack segment fault */
    except_isr_err EXCEPT_SS_VEC
except_gp: /* General protection */
    except_isr_err EXCEPT_GP_VEC
except_pf: /* Page fault */
    except_isr_err EXCEPT_PF_VEC
except_isr_res 15
except_mf: /* x87 FPU Floating-point error */
    except_isr_noerr EXCEPT_MF_VEC
except_ac: /* Alignment check */
    except_isr_err EXCEPT_AC_VEC
except_mc: /* Machine check */
    except_isr_noerr EXCEPT_MC_VEC
except_xm: /* SIMD Floating-point exception */
    except_isr_noerr EXCEPT_XM_VEC
except_ve: /* Virtualization exception */
    except_isr_noerr EXCEPT_VE_VEC
except_isr_res 21
except_isr_res 22
except_isr_res 23
except_isr_res 24
except_isr_res 25
except_isr_res 26
except_isr_res 27
except_isr_res 28
except_isr_res 29
except_isr_res 30
except_isr_res 31


section .data

global except_isr_table

ALIGN 16
except_isr_table:
    dq except_de    /* Divide error */
    dq except_db    /* Debug exception */
    dq except_nmi   /* NMI interrupt */
    dq except_bp    /* Breakpoint */
    dq except_of    /* Overflow */
    dq except_br    /* BOUND range exceeded */
    dq except_ud    /* Invalid opcode */
    dq except_nm    /* Device note available (no math coprocessor) */
    dq except_df    /* Double fault */
    dq except_09    /* Coprocessor segment overrune (reserved) */
    dq except_ts    /* Invalid TSS */
    dq except_np    /* Segment not present */
    dq except_ss    /* Stack segment fault */
    dq except_gp    /* General protection */
    dq except_pf    /* Page fault */
    dq except_15    /* Reserved */
    dq except_mf    /* x87 FPU Floating-point error */
    dq except_ac    /* Alignment check */
    dq except_mc    /* Machine check */
    dq except_xm    /* SIMD Floating-point exception */
    dq except_ve    /* Virtualization exception */
    dq except_21    /* Reserved */
    dq except_22    /* Reserved */
    dq except_23    /* Reserved */
    dq except_24    /* Reserved */
    dq except_25    /* Reserved */
    dq except_26    /* Reserved */
    dq except_27    /* Reserved */
    dq except_28    /* Reserved */
    dq except_29    /* Reserved */
    dq except_30    /* Reserved */
    dq except_31    /* Reserved */
