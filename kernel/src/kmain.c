#include "lexos/boot/stivale2.h"
#include "lexos/boot/cpu.h"
#include "lexos/boot/gdt.h"
#include "lexos/boot/idt.h"
#include "lexos/boot/acpi.h"
#include "lexos/kprint.h"


void kmain(stivale2_struct_s *args)
{
    kprint("Check CPU.\n");
    cpu_check();
    kprint("Init GDT.\n");
    gdt_init();
    kprint("Init IDT.\n");
    idt_init();
    kprint("Init ACPI driver.\n");
    acpi_init();

    kprint("Successfuly started.\n");
    HALT();
}
