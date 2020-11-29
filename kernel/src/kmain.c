#include "boot/stivale2.h"
#include "boot/cpu.h"
#include "boot/idt.h"
#include "boot/gdt.h"
#include "tmp/kprint.h"


void kmain(stivale2_struct_s *args)
{
    kprint("Check CPU.\n");
    cpu_check();
    kprint("Init GDT.\n");
    gdt_init();
    kprint("Init IDT.\n");
    idt_init();
    asm volatile("int $3");
    for (;;)
        asm volatile ("hlt\n\t");
}
