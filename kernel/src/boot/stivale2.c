#include "boot/stivale2.h"


extern uint8_t stack[0x2000];


__SECTION(".stivale2hdr")
stivale2_header_s stivale2hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = 0,
    .tags = 0
};
