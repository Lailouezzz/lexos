#ifndef H_ASM_EXCEPT
#define H_ASM_EXCEPT


/*          NAME   |  VEC NUM  |  DESCRIPTION                                 */
#define EXCEPT_DE_VEC    00  /* Divide error */
#define EXCEPT_DB_VEC    01  /* Debug exception */
#define EXCEPT_NMI_VEC   02  /* NMI interrupt */
#define EXCEPT_BP_VEC    03  /* Breakpoint */
#define EXCEPT_OF_VEC    04  /* Overflow */
#define EXCEPT_BR_VEC    05  /* BOUND range exceeded */
#define EXCEPT_UD_VEC    06  /* Invalid opcode */
#define EXCEPT_NM_VEC    07  /* Device note available (no math coprocessor) */
#define EXCEPT_DF_VEC    08  /* Double fault */
/* #define EXCEPT_VEC    09  /* Coprocessor segment overrune (reserved) */
#define EXCEPT_TS_VEC    10  /* Invalid TSS */
#define EXCEPT_NP_VEC    11  /* Segment not present */
#define EXCEPT_SS_VEC    12  /* Stack segment fault */
#define EXCEPT_GP_VEC    13  /* General protection */
#define EXCEPT_PF_VEC    14  /* Page fault */
/* #define EXCEPT_VEC    15  /* Intel reserved */
#define EXCEPT_MF_VEC    16  /* x87 FPU Floating-point error */
#define EXCEPT_AC_VEC    17  /* Alignment check */
#define EXCEPT_MC_VEC    18  /* Machine check */
#define EXCEPT_XM_VEC    19  /* SIMD Floating-point exception */
#define EXCEPT_VE_VEC    20  /* Virtualization exception */
/*                      21 to 31 include is intel reserved*/
/*                      32 to 255 are user defined*/


#endif /// #ifndef H_ASM_EXCEPT
