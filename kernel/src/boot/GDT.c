#include "boot/GDT.h"


/* Define the GDT */

gdt_entry_t gdt_entries[3] = {
    {GDT_CREATE_ENTRY(0, 0, 0)},
    {GDT_CREATE_ENTRY(0, 0xFFFF, 0b1010111110011010)},     // Code
    {GDT_CREATE_ENTRY(0, 0xFFFF, 0b1010111110010010)}      // Data
};

gdt_pointer_t gdt_pointer = {
    .limit = sizeof(gdt_entries),
    .base  = (uintptr_t)gdt_entries
};
