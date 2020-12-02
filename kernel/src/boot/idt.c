#include "lexos/boot/idt.h"
#include "lexos/kprint.h"


#define SET_IDT_ENTRY(v, off, attr, sel, _ist) \
        idt_entries[v].offset_low16 = ((uintptr_t)off) & 0xFFFF; \
        idt_entries[v].offset_mid16 = (((uintptr_t)off) >> 16) & 0xFFFF; \
        idt_entries[v].offset_hig32 = (((uintptr_t)off) >> 32) & 0xFFFFFFFF; \
        \
        idt_entries[v].type_attr = attr; \
        \
        idt_entries[v].selector = sel; \
        \
        idt_entries[v].ist = _ist; \
        \
        idt_entries[v].zero = 0;


/* Define the IDT */

idt_entry_s idt_entries[256] = { 0 };
idt_pointer_s idt_pointer = {
    .limit = sizeof(idt_entries),
    .offset = idt_entries
};


void idt_init(void)
{
    /* Set exceptions entries */
    for (size_t i = 0;
            i < sizeof(except_isr_table) / sizeof(*except_isr_table); i++)
    {
        if (except_isr_table[i])
        {
            SET_IDT_ENTRY(i, except_isr_table[i], 0x8E, 0x08, 0);
        }
    }

    /* Let's load IDT */
    asm volatile(
        "lidt (%0)"
        :
        : "r" (&idt_pointer)
        :
    );

    return;
}
