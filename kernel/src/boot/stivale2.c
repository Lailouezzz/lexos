#include "boot/stivale2.h"


static uint8_t stack[4096] = { 0 };

__SECTION(".stivale2hdr")
struct stivale2_header stivale2hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = 0,
    .tags = 0
};