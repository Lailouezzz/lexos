#ifndef H_UTIL
#define H_UTIL


#define HALT() for (;;) asm volatile ("hlt")
#define STI() asm volatile ("sti")
#define CLI() asm volatile ("cli")

#define UNUSED(a) (void)(a)

#define __PACKED __attribute__((packed))
#define __SECTION(sec) __attribute__((section(sec)))
#define __INTERRUPT __attribute__((interrupt))
#define __NORETURN __attribute__((noreturn))


#endif /// #ifndef H_UTIL
