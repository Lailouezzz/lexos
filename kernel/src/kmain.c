#include "boot/stivale2.h"
#include "boot/cpu.h"
#include "boot/idt.h"
#include "boot/gdt.h"
#include "tmp/kprint.h"


void kmain(stivale2_struct_s *arg)
{
    kprint("Check CPU.\n");
    check_cpu();
    kprint("Init GDT.\n");
    init_gdt();
    kprint("Init IDT.\n");
    init_idt();
    asm volatile("int $0");

    asm volatile ("hlt\n\t");
}
