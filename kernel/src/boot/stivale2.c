#include "boot/stivale2.h"


__attribute__((section(".stivale2hdr"), used))
struct stivale2_header stivale2hdr = {
    .entry_point = 0,
    .stack = 0,
    .flags = 0,
    .tags = 0
};
