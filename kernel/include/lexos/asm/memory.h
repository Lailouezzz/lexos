#ifndef H_LEXOS_ASM_MEMORY
#define H_LEXOS_ASM_MEMORY


/* Some paging defines related */
#define PAGE_ALIGN 4096
#define PAGE_ALIGN_DOWN(a) ((a) & ~(PAGE_ALIGN-1))
#define PAGE_ALIGN_UP(a) PAGE_ALIGN_DOWN((a) + PAGE_ALIGN-1)
#define PAGE_IS_ALIGN(a) (((a) & (PAGE_ALIGN-1)) == 0)


#endif /// #ifndef H_LEXOS_ASM_MEMORY
