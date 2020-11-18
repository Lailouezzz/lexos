#include "boot/stivale2.h"
#include "boot/idt.h"
#include "boot/gdt.h"
#include "tmp/kprint.h"


void kmain(stivale2_struct_s *arg)
{
    kprint("Init GDT...\n");
    init_gdt();
    kprint("Init IDT...\n");
    init_idt();
    asm volatile("int $0");
    asm volatile("int $1");
    asm volatile("int $2");
    asm volatile("int $3");
    asm volatile("int $4");
    asm volatile("int $5");
    asm volatile("int $6");
    asm volatile("int $7");
    asm volatile("int $8");
    asm volatile("int $10");
    asm volatile("int $11");

    asm volatile ("hlt\n\t");
}
