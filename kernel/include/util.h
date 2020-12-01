#ifndef H_UTIL
#define H_UTIL


#define HALT() asm volatile ("hlt")

#define __PACKED __attribute__((packed))
#define __SECTION(sec) __attribute__((section(sec)))
#define __INTERRUPT __attribute__((interrupt))


#endif /// #ifndef H_UTIL
