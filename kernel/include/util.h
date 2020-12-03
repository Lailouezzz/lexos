#ifndef H_UTIL
#define H_UTIL


#define HALT() for (;;) asm volatile ("hlt")
#define STI() asm volatile ("sti")
#define CLI() asm volatile ("cli")

#define UNUSED(a) (void)(a)
#define D_CHR(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | (a))
#define Q_CHR(a, b, c, d, e, f, g, h) (((h) << 56) | ((g) << 48) | ((f) << 40) \
        | ((e) << 32) | ((d) << 24) | ((c) << 16) | ((b) << 8) | (a))

#define __PACKED __attribute__((packed))
#define __SECTION(sec) __attribute__((section(sec)))
#define __INTERRUPT __attribute__((interrupt))
#define __NORETURN __attribute__((noreturn))


#endif /// #ifndef H_UTIL
