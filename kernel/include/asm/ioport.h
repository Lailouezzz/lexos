#ifndef H_ASM_IOPORT
#define H_ASM_IOPORT


/* OUTPUT */

#define PORT_OUTB(port, value) ({       \
    asm volatile (                      \
        "outb %%al, %%dx"               \
        :                               \
        :   "a" (value), "d" (port)     \
        :                               \
    );                                  \
})

#define PORT_OUTW(port, value) ({       \
    asm volatile (                      \
        "outw %%al, %%dx"               \
        :                               \
        :   "a" (value), "d" (port)     \
        :                               \
    );                                  \
})

#define PORT_OUTD(port, value) ({       \
    asm volatile (                      \
        "outd %%al, %%dx"               \
        :                               \
        :   "a" (value), "d" (port)     \
        :                               \
    );                                  \
})

/* INPUT */

#define PORT_INB(port) ({               \
    uint8_t v;                          \
    asm volatile (                      \
        "inb %%dx, %%al"                \
        :   "=a" (v)                    \
        :   "d" (port)                  \
        :                               \
    );                                  \
    v;                                  \
})


#define PORT_INW(port) ({               \
    uint16_t v;                         \
    asm volatile (                      \
        "inw %%dx, %%al"                \
        :   "=a" (v)                    \
        :   "d" (port)                  \
        :                               \
    );                                  \
    v;                                  \
})


#define PORT_IND(port) ({               \
    uint32_t v;                         \
    asm volatile (                      \
        "ind %%dx, %%al"                \
        :   "=a" (v)                    \
        :   "d" (port)                  \
        :                               \
    );                                  \
    v;                                  \
})


#endif /// #ifndef H_ASM_IOPORT
