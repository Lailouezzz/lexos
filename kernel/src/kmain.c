#include "lexos/boot/cpu.h"
#include "lexos/boot/gdt.h"
#include "lexos/boot/idt.h"
#include "lexos/boot/stivale2.h"
#include "lexos/boot/acpi.h"
#include "lexos/boot/pic.h"
#include "lexos/boot/apic.h"
#include "lexos/kprint.h"


void kmain(s2_struct_s *args)
{
    cpu_check();
    gdt_init();
    idt_init();
    s2_init(args);

/* TODO : delete print function this will be do in s2_init and pmm_init */
#ifdef DEBUG
    s2_print_tags();
    s2_print_mmap();
#endif

    acpi_init();
    /* TODO : PIC / APIC stuff after PMM VMM work.
    pic_remap();
    apic_find((acpi_madt_s *)acpi_find_sdt(ACPI_MADT_SIGN));
    */

    kprint("Successfuly started.\n");
    HALT();
}
