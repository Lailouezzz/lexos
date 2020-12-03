#include "lexos/boot/idt.h"


/* Define the IDT */

idt_entry_s idt_entries[IDT_ENTRIES_NUM] = { 0 };
idt_pointer_s idt_pointer = {
    .limit = sizeof(idt_entries),
    .offset = idt_entries
};


void idt_init(void)
{
    /* Set exceptions entries */
    for (size_t i = 0;
            i < 3; i++)
    {
        idt_entries[i] = IDT_ENTRY(except_isr_table[i], IDT_INT_GATE, 0x08, 0);
    }

    idt_entries[3] = IDT_ENTRY(except_isr_table[3], IDT_TRAP_GATE, 0x08, 0);
    idt_entries[4] = IDT_ENTRY(except_isr_table[4], IDT_TRAP_GATE, 0x08, 0);

    for (size_t i = 5;
            i < sizeof(except_isr_table) / sizeof(*except_isr_table); i++)
    {
        idt_entries[i] = IDT_ENTRY(except_isr_table[i], IDT_INT_GATE, 0x08, 0);
    }

    /* TODO : insert syscall interrupt */

    /* Let's load IDT */
    asm volatile(
        "lidt (%0)"
        :
        : "r" (&idt_pointer)
        :
    );

    return;
}
