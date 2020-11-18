#ifndef H_BOOT_GDT
#define H_BOOT_GDT
#include <stdint.h>
#include "util.h"


#define GDT_CREATE_ENTRY(b, l, f)    \
        .limit_low16 = (l & 0xFFFF),        \
        .base_low24 = (b & 0xFFFFFF),        \
        .flags = (f & 0xFFFF),              \
        .base_high8 = (b & 0xFF000000)


typedef struct {
    uint16_t    limit_low16;
    uint32_t    base_low24 : 24;
    uint16_t    flags;
    uint8_t     base_high8;
} __PACKED gdt_entry_s;

typedef struct {
    uint16_t    limit;
    uint64_t    base;
} __PACKED gdt_pointer_s;


extern gdt_entry_s gdt_entries[3];
extern gdt_pointer_s gdt_pointer;


void init_gdt(void);


#endif /// #ifndef H_BOOT_GDT
